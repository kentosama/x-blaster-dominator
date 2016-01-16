/* 
 * File:   Enemy.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 3 mars 2013, 21:42
 */

#include "Enemy.h"

Enemy::Enemy(Vector2f position, unsigned char enemyType, float startTime, bool stop, float stopPosition, float stopTime, unsigned char movement, bool fire, bool powerUp) {
    lastShot = 0;
    if (enemyType == 8)
        frameCount = 6;
    else if (enemyType == 9)
        frameCount = 4;
    else frameCount = 3;
    sprite.setTexture(FileManager::Instance()->enemies[enemyType]);
    scale = Vector2f(1.2f, 1.2f);


    // Attribution de la direction du mouvement
    if (movement == 1 || movement == 3)
        directionLeft = true;
    else if (movement == 2 || movement == 4)
        directionRight = true;

    // Attribution de la rotation
    if (enemyType == 12) {
        if (movement == 8)
        rotation = -180.0f;
        else rotation = 0.0f;
    } else {
        if (movement == 6)
            rotation = -65.0f;
        else if (movement == 7)
            rotation = 65.0f;
        else if (movement == 8 || movement == 10)
            rotation = -90.0f;
        else if (movement == 9 || movement == 11)
            rotation = 90.0f;
        else rotation = 0.0f;
    } 

    origin = setOrigin();
    sprite.setOrigin(origin);
    sprite.setScale(scale);
    
#ifdef _DEBUG
    rectOrigin.setFillColor(sf::Color::Red);
    rectOrigin.setSize(Vector2f(2, 2));
    rectOrigin.setPosition(position);
#endif

    collision = false;
    previousCollision = 0;
    count = 0;
    this->enemyType = enemyType;
    position.x += 160 + getSize().x / 2;
    position.y -= 30;

    this->position = position;
    sprite.setPosition(position);

    this->startTime = startTime + GameTime::Instance()->getElapsedTime().asMilliseconds();
    this->stop = stop;
    this->stopPosition = stopPosition;
    this->stopTime = stopTime;
    this->movement = movement;
    this->fire = fire;
    this->powerUp = powerUp;
    
    rect.reserve(3);
    for (unsigned char i = 0; i < 3; i++)
        rect.emplace_back();
    
#ifdef _DEBUG
    showRectangle = false;
    rectShape.reserve(3);
    for (unsigned char i = 0; i < 3; i++)
        rectShape.emplace_back();
    
    rectShape[0].setFillColor(sf::Color::Red);
    rectShape[1].setFillColor(sf::Color::Blue);
    rectShape[2].setFillColor(sf::Color::Yellow);
#endif
    
    
    sprite.setRotation(rotation);

    initialize();

}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
}

