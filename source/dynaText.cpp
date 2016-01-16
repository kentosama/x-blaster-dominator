/* 
 * File:   dynaText.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 10 mars 2013, 11:59
 */

#include "dynaText.h"

dynaText::dynaText() {
}

dynaText::dynaText(const dynaText& orig) {
}

dynaText::~dynaText() {
}

void dynaText::initialize(unsigned char stage,Vector2f position, unsigned char direction, float speed) {
    sprite.setTexture(FileManager::Instance()->text[stage - 1]);
    sprite.setPosition(position);
    this->direction = direction;
    this->speed = speed;
    active = true;
    
}

void dynaText::update() {
    
    if(active)
    {
        if(direction == 0)
            sprite.move(speed,0);
        if(direction == 1)
            sprite.move(0,speed);
    }
        
}

void dynaText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(active)
        target.draw(sprite, states);
    
}
