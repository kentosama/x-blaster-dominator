/* 
 * File:   Animation.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 2 mars 2013, 14:52
 */

#include "Animation.h"

Animation::Animation() {
}

Animation::Animation(const Animation& orig) {
}

Animation::~Animation() {
}

void Animation::initialize(Sprite sprite, Vector2f position, int frameWidth, int frameHeight, int frameCount, int frameLine, int frameTime, Color color, Vector2f scale, bool looping, float rotation, Vector2f origin, bool playerShip) {
    this->sprite = sprite;
    this->position = position;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->frameLine = frameLine;
    this->frameTime = frameTime;
    this->color = color;
    this->sprite.setColor(color);
    this->scale = scale;
    this->looping = looping;
    this->rotation = rotation;
    this->origin = origin;
    this->playerShip = playerShip;
    frameEnd = false;
    currentFrame = 0;
    elapsedTime = 0;
    active = true;
    previous = 0;
    currentFrameLine = 0;
    
    
    sourceRect = IntRect(currentFrame * frameWidth, frameLine * frameHeight, frameWidth, frameHeight);
    sprite.setTextureRect(sourceRect);
    sprite.setScale(scale);
    
}

void Animation::update() {
    if(!active)
        return;
    else
    {
        sourceRect = IntRect(currentFrame * frameWidth, currentFrameLine * frameHeight, frameWidth, frameHeight);
        sprite.setTextureRect(sourceRect);
        sprite.setScale(scale);
    
        elapsedTime = (int)GameTime::Instance()->getElapsedTime().asMilliseconds();
        
        if (elapsedTime - previous > frameTime)
        {

            if (currentFrame < frameCount)
            {    
                currentFrame++;
                if (!playerShip)
                {
                    if (currentFrame == frameCount)
                    { 
                        currentFrame = 0;
                        if (currentFrameLine < frameLine) {
                            currentFrameLine++;
                            
                            if (currentFrameLine == frameLine)
                                currentFrameLine = 0;
                        }
                        
                        if (currentFrameLine == frameLine) {
                            if (!looping)
                                active = false;
                            }
                    }
                
                }

                else if (playerShip)
                {
                    if(looping)
                    {
                        if (currentFrame == frameCount)
                            currentFrame = 0;
                    }
                }
                
                previous = elapsedTime;
                
                
             }
        }
    }
    
    

}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active)
        target.draw(sprite, states);
    
}