Vector2f Enemy::getPosition() {

    return Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

Vector2f Enemy::setOrigin() {
    return Vector2f((sprite.getGlobalBounds().width / frameCount) / 2, sprite.getGlobalBounds().height / 2);
}

Vector2f Enemy::getOrigin() {
    return sprite.getOrigin();
}

Vector2f Enemy::getSize() {
    return Vector2f((sprite.getTexture()->getSize().x / frameCount), sprite.getTexture()->getSize().y);
}

float Enemy::getRotation() {
    return rotation;
}

void Enemy::initialize() {

    if (enemyType == 0 || (enemyType > 0 && enemyType < 3)) // Type : A
    {
        speed = 2;
        health = 15;
        damage = 15;

        if (enemyType == 0)
            score = 100;
        else if (enemyType == 1)
            score = 700;
        else if (enemyType == 2)
            score = 900;
    } else if (enemyType > 2 && enemyType < 6) // Type : B
    {
        speed = 1.5;
        if (enemyType == 3) {
            shotTime = sf::seconds(2);
            health = 50;
            damage = 50;
            score = 1200;
        } else if (enemyType == 4) {
            shotTime = sf::seconds(1.5);
            health = 100;
            damage = 80;
            score = 2200;
        } else if (enemyType == 5) {
            shotTime = sf::seconds(1);
            health = 120;
            damage = 100;
            score = 2800;
        }
    } else if (enemyType == 6) { // Type : C
        speed = 1.5f;
        shotTime = sf::seconds(0.9f);
        health = 120;
        damage = 100;
        score = 3000;
    } else if (enemyType == 7) { // Type : D
        speed = 1.3f;
        shotTime = sf::seconds(1.5f);
        health = 100;
        damage = 100;
        score = 2200;
    } else if (enemyType == 8) { // Type : E
        speed = 1.5f;
        shotTime = sf::seconds(1.0f);
        health = 80;
        damage = 25;
        score = 1800;
    } else if (enemyType == 9) { // Type : F
        speed = 1.7;
        shotTime = sf::seconds(1.2f);
        health = 65;
        damage = 35;
        score = 2500;
    } else if (enemyType == 10) { // Type : G
        speed = 1.3f;
        shotTime = sf::seconds(1.0f);
        health = 120;
        damage = 100;
        score = 3000;
    } else if (enemyType == 11) { // Type : H
        speed = 2.8f;
        shotTime = sf::seconds(0.5f);
        health = 15;
        damage = 25;
        score = 1300;
    } else if (enemyType == 12) { // Type : I
        speed = 1.4f;
        shotTime = sf::seconds(1.5f);
        health = 15;
        damage = 25;
        score = 1500;
    } else if (enemyType == 13) { // Type : J
        speed = 1.3f;
        shotTime = sf::seconds(1.5f);
        health = 200;
        damage = 100;
        score = 4200;
    } else if (enemyType == 14) { // Type : K (protor)
        speed = 1.3f;
        shotTime = sf::seconds(1.2f);
        health = 400;
        damage = 100;
        score = 5800;
    } else if (enemyType == 15) { // Type : L
        speed = 1.3f;
        shotTime = sf::seconds(1.2f);
        health = 500;
        damage = 100;
        score = 6500;
    }

    animation.initialize(sprite, position, getSize().x, getSize().y, frameCount, 0, 100, Color::White, scale, true, rotation, getOrigin(), false);

    animation_shadow = animation;
    animation_shadow.sprite.setColor(Color(50, 50, 50, 50));
    lastSpeed = speed;
}

void Enemy::movementManager() {
    speed = 0;
    if (!restartClock) {
        pauseClock.restart();
        restartClock = true;
    } else {

    if (movement == 1 || movement == 2) {
        if (directionLeft)
            sprite.move(-2, 0);
        else if (directionRight)
            sprite.move(+2, 0);
        
        if (sprite.getPosition().x < 160 + getSize().x / 2) {
            directionLeft = false;
            directionRight = true;
        } else if (sprite.getPosition().x > 600 + getSize().x / 2) {
            directionLeft = true;
            directionRight = false;
        }
    }

    else if (movement == 3 || 4) {

        if (directionLeft) {
            sprite.move(-3, 0);

            if (sprite.getPosition().x < 140 + getSize().x / 2) {
                sprite.setPosition(640, sprite.getPosition().y);
            }
        }

        if (directionRight) {
            sprite.move(+3, 0);
            if (sprite.getPosition().x > 620 + getSize().x / 2) {
                sprite.setPosition(120, sprite.getPosition().y);
            }
        }
    }

        if (stopTime < pauseClock.getElapsedTime().asMilliseconds()) {
            if (sprite.getPosition().x < 160 + getSize().x / 2)
                sprite.setPosition(160, sprite.getPosition().y);
            if (sprite.getPosition().x > 620 + getSize().x / 2)
                sprite.setPosition(600, sprite.getPosition().y);

            stop = false;
            speed = lastSpeed;
        }
    }
}

void Enemy::update() {
    animation.sprite.setPosition(getPosition().x, getPosition().y);
    animation.sprite.setRotation(sprite.getRotation());
    animation_shadow.sprite.setPosition(getPosition().x + 5, getPosition().y + 10);
    animation_shadow.sprite.setRotation(sprite.getRotation());
    animation.update();
    animation_shadow.update();

    if (active) {
        animation.sprite.setColor(color);

#ifdef _DEBUG
        rectOrigin.setPosition(getPosition()); // Affiche le centre de l'appaeil
#endif

        if (enemyType == 6 || enemyType == 10) {
            if (count > 2)
                count = 0;
        } else if (enemyType == 15) {
            if(count > 4)
                count = 0;
        }

        if (collision) {
            color = Color(50, 50, 50, 150);


            if (previousCollision == 0)
                previousCollision = GameTime::Instance()->getElapsedTime().asMilliseconds();

            else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - previousCollision > 100) {
                color = Color::White;
                collision = false;
                previousCollision = 0;
            }
        }

        if (enemyType == 0 || enemyType == 1 || enemyType == 2) {
            rect[0] = IntRect((int) sprite.getPosition().x - 2, (int) sprite.getPosition().y + 6.5, (int) 4, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 20);
            rect[1] = IntRect((int) sprite.getPosition().x - 17, (int) sprite.getPosition().y - 10, (int) 34, (int) 10);
        } else if (enemyType == 3 || enemyType == 4 || enemyType == 5) {
            rect[0] = IntRect((int) sprite.getPosition().x - 5, (int) sprite.getPosition().y + 6, (int) 9, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 10, (int) sprite.getPosition().y - 15, (int) 18, (int) 20);
            rect[1] = IntRect((int) sprite.getPosition().x - 17, (int) sprite.getPosition().y - 20, (int) 34, (int) 10);
        } else if (enemyType == 6) {
            rect[0] = IntRect((int) sprite.getPosition().x - 4, (int) sprite.getPosition().y + 6.5, (int) 8, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 20);
            rect[1] = IntRect((int) sprite.getPosition().x - 14, (int) sprite.getPosition().y - 10, (int) 30, (int) 10);
        }
        else if (enemyType == 7) {
            rect[0] = IntRect((int) sprite.getPosition().x - 2, (int) sprite.getPosition().y + 6.5, (int) 4, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 12, (int) sprite.getPosition().y - 15, (int) 24, (int) 25);
            rect[1] = IntRect((int) sprite.getPosition().x - 16, (int) sprite.getPosition().y - 10, (int) 34, (int) 5);
        } else if (enemyType == 8) {
            rect[0] = IntRect((int) sprite.getPosition().x - 2, (int) sprite.getPosition().y + 6.5, (int) 4, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 20);
            rect[1] = IntRect((int) sprite.getPosition().x - 17, (int) sprite.getPosition().y - 10, (int) 34, (int) 10);
        } else if (enemyType == 9) {
            rect[0] = IntRect((int) sprite.getPosition().x - 2, (int) sprite.getPosition().y - 6.5, (int) 4, (int) 20);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 12);
            rect[1] = IntRect((int) sprite.getPosition().x - 14, (int) sprite.getPosition().y - 14, (int) 28, (int) 5);
        } else if (enemyType == 10) {
            rect[0] = IntRect((int) sprite.getPosition().x - 5, (int) sprite.getPosition().y, (int) 10, (int) 16);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 12);
            rect[1] = IntRect((int) sprite.getPosition().x - 10, (int) sprite.getPosition().y - 10, (int) 23, (int) 20);
        } else if (enemyType == 11) {
            rect[0] = IntRect((int) sprite.getPosition().x - 2, (int) sprite.getPosition().y, (int) 4, (int) 25);
            rect[2] = IntRect((int) sprite.getPosition().x - 11, (int) sprite.getPosition().y - 15, (int) 22, (int) 12);
            rect[1] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 10, (int) 17, (int) 22);
        } else if (enemyType == 12) {
            if (movement == 8) {
                rect[0] = IntRect((int) sprite.getPosition().x -8, (int) sprite.getPosition().y -15, (int) 16, (int) 30);
            } else {
                rect[0] = IntRect((int) sprite.getPosition().x -5, (int) sprite.getPosition().y - 15, (int) 16, (int) 30);
            }
        } else if (enemyType == 13) {
            rect[0] = IntRect((int) sprite.getPosition().x - 5, (int) sprite.getPosition().y + 6.5, (int) 10, (int) 13);
            rect[2] = IntRect((int) sprite.getPosition().x - 9, (int) sprite.getPosition().y - 15, (int) 18, (int) 20);
            rect[1] = IntRect((int) sprite.getPosition().x - 17, (int) sprite.getPosition().y - 10, (int) 34, (int) 20);
        } else if (enemyType == 14) {
            rect[0] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y, (int) getSize().x, (int) getSize().y / 3);
            rect[1] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y - rect[0].height, (int) getSize().x, (int) getSize().y / 3);
            rect[2] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y - (rect[0].height * 2), (int) getSize().x, (int) getSize().y / 3);
        } else if (enemyType == 15) {
            rect[0] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y, (int) getSize().x, (int) getSize().y / 3);
            rect[1] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y - rect[0].height, (int) getSize().x, (int) getSize().y / 3);
            rect[2] = IntRect((int) sprite.getPosition().x - getSize().x / 2, (int) sprite.getPosition().y - (rect[0].height * 2), (int) getSize().x, (int) getSize().y / 3);
        }

