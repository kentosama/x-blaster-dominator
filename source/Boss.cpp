/* 
 * File:   Boss.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 26 mars 2013, 09:21
 */

#include "Boss.h"

Boss::Boss(const unsigned char stage, Vector2f position, float time) {
    gameDifficulty = Profil::Instance()->mode;
    if (stage != 2)
        frameCount = 4;
    else frameCount = 7;

    if (stage == 1)
        frameLine = 3;
    else if (stage == 2 || stage == 3)
        frameLine = 2;
    else if (stage == 4)
        frameLine = 4;


    this->stage = stage;
    position.x += 160;
    this->position = position;
    startTime = 0;
    unsigned char countHealth = 0;
    unsigned char countRect = 0;
    if (stage == 1 || stage == 2) {
        countHealth = 3;
        countRect = 6;
    } else {
        countHealth = 1;
        countRect = 4;
    }
    health.reserve(countHealth);
    energy.reserve(10);
    int e_position = 160 + 145;
    for (unsigned char i = 0; i < 10; i++) {
        energy.emplace_back();
        energy[i].setTexture(FileManager::Instance()->items[7]);
        energy[i].setPosition(e_position, 10);
        energy[i].setScale(1.5, 1.5);
        e_position += 20;
    }
    portionEnergy = 0;
    rect.reserve(6);
    color.reserve(3);
    collision.reserve(6);
    lastTime.reserve(2);
    lastCollision = 0;
    modeShotA = 0;
    modeShotB = 0;
    activeCanonA = true;
    activeCanonB = true;
    activeShotA = false;
    activeShotB = false;
    activeMovement = false;
    activeTarget = false;
    activeWave = false;
    activeDead = false;
    lastEvent = 0;
    countEvent = 0;
    currentWave = 0;
    trans = 255;
    lastTrans = 0;
    lastDead = 0;
    countTrans = 0;
    deadTime = sf::seconds(10);

#ifdef _DEBUG
    rectShape.reserve(6);
    for (unsigned char i = 0; i < 6; i++) {
        rectShape.emplace_back();
        rectShape[i].setOutlineColor(sf::Color::White);
    }

    rectShape[0].setFillColor(sf::Color::Red);
    rectShape[1].setFillColor(sf::Color::Blue);
    rectShape[2].setFillColor(sf::Color::Blue);
    rectShape[3].setFillColor(sf::Color::Red);
    rectShape[4].setFillColor(sf::Color::Yellow);
    rectShape[5].setFillColor(sf::Color::Yellow);

    rectOrigin.setFillColor(sf::Color::White);
    rectOrigin.setSize(Vector2f(10, 10));
#endif

    startTime = time + GameTime::Instance()->getElapsedTime().asMilliseconds();
    for (unsigned char i = 0; i < 6; i++) {
        if (i < 3)
            color.emplace_back();

        if (i < countHealth) {
            health.emplace_back();
            health[i] = 0;
        }
        if (i < countRect)
            rect.emplace_back();

        collision.emplace_back();
        collision[i] = 0;
    }

    color[0] = Color::White;
    color[1] = Color(50, 50, 50, 150);
    color[2] = Color(255, 69, 0, 150);

    for (unsigned char i = 0; i < 2; i++) {
        lastTime.emplace_back();
        lastTime[i] = 0;
    }

    destroyed = false;
    active = true;
    inZone = false;
    sprite.setTexture(FileManager::Instance()->boss[stage - 1]);

    sprite.setOrigin(setOrigin());
    sprite.setPosition(position);
    sprite.setScale(2.2, 2.2);

    if (stage == 1) {
        speed = 2.5;
        lastShotA = 0;
        lastShotB = 0;
        leftMovement = true;
        rightMovement = false;
        if (gameDifficulty == 2) {
            health[0] = 10000;
            health[1] = 2000;
            health[2] = 2000;
            shotTimeA = sf::seconds(0.9);
            shotTimeB = sf::seconds(1.2);
        } else if (gameDifficulty == 1) {
            health[0] = 15000;
            health[1] = 2000;
            health[2] = 2000;
            shotTimeA = sf::seconds(0.8);
            shotTimeB = sf::seconds(1);
        } else if (gameDifficulty == 0) {
            health[0] = 18000;
            health[1] = 4000;
            health[2] = 4000;
            shotTimeA = sf::seconds(0.7);
            shotTimeB = sf::seconds(0.9);
        }
    } else if (stage == 2) {
        speed = 2.8;
        lastShotA = 0;
        lastShotB = 0;
        leftMovement = true;
        rightMovement = false;
        if (gameDifficulty == 2) {
            health[0] = 15000;
            health[1] = 2000;
            health[2] = 2000;
            shotTimeA = sf::seconds(0.2);
            shotTimeB = sf::seconds(1.7);
        } else if (gameDifficulty == 1) {
            health[0] = 15000;
            health[1] = 2000;
            health[2] = 2000;
            shotTimeA = sf::seconds(0.2);
            shotTimeB = sf::seconds(1.9);
        } else if (gameDifficulty == 0) {
            health[0] = 18000;
            health[1] = 4000;
            health[2] = 4000;
            shotTimeA = sf::seconds(0.2);
            shotTimeB = sf::seconds(2.2);
        }
    } else if (stage == 3) {
        speed = 2.8;
        lastShotA = 0;
        lastShotB = 0;
        leftMovement = true;
        rightMovement = false;
        if (gameDifficulty == 2) {
            health[0] = 18000;
            shotTimeA = sf::seconds(0.8);
            shotTimeB = sf::seconds(1.2);
        } else if (gameDifficulty == 1) {
            health[0] = 22000;
            shotTimeA = sf::seconds(0.7);
            shotTimeB = sf::seconds(1.1);
        } else if (gameDifficulty == 0) {
            health[0] = 25000;
            shotTimeA = sf::seconds(0.6);
            shotTimeB = sf::seconds(0.9);
        }
    } else if (stage == 4) {
        speed = 1.5;
        lastShotA = 0;
        lastShotB = 0;
        leftMovement = true;
        rightMovement = false;
        if (gameDifficulty == 2) {
            health[0] = 25000;
            shotTimeA = sf::seconds(1.3);
            shotTimeB = sf::seconds(1.7);
        } else if (gameDifficulty == 1) {
            health[0] = 28000;
            shotTimeA = sf::seconds(1.6);
            shotTimeB = sf::seconds(1.9);
        } else if (gameDifficulty == 0) {
            health[0] = 32000;
            shotTimeA = sf::seconds(1.8);
            shotTimeB = sf::seconds(2.2);
        }
    }
    energyfix = health[0];
    portionEnergy = (energyfix * 100) / health[0];
    portionEnergy = portionEnergy / 10;
    countFire = 0;
    animation.initialize(sprite, getPosition(), getSize().x, getSize().y, frameCount, frameLine, 100, sf::Color::White, sprite.getScale(), true, 0, Vector2f(0, 0), false);
    shadow = animation;
    shadow.sprite.setColor(Color(50, 50, 50, 50));
}

