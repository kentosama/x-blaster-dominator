/* 
 * File:   Bullet.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 3 mars 2013, 15:06
 */
#include "Bullet.h"

Bullet::Bullet(Vector2f position, unsigned char bullet) {
    
    if (bullet == 0)
    sprite.setTexture(FileManager::Instance()->bullets[0]);
    else sprite.setTexture(FileManager::Instance()->bullets[1]);
    
    sprite.setPosition(position);
    shadow = sprite ;
    shadow.setColor(sf::Color(50,50,50,50));
    if (bullet == 1)
    {
        damage = 25;
        speed = 5;
    }
#ifdef _DEBUG
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1);
#endif
}

Bullet::Bullet(const Bullet& orig) {
}

Bullet::~Bullet() {
}

void Bullet::initialize() {
    
}

Vector2f Bullet::getPosition() {
    return sprite.getPosition();
}

void Bullet::update() {
    
    if(active)
    {
       rectangle = IntRect((int)sprite.getPosition().x+2,(int)sprite.getPosition().y-5,(int)4,(int)10);
#ifdef _DEBUG
       if (showRectangle) {
       rect.setPosition(rectangle.left, rectangle.top);
       rect.setSize(Vector2f(rectangle.width,rectangle.height));
       }
#endif
       
       sprite.move(0,-speed);
       shadow.setPosition(sprite.getPosition().x +5, sprite.getPosition().y -5);
    
       if (sprite.getPosition().y < -5)
       active = false;
    }

}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    if(active){
        target.draw(shadow, states);
        target.draw(sprite, states);
    }
#ifdef _DEBUG 
    if (showRectangle)
    target.draw(rect, states);

#endif
    
}

