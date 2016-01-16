/* 
 * File:   Animation.h
 * Author: jacques belosoukinski
 *
 * Created on 2 mars 2013, 14:52
 */

#ifndef ANIMATION_H
#define	ANIMATION_H
#include <SFML/Graphics.hpp>
#include "GameTime.h"
#include <iostream>

using sf::Vector2f;
using sf::IntRect;
using sf::Color;
using sf::Sprite;
using sf::Time;
using std::cout;
using std::endl;


class Animation : public sf::Drawable {
public:
    Animation();
    Animation(const Animation& orig);
    virtual ~Animation();
    void update();
    void loadcontent();
    void initialize(Sprite sprite, Vector2f position, int frameWidth, int frameHeight, int frameCount, int frameLine, int frameTime, Color color, Vector2f scale, bool looping, float rotation, Vector2f origin, bool playerShip);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int frameWidth, frameHeight, frameLine, frameLineCount, frameCount, frameTime,elapsedTime, currentFrameLine, currentFrame;
    bool active, looping, frameEnd, playerShip;
    float rotation, previous;
    Color color;
    IntRect sourceRect;
    IntRect destinationRect;
    Sprite sprite;
    Vector2f origin, position, scale;
   
    
private:
    
};

#endif	/* ANIMATION_H */