Boss::Boss(const Boss& orig) {
}

Boss::~Boss() {
}

Vector2f Boss::setOrigin() {
    return Vector2f(getSize().x / 2, getSize().y / 2);
}

Vector2f Boss::getSize() {
    return Vector2f(sprite.getTexture()->getSize().x / frameCount, sprite.getTexture()->getSize().y / frameLine);
}

Vector2f Boss::getPosition() {
    return sprite.getPosition();
}

unsigned char Boss::getCurrentFrame() {
    return animation.currentFrame;
}

unsigned char Boss::getCurrentFrameLine() {
    return animation.currentFrameLine;
}

void Boss::initialize(const unsigned char stage) {

}

void Boss::update() {
    if (active) {
        animation.sprite.setPosition(getPosition().x, getPosition().y);
        shadow.sprite.setPosition(getPosition().x, getPosition().y + 10);
        animation.update();
        shadow.update();

        movementManager();
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() > startTime) {
            if (sprite.getPosition().y < 200 && !activeMovement)
                sprite.move(0, speed);
            else if (!inZone)
                inZone = true;
            else if (!activeDead) {

                // rect[0] = partie centrale
                // rect[1] = partie arrière
                // rect[2] = partie du bas gauche
                // rect[3] = partie du bas droite
                // rect[4] = canon gauche
                // rect[5] = canon droit

                scenario(stage);

                if (stage == 1) {
                    rect[0] = IntRect((int) sprite.getPosition().x - (getSize().x / 2) - 20, (int) (sprite.getPosition().y - (getSize().y / 2)), (int) 175, (int) 50);
                    rect[1] = IntRect((int) sprite.getPosition().x - (getSize().x / 2) - 20, (int) (sprite.getPosition().y - (getSize().y / 2) - 40), (int) 175, (int) 30);
                    rect[2] = IntRect((int) sprite.getPosition().x - (getSize().x / 2) - 20, (int) sprite.getPosition().y + 15, (int) 64, (int) 50);
                    rect[3] = IntRect((int) sprite.getPosition().x + 24, (int) sprite.getPosition().y + 15, (int) 64, (int) 50);
                    rect[4] = IntRect((int) sprite.getPosition().x - (getSize().x / 2) - 60, (int) (sprite.getPosition().y - (getSize().y / 2) - 20), (int) 40, (int) 100);
                    rect[5] = IntRect((int) sprite.getPosition().x + 88, (int) (sprite.getPosition().y - (getSize().y / 2) - 20), (int) 40, (int) 100);
                } else if (stage == 2) {
                    rect[0] = IntRect((int) sprite.getPosition().x - 39, (int) sprite.getPosition().y - 70, (int) 80, (int) 130);
                    rect[1] = IntRect((int) sprite.getPosition().x - 30, (int) sprite.getPosition().y + 60, (int) 60, (int) 10);
                    rect[2] = IntRect((int) sprite.getPosition().x - 90, (int) sprite.getPosition().y - 55, (int) 60, (int) 70);
                    rect[3] = IntRect((int) sprite.getPosition().x + 30, (int) sprite.getPosition().y - 55, (int) 60, (int) 70);
                    rect[4] = IntRect((int) sprite.getPosition().x - 107, (int) sprite.getPosition().y - 20, (int) 45, (int) 80);
                    rect[5] = IntRect((int) sprite.getPosition().x + 63, (int) sprite.getPosition().y - 20, (int) 45, (int) 80);
                } else if (stage == 3) {
                    rect[0] = IntRect((int) sprite.getPosition().x - 150, (int) sprite.getPosition().y - 70, (int) 300, (int) 140);
                    rect[1] = IntRect((int) sprite.getPosition().x - 5, (int) sprite.getPosition().y + 40, (int) 20, (int) 70);
                    rect[2] = IntRect((int) sprite.getPosition().x - 180, (int) sprite.getPosition().y + 10, (int) 35, (int) 55);
                    rect[3] = IntRect((int) sprite.getPosition().x + 150, (int) sprite.getPosition().y + 10, (int) 35, (int) 55);

                } else if (stage == 4) {

                }

                // Changement des couleurs selon la collision

                for (unsigned char i = 0; i < 6; i++) {
                    if (collision[i] == 1) {
                        if (lastCollision == 0)
                            lastCollision = GameTime::Instance()->getElapsedTime().asMilliseconds();

                        if (i < 4)
                            sprite.setColor(color[1]);
                        else if (i > 3)
                            sprite.setColor(color[2]);

                        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastCollision > 100) {
                            sprite.setColor(color[0]);
                            collision[i] = 0;
                            lastCollision = 0;
                        }
                    }
                }

                if (stage == 1 || stage == 2) {
                    for (unsigned char i = 0; i < 3; i++) {

                        if (health[i] < 0) {
                            health[i] = 0;

                        }
                    }

                    if (!activeCanonA) {
                        if (lastTimeA == 0)
                            lastTimeA = GameTime::Instance()->getElapsedTime().asMilliseconds();
                        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTimeA > 10000) {
                            if (gameDifficulty == 2)
                                health[1] = 1000;
                            else if (gameDifficulty == 1)
                                health[1] = 2000;
                            else if (gameDifficulty == 2)
                                health[1] = 3000;

                            activeCanonA = true;
                            lastTimeA = 0;
                        }
                    }

                    if (!activeCanonB) {
                        if (lastTimeB == 0)
                            lastTimeB = GameTime::Instance()->getElapsedTime().asMilliseconds();
                        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTimeB > 10000) {
                            if (gameDifficulty == 2)
                                health[2] = 1000;
                            else if (gameDifficulty == 1)
                                health[2] = 2000;
                            else if (gameDifficulty == 2)
                                health[2] = 3000;
                            activeCanonB = true;
                            lastTimeB = 0;
                        }
                    }
                }

