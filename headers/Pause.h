/* 
 * File:   Pause.h
 * Author: jacques belosoukinski
 *
 * Created on 25 mars 2013, 07:10
 */

#ifndef PAUSE_H
#define	PAUSE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "GamePadManager.h"
#include "FileManager.h"
using sf::Sprite;
using sf::Font;
using sf::Text;
using sf::Sound;
using sf::Clock;
using sf::Time;
using sf::Joystick;
using sf::Keyboard;
using std::string;

using std::vector;

class Pause : public sf::Drawable {
public:
    Pause();
    Pause(const Pause& orig);
    virtual ~Pause();
    unsigned char action();
    void initialize();
    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool active;
    unsigned char useraction;
private:
    void moveUp();
    void moveDown();
    char move, marge;
    char axisUp, axisDown;
    Font font;
    Sprite window, select;
    Sound sound;
    vector<Text> text;
    vector<string> language;
    Time time;
    Clock gameTime;
    float lastTime;
    
};

#endif	/* PAUSE_H */

