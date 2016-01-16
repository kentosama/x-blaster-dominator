/* 
 * File:   Transition.h
 * Author: jacques belosoukinski
 *
 * Created on 9 mars 2013, 18:21
 */

#ifndef TRANSITION_H
#define	TRANSITION_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameTime.h"
using sf::RectangleShape;
using sf::Color;
using sf::Time;
using sf::Vector2f;
using std::cout;
using std::endl;
class Transition : public sf::Drawable {
public:
    Transition(unsigned char action, unsigned char mode);
    Transition(const Transition& orig);
    virtual ~Transition();
    void initialize(unsigned char action);
    void update();
    void restart();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool active, start, finish, autoActive;
    unsigned char trans, action;
    RectangleShape rectangle;
private:
    
    Time time;
    int lastTime = 0;
    

};

#endif	/* TRANSITION_H */

