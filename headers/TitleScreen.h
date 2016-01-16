/* 
 * File:   TitleScreen.h
 * Author: jacques belosoukinski
 *
 * Created on 1 mars 2013, 13:19
 */

#ifndef TITLESCREEN_H
#define	TITLESCREEN_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameTime.h"
#include "FileManager.h"
#include "Transition.h"

class TitleScreen : public sf::Drawable{
public:
    TitleScreen();
    TitleScreen(const TitleScreen& orig);
    virtual ~TitleScreen();
    void initialize();
    void update(); 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool initialized = false;
    bool title_end = false;
private:
    Transition transition = Transition(2,1);
    sf::Sprite injection;
    sf::Sprite linux;
    sf::Sprite sfml;
    float lastTime;
    float lastTime2;
    int trans = 255;
    unsigned char screen;
    bool a, b, c, d;
    sf::Sound sound;
};

#endif	/* TITLESCREEN_H */

