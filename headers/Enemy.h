/* 
 * File:   Enemy.h
 * Author: jacques belosoukinski
 *
 * Created on 3 mars 2013, 21:42
 */

#ifndef ENEMY_H
#define	ENEMY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "GameTime.h"
#include "FileManager.h"
#include <iostream>
using sf::Texture;
using sf::Sprite;
using sf::Vector2f;
using sf::IntRect;
using sf::RectangleShape;
using sf::Time;
using sf::Clock;
using sf::Color;
using std::vector;

class Enemy : public sf::Drawable{
public:
    Enemy(Vector2f position, unsigned char enemyType, float startTime, bool stop, float stopPosition, float stopTime, unsigned char movement, bool fire, bool powerUp);
    Enemy(const Enemy& orig);
    virtual ~Enemy();
    Vector2f getPosition();
    Vector2f getSize();
    float getRotation();
    Vector2f getOrigin();
    Vector2f setOrigin();
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Sprite sprite;
    bool active = true, fire, powerUp, collision = false;
#ifdef _DEBUG
    bool showRectangle;
#endif
    int enemyType, health, damage, score;
    unsigned char count, movement = 0;
    float lastShot, startTime;
    sf::Time shotTime = sf::seconds(1);
    vector<IntRect> rect;

private:
    void movementManager();
    Animation animation;
    Animation animation_shadow;
    Vector2f position, origin, scale;
    float speed, rotation, lastSpeed, stopTime, stopPosition, previousCollision;
    unsigned char frameCount;
    bool stop = false; 
    unsigned char stopMovement;
    vector<RectangleShape> rectShape;
    RectangleShape rectOrigin;
    Color color = Color::White;
    Clock pauseClock;
    bool restartClock = false;
    bool directionLeft = false;
    bool directionRight = false;
    

};

#endif	/* ENEMY_H */

