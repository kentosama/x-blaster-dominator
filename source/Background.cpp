/* 
 * File:   Background.cpp
 * Author: jacques belosoukinski belosoukinski
 * 
 * Created on 1 mars 2013, 19:22
 */

#include "Background.h"

Background::Background() {
    limitPosition = 640;
}

Background::Background(const Background& orig) {
}

Background::~Background() {
}

void Background::initialize(unsigned char stage) {
    if (ecumes.size() > 0)
        ecumes.clear();
    this->stage = stage;
    unsigned char a;
    if (stage == 1) {
        a = 5;
        this->position = -1280;
        countBackground = 4;
        ecumes.reserve(2);
        ecumes.emplace_back(0);
        ecumes.emplace_back(1);
        for (unsigned char i = 0; i < 2; i++)
            ecumes[i].initialize();

    } else {
        a = 4;
        this->position = -640;
        countBackground = 3;
    }
    background.clear();
    background.reserve(a);
    if (FileManager::Instance()->loaded) {
        int position = 640;
        for (unsigned char i = 0; i < a; i++) {
            position -= 640;
            background.emplace_back();
            background[i].setPosition(160, position);

            background[i].setTexture(FileManager::Instance()->backgrounds[stage - 1][i]);

        }

        if (stage == 5) {
            animation.reserve(2);
            for (unsigned char i = 0; i < 2; i++) {
                animation.emplace_back();
                animation[i].initialize(background[i], background[i].getPosition(), 480, 640, 2,0, 1000, sf::Color::White, Vector2f(1,1), true, 0, background[i].getOrigin(), false);
            }
        }
    }

}

void Background::update() {
    if (stage == 5) {
        for (unsigned char i = 0; i < 2; i++) {
            animation[i].sprite.setPosition(background[i].getPosition());
            animation[i].update();
        }
    }

    background[0].move(0, 0.8);
    background[1].move(0, 0.8);
    if (stage == 1) {
        background[2].move(0, 0.8);
        background[3].move(0, 1.3);
        background[4].move(0, 1.5);
    } else {
        background[2].move(0, 1.3);
        background[3].move(0, 1.5);
    }

    for (unsigned char i = 0; i < countBackground; i++) {

        if (background[i].getPosition().y > limitPosition) {
            if (stage == 1)
                background[i].setPosition(160, -1278);
            else background[i].setPosition(160, -639);
            
        }
    }

    if (background[countBackground].getPosition().y > limitPosition)
        background[countBackground].setPosition(160, position - 640);

    if (stage == 1) {
        for (unsigned char i = 0; i < 2; i++)
            ecumes[i].update();
    }

}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(animation[0], states);

}

Background::Ecume::Ecume(unsigned char mode) {
    this->mode = mode;
    ecumes.reserve(3);
    speed = 0.8;
    for (unsigned char i = 0; i < 3; i++) {
        ecumes.emplace_back();
        if (mode == 0)
            ecumes[i] = FileManager::Instance()->ecumes[i];
        else if (mode == 1)
            ecumes[i] = FileManager::Instance()->ecumes[i + 3];
    }
}

void Background::Ecume::initialize() {
    sprite.setTexture(ecumes[0]);
    lastTime = 0;
    count = 0;
    if (mode == 0)
        sprite.setPosition(160, 0);
    else if (mode == 1)
        sprite.setPosition(160, -640);
}

void Background::Ecume::update() {

    // Dédié à l'animation
    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (count == 2) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 2000) {
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            count += 1;
            sprite.setTexture(ecumes[count - 1]);
        }
    } else if (count < 2) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 400) {
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            count += 1;
            sprite.setTexture(ecumes[count - 1]);
        }
    } else if (count < 6) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 400) {
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            count += 1;
            if (count == 4)
            sprite.setTexture(ecumes[count - 3]);
            else if (count == 5)
                sprite.setTexture(ecumes[count - 5]);
    }
    }
    
    

    if (count > 5)
        count = 0;

    sprite.move(0, +speed);

    if (sprite.getPosition().y > 640)
        sprite.setPosition(160, -1278);
}

void Background::Ecume::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (count > 0 && count < 6) {
        target.draw(sprite, states);
    }
}
