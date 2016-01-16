/* 
 * File:   WindowBox.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 20 mars 2013, 13:51
 */

#include "WindowBox.h"

WindowBox::WindowBox(string messagebox) {
    active = true;
    font.loadFromFile(FileManager::Instance()->font);
    sound.setBuffer(FileManager::Instance()->sound[1]);
    sound.setVolume(30);
    sndPlayed = false;

    sprite.setTexture(FileManager::Instance()->windowbox);
    text.setString(messagebox);
    text.setFont(font);
    initialize();
}

WindowBox::WindowBox(const WindowBox& orig) {
}

WindowBox::~WindowBox() {
}

void WindowBox::initialize() {
    position = Vector2f(225, 600);
    eventPosition = Vector2f(250, 555);
    sprite.setPosition(position);
    text.setPosition(position);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 );

    text.setScale(0.4, 0.4);
    speed = 1;
    count = 0;
    lastTime = 0;

}

void WindowBox::update() {
    if (active) {

        if (!sndPlayed) {
            sound.play();
            sndPlayed = true;
        }

        if (count == 0) {
            if (sprite.getPosition().y > eventPosition.y)
                sprite.move(0, -speed);
            else count = 1;
        }

        else if (count == 1) {
            if(lastTime == 0)
               lastTime = gameTime.getElapsedTime().asMilliseconds(); 
            else if (gameTime.getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {
                
                if (sprite.getPosition().y < position.y) {
                    sprite.move(0, +speed);
                } else if (sprite.getPosition().y == position.y)
                    active = false;
                
            }
        }
    }
    
    text.setPosition((sprite.getPosition().x) + (sprite.getTexture()->getSize().x / 2), sprite.getPosition().y + 25);
}

void WindowBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {
        target.draw(sprite, states);
        target.draw(text, states);
    }

}