#ifdef _DEBUG
                if (showRectangle)
                    for (unsigned char i = 0; i < 6; i++) {
                        rectShape[i].setPosition(rect[i].left, rect[i].top);
                        rectShape[i].setSize(Vector2f(rect[i].width, rect[i].height));
                    }

                rectOrigin.setPosition(getPosition());

#endif
            }
        }

        if (health[0] <= 0)
            dead();
        else {
            portionEnergy = (health[0] * 100) / energyfix;
            portionEnergy = portionEnergy / 10;
            if (portionEnergy < 1)
                portionEnergy = 1;

        }
    }

    redShape.update();
    animation.sprite.setColor(sprite.getColor());
}

void Boss::movementManager() {
    if (activeMovement) {

        if (movement == 0) {

            if (leftMovement)
                sprite.move(-speed, 0);
            else if (rightMovement)
                sprite.move(speed, 0);

            if (getPosition().x < 160 + getSize().x) {
                leftMovement = false;
                rightMovement = true;
            } else if (getPosition().x > 580 - getSize().x / 2) {
                leftMovement = true;
                rightMovement = false;
            }
        } else if (movement == 1) {

            if (getPosition().y > 100 + getSize().y / 2) {
                sprite.move(0, -speed);
            }

        }
    } else if (getPosition().x < position.x)
        sprite.move(speed, 0);
    else if (getPosition().x > position.x)
        sprite.move(-speed, 0);
}

