/* 
 * File:   Transition.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 9 mars 2013, 18:21
 */

#include "Transition.h"

Transition::Transition(unsigned char action, unsigned char mode) {
    this->action = action;
    if (mode == 0) {
        rectangle.setSize(Vector2f(480, 600));
        rectangle.setPosition(Vector2f(160, 0));
    } else if (mode == 1) {
        rectangle.setSize(Vector2f(800, 600));
        rectangle.setPosition(Vector2f(0, 0));
    }
    trans = 0;
    initialize(action);
    autoActive = true;
}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}

void Transition::initialize(unsigned char action) {

    this->action = action;
    if (action == 1) {
        trans = 0;
    } else if (action == 2) {
        trans = 255;
    }
    rectangle.setFillColor(Color(0, 0, 0, trans));
    lastTime = 0;
    start = true;
    active = true;
    finish = false;
    
}

void Transition::update() {

    if (finish && autoActive) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 1000) {
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            active = false;
        }
    }
    
    if (action == 1) {

        if (trans < 255) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 50) {
            trans += 5;
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
        }


        else if (trans >= 255) {
            trans = 255;
            finish = true;
        }
    }

    else if (action == 2) {
        if (trans > 0) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 50) {
            trans -= 5;
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
        } 


        else if (trans <= 0) {
            trans = 0;
            finish = true;
        }

    }
rectangle.setFillColor(sf::Color(0, 0, 0, trans));

}

void Transition::restart() {

}

void Transition::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if(active)
        target.draw(rectangle, states);
}
