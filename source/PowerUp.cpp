/* 
 * File:   PowerUp.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 15 mars 2013, 21:32
 */

#include "PowerUp.h"

PowerUp::PowerUp(Vector2f position) {
        powerup = rand() % 100;
    if (powerup <= 25 || powerup >= 55 )
        powerup = 0;
    
        else if (powerup > 25 && powerup < 55)
        powerup = 1;
    
    sprite.setTexture(FileManager::Instance()->items[powerup]);
    this->position = position;
    sprite.setPosition(position);
    rectangle = IntRect((int)sprite.getPosition().x,(int)sprite.getPosition().y,(int)sprite.getTexture()->getSize().x,(int)sprite.getTexture()->getSize().y);
    

    active = true;
}

PowerUp::PowerUp(const PowerUp& orig) {
}

PowerUp::~PowerUp() {
}


void PowerUp::update() {
    
    if (active)
    {
        sprite.move(0,+1);
        rectangle = IntRect((int)sprite.getPosition().x,(int)sprite.getPosition().y,(int)sprite.getTexture()->getSize().x,(int)sprite.getTexture()->getSize().y);
        
        if (sprite.getPosition().y > 640)
            active = false;
    }
    
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active)
        target.draw(sprite, states);
    
}