void Boss::scenario(const unsigned char stage) {

    if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastEvent > 5000) {
        lastEvent = GameTime::Instance()->getElapsedTime().asMilliseconds();
        if (countEvent < 8)
            countEvent += 1;
        else countEvent = 1;

    }

    if (stage == 1 || stage == 2) {
        if (countEvent == 1) {
            modeShotA = 0;
            modeShotB = 0;
            if (stage == 2)
                shotTimeA = sf::seconds(0.2);
            activeShotA = true;
            activeShotB = true;
            activeMovement = false;
            activeWave = false;
        } else if (countEvent == 2) {
            activeShotA = false;
            activeShotB = false;
            if (!activeWave) {
                currentWave = 1;
                activeWave = true;
            }
        } else if (countEvent == 3) {
            modeShotA = 1;
            modeShotB = 1;
            if (stage == 2)
                shotTimeA = sf::seconds(0.6);
            activeShotA = true;
            activeShotB = true;
            currentWave = 0;
            activeWave = false;
        } else if (countEvent == 4) {
            activeShotA = false;
            activeShotB = false;
            if (stage == 2)
                shotTimeA = sf::seconds(0.2);
            if (!activeWave) {
                currentWave = 2;
                activeWave = true;
            }
        } else if (countEvent == 5) {
            modeShotA = 0;
            modeShotB = 0;
            activeShotA = true;
            activeShotB = true;
            activeMovement = true;
            movement = 0;
        } else if (countEvent == 6) {
            activeShotA = false;
            activeShotB = false;
            activeMovement = false;
            if (!activeWave) {
                currentWave = 1;
                activeWave = true;
            }
        } else if (countEvent == 7) {
            modeShotA = 1;
            modeShotB = 1;
            if (stage == 2)
                shotTimeA = sf::seconds(0.6);
            activeShotA = true;
            activeShotB = true;
            activeMovement = true;
            movement = 1;
        }

    } else if (stage == 3) {
        if (countEvent == 1) {
            modeShotA = 0;
            modeShotB = 0;
            activeShotA = true;
            activeShotB = true;
            activeMovement = false;
            activeWave = false;
        } else if (countEvent == 2) {
            modeShotA = 1;
            modeShotB = 1;
            shotTimeA = sf::seconds(0.5f);
            activeShotA = false;
            activeShotB = false;
            activeWave = true;
        } else if (countEvent == 3) {
            activeShotA = true;
            activeShotB = true;
        } else if (countEvent == 4) {
            activeShotA = false;
            activeShotB = false;
            modeShotA = 2;
            modeShotB = 2;
            shotTimeA = sf::seconds(1.0f);
            shotTimeB = sf::seconds(0.7f);
        } else if (countEvent == 5) {
            activeShotA = true;
            activeShotB = true;
            activeWave = false;
        } else if (countEvent == 6) {
            modeShotA = 0;
            modeShotB = 0;
            shotTimeA = sf::seconds(0.3f);
            shotTimeB = sf::seconds(1.0f);
        } else if (countEvent == 7) {
            activeShotA = true;
            activeShotB = true;
            modeShotA = 3;
            modeShotB = 3;
        }
    }
}

