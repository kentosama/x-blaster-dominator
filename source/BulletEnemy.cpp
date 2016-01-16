/* 
 * File:   BulletEnemy.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 5 mars 2013, 12:29
 */

#include "BulletEnemy.h"

BulletEnemy::BulletEnemy(Vector2f position, unsigned char bullet, unsigned char movement, Vector2f target) { 
    
    this->bullet = bullet;
    if(bullet == 0)
       sprite.setTexture(FileManager::Instance()->bullets[2]);
    else if (bullet == 1)
        sprite.setTexture(FileManager::Instance()->bullets[3]);
    else if(bullet == 2) 
        sprite.setTexture(FileManager::Instance()->bullets[4]);
    this->position = position;
    sprite.setPosition(this->position);
    shadow = this->sprite;
    shadow.setColor(sf::Color(50,50,50,50));
    this->movement = movement;
    
    if (movement == 3) {
        this->target = this->position - target;
        normalize(this->target);
    } else if (movement == 4)
        sprite.setRotation(1.3f);
    else if (movement == 5)
        sprite.setRotation(-1.3f);

    if (bullet == 0) {
        damage = 10;
        speed = 4.4;
    } else if (bullet == 1) {
        damage = 100;
        speed = 3;
    }
    else if (bullet == 2) {
        damage = 50;
        speed = 2.8;
    }
        
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1);
    
}
 
BulletEnemy::BulletEnemy(const BulletEnemy& orig) {
}

BulletEnemy::~BulletEnemy() {
  
}

Vector2f BulletEnemy::getPosition() {
    return sprite.getPosition();
}

void BulletEnemy::normalize(Vector2f vector) {
    
    Vector2f normalize(vector);
    float norme = std::sqrt(normalize.x*normalize.x + normalize.y*normalize.y);
    vector = normalize / norme;
    target = vector;
}

void BulletEnemy::initialize() {
    
}

void BulletEnemy::update() {
    if(active)
    {
        rectangle = IntRect((int)sprite.getPosition().x+3, (int)sprite.getPosition().y+5, (int)10, (int)10);
        rect.setPosition(rectangle.left, rectangle.top);
        rect.setSize(Vector2f(rectangle.width, rectangle.height));
        
        if (movement == 0) {
            sprite.move(0,+speed);
        }
        
        else if (movement == 1 || movement == 4) {
            
            sprite.move(-0.8,+speed);
        }
        else if (movement == 2 || movement == 5) {
            
            sprite.move(+0.8,+speed);
        }
        
        else if (movement == 3) {
            sprite.move(- target * speed);
            
        } else if (movement == 6) {
            sprite.move(+speed, 0);
        } else if (movement == 7) {
            sprite.move(-speed, 0);
        }
        
        shadow.setPosition(sprite.getPosition().x+5, sprite.getPosition().y+2);
        
        if (sprite.getPosition().y > 640 || sprite.getPosition().x < 150 || sprite.getPosition().x > 640)
            active = false;
    }

}

void BulletEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(active)
    {
        target.draw(shadow, states);
        target.draw(sprite, states);
        if(showRectangle)
        target.draw(rect);
    }
}
