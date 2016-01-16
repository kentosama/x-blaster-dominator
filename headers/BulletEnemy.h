/* 
 * File:   BulletEnemy.h
 * Author: jacques belosoukinski
 *
 * Created on 5 mars 2013, 12:29
 */

#ifndef BULLETENEMY_H
#define	BULLETENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FileManager.h"

using sf::Sprite;
using sf::Vector2f;
using sf::IntRect;
using sf::RectangleShape;
using std::cout;
using std::endl;

class BulletEnemy : public sf::Drawable {
public:
    BulletEnemy(Vector2f position, unsigned char bullet, unsigned char movement, Vector2f target);
    BulletEnemy(const BulletEnemy& orig);
    virtual ~BulletEnemy();
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Vector2f getPosition();
    bool active = true;
    unsigned char damage;
    IntRect rectangle;
private:
    void normalize(Vector2f vector);
    float speed = 0;
    unsigned char bullet, movement;
    Sprite sprite;
    Sprite shadow;
    Vector2f position, target;
    bool showRectangle = false;
    RectangleShape rect;

};

#endif	/* BULLETENEMY_H */

