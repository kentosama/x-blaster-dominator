/* 
 * File:   Player.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 2 mars 2013, 12:57
 */

#include "Player.h"

Player::Player() {
    gameDifficulty = Profil::Instance()->mode;
    color = Color::White;
    sprite.setTexture(FileManager::Instance()->player[0]);
    shadow = sprite;
    SuperAttackTime = sf::seconds(2);
    bulle.setScale(1.2, 1.2);
    bulle.setTexture(FileManager::Instance()->items[3]);
    setFrame = false;
    modules.reserve(2);
    shadowModules.reserve(2);
    rect.reserve(4);
    rectShape.reserve(4);
    for (unsigned char i = 0; i < 2; i++) {
        modules.emplace_back();
        shadowModules.emplace_back();
        modules[i].setTexture(FileManager::Instance()->items[2]);
        shadowModules[i].setColor(Color(50, 50, 50, 50));
    }
    
    for (unsigned char i = 0; i < 4; i++)
        rect.emplace_back();
        
   
    secondaryShotTime = sf::seconds(0.26);
    shotTime = sf::seconds(0.13);
    deadTime = sf::seconds(5);
    
    // Cible
    target.rect.setOrigin(getOrigin());
    sndSuperAttack.setBuffer(FileManager::Instance()->sound[8]);

   
#ifdef _DEBUG
    showRectangle = false;
    godMode = false;
    unlimitedAttack = false;
    for (unsigned char i = 0; i < 4; i++)
    rectShape.emplace_back();
    // Affichage des rectangles et attribution des couleurs
    rectShape[0].setFillColor(Color::Red);
    rectShape[1].setFillColor(Color::Blue);
    rectShape[2].setFillColor(Color::Blue);
    rectShape[3].setFillColor(Color::Yellow);
   
#endif

}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

Vector2f Player::getPosition() {

    return Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

Vector2f Player::getSize() {
    return Vector2f(sprite.getTexture()->getSize().x / 4, sprite.getTexture()->getSize().y);
}

Vector2f Player::getOrigin() {
    return Vector2f((sprite.getGlobalBounds().width / 4) / 2, sprite.getGlobalBounds().height / 2);
}

const unsigned char Player::getHealthPortion() {
    return health / 10;
}

bool Player::gameover() {
    
    if (lives <= 0 && credits <= 0)
        return true;
    else return false;
}

bool Player::getCredits() {
    if(lives <= 0 && credits > 0)
        return true;
    else return false;
}

void Player::initialize(bool a) {
    if (a) {
        gameDifficulty = Profil::Instance()->mode;
        active = true;
        countSuperAttack = 1;
        weapon = 0;
        newLive = false;
        credits = Profil::Instance()->credits;

        if (gameDifficulty == 2)
            moduleTime = sf::seconds(10);
        else moduleTime = sf::seconds(5);
        setBullet();
        setLive();
    } else { 
        sprite.setPosition(380, 800);
        target.active = false;
        SuperAttack.initialize();
    }
    
    activeSuperAttack = false;
    lastShot = 0;
    collision = false;
    goldCollision = false;
    previousCollision = 0;
    previousSetBullet = 0;
    lastModule = 0;
    playerMove = 0;
    health = 100;
    module = 0;
    lostLives = 0;
    lastTime = 0;
    control = false;
    inZone = false;
    dead = true;
    target.active = false;
    startMission = true;
    
    animationShadow.initialize(sprite, Vector2f(380, 800), sprite.getTexture()->getSize().x / 4, 35, 4, 0, 100, Color(50, 50, 50, 50), Vector2f(1.2,1.2), true, 0, Vector2f(sprite.getOrigin()), true);
    animation.initialize(sprite, Vector2f(380, 800), sprite.getTexture()->getSize().x / 4, 35, 4,0, 100, color, Vector2f(1.2,1.2), true, 0, Vector2f(sprite.getOrigin()), true);

    moduleClock.restart();
}

void Player::liveManager() {

    // Gestion de la vie et de l'énergie
    
    if (health <= 0) {
        // Le joueur meurt
        active = false;
        startMission = false;
        control = false;
        inZone = false;
        previousDead = GameTime::Instance()->getElapsedTime().asMilliseconds();
        
        // Nouvelle vie
        if (lives > 0 && gameover() == false) {
            lives -= 1;
            lostLives += 1;
            sprite.setPosition(380, 800);
            module = 0;
            weapon = 0;
            health = 100;
            active = true;
            dead = true;
            setBullet();
        }
    }
    // Réaparition du joueur
    if (dead) {
        if (lives > 0) {
            if (!startMission)
                bulle.setPosition(sprite.getPosition().x - 25, sprite.getPosition().y - 22); // Nouvelle position du joueur

            // Déplace le joueur dans la surface de combat
            if (!inZone) {
                if (sprite.getPosition().y > 500)
                    sprite.move(0, -speed);
                else {
                    inZone = true;
                    if (startMission) {
                        control = true;
                        dead = false;
                    }

                }
            } else {
                control = true;

                if (previousDead == 0)
                    previousDead = GameTime::Instance()->getElapsedTime().asMilliseconds();

                // Protège le joueur pendant quelques secondes
                if (deadTime.asMilliseconds() < GameTime::Instance()->getElapsedTime().asMilliseconds() - previousDead) {
                    dead = false;

                }
            }
        }
    }
}

void Player::setNewCredit() {

    if (credits > 0) {
        credits -= 1;
        setLive();
        setBullet();
        active = true;
        health = 100;
        weapon = 0;
        module = 0;
        countSuperAttack = 1;
        dead = true;
        
    }
}

void Player::keyboardControl() {
    if (WindowGame::Instance()->focus) {
        if (Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed, 0);
            if (playerMove == 0 || playerMove == 2 || playerMove == 6)
                animation.currentFrame = 0;
            playerMove = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            sprite.move(+speed, 0);
            if (playerMove == 0 || playerMove == 1 || playerMove == 5)
                animation.currentFrame = 0;
            playerMove = 2;
        }

        if (playerMove == 5 || playerMove == 6) {
            playerMove = 3;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
            sprite.move(0, -speed);

        else if (Keyboard::isKeyPressed(Keyboard::Down))
            sprite.move(0, +speed);

        if (GameTime::Instance()->getElapsedTime().asMilliseconds() > 6000) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[2])) {
                if (countSuperAttack > 0) {
                    sndSuperAttack.play();
                    activeSuperAttack = true;
#ifdef _DEBUG
                    if (!unlimitedAttack)
                        countSuperAttack -= 1;
#else
                    countSuperAttack -= 1;
#endif

                }
            }
        }
    }
}

