/* 
 * File:   Explosion.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 4 mars 2013, 13:23
 */

#include "Explosion.h"

Explosion::Explosion(Vector2f position, Vector2f origin, float rotation, Vector2f scale) {
    sprite.setTexture(FileManager::Instance()->items[4]);
    sprite.setOrigin(origin);
    
    sprite.setScale(scale);
    sprite.setPosition(position);
    this->origin = origin;
    this->scale = scale;
    this->position = position;
    this->rotation = rotation;
    sprite.setRotation(rotation);
    active = true;
    initialize();
}

Explosion::Explosion(const Explosion& orig) {
}

Explosion::~Explosion() {
}

Vector2f Explosion::getPosition() {
    return sprite.getPosition();
}

Vector2f Explosion::setOrigin() {
    return Vector2f((sprite.getGlobalBounds().width / 4) / 2, sprite.getGlobalBounds().height / 2);
}

void Explosion::initialize() {
    animation.initialize(sprite, Vector2f(position),63,63,4,0,100,Color::White,scale,false,rotation,origin, false);
    active = animation.active;
}

void Explosion::update() {
    active = animation.active;
    
    if (active) {
        animation.update();
        animation.sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        
    }
    
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active)
    target.draw(animation, states);
}