void Boss::dead() {
    if (!activeDead) {
        activeShotA = false;
        activeShotB = false;
        activeCanonA = false;
        activeCanonB = false;
        activeMovement = false;
        activeDead = true;
    }

    if (lastDead == 0)
        lastDead = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastDead > deadTime.asMilliseconds()) {
        destroyed = true;
    } else {
        if (lastTrans == 0)
            lastTrans = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTrans > 10) {
            if (countTrans == 0) {
                if (trans != 125)
                    trans += 5;
                else countTrans = 1;

            } else if (countTrans == 1) {
                if (trans != 155)
                    trans -= 5;
                else countTrans = 0;
            }
            sprite.setColor(sf::Color(236, 13, 13, trans));
        }
    }
}

void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {

        if (health[0] > 0 && inZone) {
            for (unsigned char i = 0; i < portionEnergy; i++) {
                target.draw(energy[i], states);
            }
        }
        target.draw(shadow, states);
        target.draw(animation, states);


#ifdef _DEBUG
        if (showRectangle) {
            for (unsigned char i = 0; i < 6; i++)
                target.draw(rectShape[i], states);
            target.draw(rectOrigin, states);
        }
#endif
    }
}

Boss::RedShape::RedShape() {
    trans = 0;
    count = 0;
    lastTime = 0;
    rect.setFillColor(sf::Color(182, 6, 6, 0));
    rect.setSize(Vector2f(480, 600));
    rect.setPosition(160, 0);
}

void Boss::RedShape::update() {

    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();

    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 50) {
        if (count == 0) {
            if (trans != 105)
                trans += 5;
            else count = 1;
        } else if (count == 1) {
            if (trans != 0)
                trans -= 5;
            else count = 0;
        }

        rect.setFillColor(sf::Color(182, 6, 6, trans));
        lastTime = 0;
    }
}

void Boss::RedShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(rect, states);
}