void Player::joystickControl() {

    if (GamePadManager::Instance()->gamepadConnected) {
        
        if (Joystick::getAxisPosition(0, Joystick::Y) > GamePadManager::Instance()->axisUp)
            sprite.move(0, +speed);
        
        if (Joystick::getAxisPosition(0, Joystick::Y) < GamePadManager::Instance()->axisDown)
            sprite.move(0, -speed);
        
        if (Joystick::getAxisPosition(0, Joystick::X) > GamePadManager::Instance()->axisUp) {
            sprite.move(+speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 2;
        }

        if (Joystick::getAxisPosition(0, Joystick::X) < GamePadManager::Instance()->axisDown) {
            sprite.move(-speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 1;
        }
        
        // DPAD
#if __linux
        
        if (Joystick::getAxisPosition(0, Joystick::PovY) < -70)
            sprite.move(0, -speed);
        
        if (Joystick::getAxisPosition(0, Joystick::PovY) > 70)
            sprite.move(0, +speed);
        
        if (Joystick::getAxisPosition(0, Joystick::PovX) > 1) {
            sprite.move(+speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 2;
        }

        if (Joystick::getAxisPosition(0, Joystick::PovX) < -4) {
            sprite.move(-speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 1;
        }

#elif _WIN32 || _WIN64     
        if (Joystick::getAxisPosition(0, Joystick::PovX) < -70)
            sprite.move(0, +speed);
        
        if (Joystick::getAxisPosition(0, Joystick::PovX) > 70)
            sprite.move(0, -speed);
        
        if (Joystick::getAxisPosition(0, Joystick::PovY) > 1) {
            sprite.move(+speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 2;
        }

        if (Joystick::getAxisPosition(0, Joystick::PovY) < -4) {
            sprite.move(-speed, 0);
            if (playerMove == 0)
                animation.currentFrame = 0;
            playerMove = 1;
        }

#endif
        
    if (Joystick::isButtonPressed(0,GamePadManager::Instance()->buttons[2])) {
        if (countSuperAttack > 0) {
            sndSuperAttack.play();
            activeSuperAttack = true;
#ifdef _DEBUG
            if (!unlimitedAttack)
                countSuperAttack -= 1;
#else
            countSuperAttack -= 1;
#endif
        }
    }
}
}

void Player::update() {
    liveManager();
    animation.sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    animation.update();

    animationShadow.sprite.setPosition(sprite.getPosition().x + 8, sprite.getPosition().y - 8);
    animationShadow.update();

    if (!active)
        return;
    
    // Cible
    if (target.active) {
        target.rect.setPosition((getPosition().x - 7) + (getSize().x) , (getPosition().y - 9) + (getSize().y));
        target.update();
    }
    
    if (activeSuperAttack) {
        SuperAttack.update();
        
        if (lastTime == 0)
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > SuperAttackTime.asMilliseconds()) {
            lastTime = 0;
            activeSuperAttack = false;
        }   
    }

    if (bullet == 0) {

        if (previousSetBullet == 0)
            previousSetBullet = GameTime::Instance()->getElapsedTime().asMilliseconds();


        if (30000 < GameTime::Instance()->getElapsedTime().asMilliseconds() - previousSetBullet) {
            previousSetBullet = 0;
            setBullet();

        }
    }

    

    if (module > 0)
        updateModule();

    animation.sprite.setColor(color);

    if (collision || goldCollision) {
        if (collision)
            color = Color(50, 50, 50, 150);
        else if (goldCollision)
            color = Color(255, 223, 0, 150);
        if (previousCollision == 0)
            previousCollision = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - previousCollision > 100) {
            color = Color::White;
            collision = false;
            goldCollision = false;
            previousCollision = 0;
        }
    }
    
    
    
    // rect[0] = top
    // rect[1] = left
    // rect[2] = right
    // rect[3] = bottom

    if (playerMove == 3 || playerMove == 0) {
        rect[0] = IntRect((int) sprite.getPosition().x + 16, (int) sprite.getPosition().y + 5, (int) 6, (int) 10);
        rect[3] = IntRect((int) sprite.getPosition().x + 12, (int) sprite.getPosition().y + 17, (int) 15, (int) 15);
        rect[1] = IntRect((int) sprite.getPosition().x, (int) sprite.getPosition().y + 20, (int) 10, (int) 5);
        rect[2] = IntRect((int) sprite.getPosition().x + 28, (int) sprite.getPosition().y + 20, (int) 10, (int) 5);
    }

    if (playerMove == 1 || playerMove == 5) {
        rect[0] = IntRect((int) sprite.getPosition().x + 14, (int) sprite.getPosition().y + 5, (int) 6, (int) 10);
        rect[3] = IntRect((int) sprite.getPosition().x + 12, (int) sprite.getPosition().y + 17, (int) 10, (int) 15);
        rect[1] = IntRect((int) sprite.getPosition().x + 8, (int) sprite.getPosition().y + 20, (int) 3, (int) 5);
        rect[2] = IntRect((int) sprite.getPosition().x + 24, (int) sprite.getPosition().y + 20, (int) 3, (int) 5);
    }

    if (playerMove == 2 || playerMove == 6) {
        rect[0] = IntRect((int) sprite.getPosition().x + 18, (int) sprite.getPosition().y + 5, (int) 6, (int) 10);
        rect[3] = IntRect((int) sprite.getPosition().x + 14, (int) sprite.getPosition().y + 17, (int) 10, (int) 15);
        rect[1] = IntRect((int) sprite.getPosition().x + 10, (int) sprite.getPosition().y + 20, (int) 3, (int) 5);
        rect[2] = IntRect((int) sprite.getPosition().x + 28, (int) sprite.getPosition().y + 20, (int) 3, (int) 5);
    }
#ifdef _DEBUG
    if (showRectangle) {
        
        for (unsigned char i = 0; i < 4; i++) {
            
            rectShape[i].setSize(Vector2f(rect[i].width, rect[i].height));
            rectShape[i].setPosition(rect[i].left, rect[i].top);
        }
    }
#endif

    if (control) {
        
        joystickControl();
        keyboardControl();
        // Limitatoin de la zone de combat
        if (sprite.getPosition().x < limitLeft)
            sprite.setPosition(limitLeft, sprite.getPosition().y);
        if (sprite.getPosition().x > limitRight)
            sprite.setPosition(limitRight, sprite.getPosition().y);
        if (sprite.getPosition().y < limitUp)
            sprite.setPosition(sprite.getPosition().x, limitUp);
        if (sprite.getPosition().y > limitDown + sprite.getTexture()->getSize().y)
            sprite.setPosition(sprite.getPosition().x, limitDown + sprite.getTexture()->getSize().y);
    }


    if (playerMove == 3) {
        animation.sprite.setTexture(FileManager::Instance()->player[0]);
        animation.currentFrame = 0;
        animation.frameCount = 4;
        animationShadow.frameCount = 4;
        animation.looping = true;
        setFrame = false;
        // Ombrage

        animationShadow.sprite.setTexture(FileManager::Instance()->player[0]);
        animationShadow.currentFrame = 0;
        animationShadow.looping = true;

        playerMove = 0;
    }

    if (playerMove == 1) {
        animation.frameCount = 3;
        animationShadow.frameCount = 3;
        animation.looping = false;
        animation.sprite.setTexture(FileManager::Instance()->player[1]);
        
        
        // Ombrage
        animationShadow.sprite.setTexture(FileManager::Instance()->player[1]);
        animationShadow.looping = false;

        playerMove = 5;
    }

    if (playerMove == 2) {
        animation.frameCount = 3;
        animationShadow.frameCount = 3;
        animation.looping = false;
        animation.sprite.setTexture(FileManager::Instance()->player[2]);
        
    
        // Ombrage
        animationShadow.sprite.setTexture(FileManager::Instance()->player[2]);
        animationShadow.looping = false;
        playerMove = 6;
    }


}

void Player::updateModule() {


    if (moduleClock.getElapsedTime().asMilliseconds() - lastModule > moduleTime.asMilliseconds()) {
        module -= 1;
        lastModule += moduleClock.restart().asMilliseconds();
    }


    if (module >= 0) {
        modules[0].setPosition(sprite.getPosition().x - 20, sprite.getPosition().y);
        shadowModules[0].setPosition(modules[0].getPosition().x + 8, modules[0].getPosition().y - 5);

    }

    if (module == 2) {
        modules[1].setPosition(sprite.getPosition().x + 42, sprite.getPosition().y);
        shadowModules[1].setPosition(modules[0].getPosition().x + 8, modules[1].getPosition().y - 5);
    }
}

void Player::setLive() {
    int countLive;

    if (gameDifficulty == 0)
        countLive = 3;

    if (gameDifficulty == 1)
        countLive = 4;

    if (gameDifficulty == 2)
        countLive = 5;

    lives = countLive;

    sprite.setPosition(380, 800);
    active = true;

}

void Player::setBullet() {

    if (gameDifficulty == 0)
        bullet = 30;
    if (gameDifficulty == 1)
        bullet = 40;
    if (gameDifficulty == 2)
        bullet = 50;

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {
        target.draw(animationShadow, states);
        target.draw(animation, states);

        if (module >= 1) {
            target.draw(shadowModules[0], states);
            target.draw(modules[0], states);
        }
        if (module == 2) {
            target.draw(shadowModules[1], states);
            target.draw(modules[1], states);
        }


        if (dead && lives > 0) {
            if (!startMission)
                target.draw(bulle, states);
        }
        
        if (this->target.active)
            target.draw(this->target, states);
            
#ifdef _DEBUG
        if (showRectangle) {
            for (unsigned char i = 0; i < 4; i++)
                target.draw(rectShape[i], states);
        }
#endif
    }
}

Player::SuperAttack::SuperAttack() {
    time = sf::milliseconds(50);
    flasher.setPosition(160,0);
    flasher.setSize(Vector2f(480,600));
    rectangle = IntRect(160,0,480,600);
    initialize();
}

void Player::SuperAttack::initialize() {
    flasher.setFillColor(sf::Color(0,0,0,155));
    lastTime = 0;
    active = true;
}

void Player::SuperAttack::update() {
   
    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {
        if (active) {
            flasher.setFillColor(sf::Color(255,255,255,0));
            active = false;
        } else if (!active) {
            flasher.setFillColor(sf::Color(255,255,255,155));
            active = true;
        }
        lastTime = 0;
    } 
}

void Player::SuperAttack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active)
    target.draw(flasher, states);
}

Player::Target::Target() {
    lastTime = 0;
    count = 0;
    trans = 0;
    active = false;
    
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(3);
    rect.setSize(Vector2f(20,20));
}

void Player::Target::update() {
    if (active) {
        
        if (lastTime == 0)
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 50) {
            if (count == 0) {
                if (trans != 155)
                    trans = 155;
                else count = 1;
            } else if (count == 1) {
                if (trans != 0)
                    trans = 0 ;
                else count = 0;
            }
            rect.setOutlineColor(sf::Color(236, 13, 13, trans));
            lastTime = 0;
        }
    }
}

void Player::Target::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {
        target.draw(rect, states);
    }
}