#ifdef _DEBUG
        if (showRectangle) {
            for (unsigned char i = 0; i < 3; i++) {
                rectShape[i].setSize(Vector2f(rect[i].width, rect[i].height));
                rectShape[i].setPosition(rect[i].left, rect[i].top);
            }
        }
#endif

        // Gestion des déplacements 
        if (startTime < GameTime::Instance()->getElapsedTime().asMilliseconds()) {

            if (stop && movement == 8 && sprite.getPosition().x >= stopPosition + 160 ||
                    stop && movement == 9 && sprite.getPosition().x <= stopPosition ||
                    stop && movement < 6 && sprite.getPosition().y >= stopPosition) {
                movementManager();
            } else if (movement < 6)
                sprite.move(0, +speed);
            else if (movement == 6)
                sprite.move(+3, +speed);
            else if (movement == 7)
                sprite.move(-3, +speed);
            else if (movement == 8)
                sprite.move(+speed, 0);
            else if (movement == 9)
                sprite.move(-speed, 0);
            else if (movement == 10) {
                if (getRotation() == -90)
                sprite.move(+speed, 0);
                if (sprite.getPosition().x > 350) {
                    if (sprite.getRotation() != 0.0f)
                        sprite.rotate(+5.0f);
                    else { 
                        fire = true;
                        movement = 0;
                    }
                }
            } else if (movement == 11) {
                if (getRotation() == 90)
                sprite.move(-speed, 0);
                if (sprite.getPosition().x < 480) {
                    if (sprite.getRotation() != 0.0f)
                        sprite.rotate(-5.0f);
                    else { 
                        movement = 0;
                        fire = true;
                    }
                }
            }
        }

        if (sprite.getPosition().y > 600 + getSize().y / 2)
            active = false;
        else if (movement == 8 || movement == 6) {
            if (getPosition().x > 640 + getSize().x / 2)
                active = false;
        } else if (movement == 9 || movement == 7) {
            if (getPosition().x < 100 + getSize().x / 2)
                active = false;
        }
    } else return;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {
        target.draw(animation_shadow, states);
        target.draw(animation, states);
#ifdef _DEBUG
        if (showRectangle) {
            for (unsigned char i = 0; i < 3; i++)
                target.draw(rectShape[i], states);
            target.draw(rectOrigin, states);
        }
        
#endif

    }
}

