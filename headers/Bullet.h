/* 
 * File:   Bullet.h
 * Author: jacques belosoukinski
 *
 * Created on 3 mars 2013, 15:06
 */

#ifndef BULLET_H
#define	BULLET_H
#include <SFML/Graphics.hpp>
#include "FileManager.h"

using sf::Sprite;
using sf::Texture;
using sf::Vector2f;
using sf::IntRect;
using sf::RectangleShape;

class Bullet : public sf::Drawable {
public:
    Bullet(Vector2f position, unsigned char bullet);
    Bullet(const Bullet& orig);
    virtual ~Bullet();
    void initialize();
    void update();
    Vector2f getPosition();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Sprite sprite;
    bool active = true;
    IntRect rectangle;
    int damage = 15;
#ifdef _DEBUG
    bool showRectangle = false;
#endif
private:
    Vector2f position;
    Texture bulletA;
    Texture bulletB;
    Sprite shadow;
    RectangleShape rect;
    float speed = 8;
    
   

};

#endif	/* BULLET_H */

