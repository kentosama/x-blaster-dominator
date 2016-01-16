/* 
 * File:   WindowBox.h
 * Author: jacques belosoukinski
 *
 * Created on 20 mars 2013, 13:51
 */

#ifndef WINDOWBOX_H
#define	WINDOWBOX_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameTime.h"
#include "FileManager.h"
#include <iostream>
#include <vector>
using sf::Texture;
using sf::Sprite;
using sf::Text;
using sf::Vector2f;
using sf::Time;
using sf::Clock;
using sf::SoundBuffer;
using sf::Sound;
using std::string;

class WindowBox : public sf::Drawable {
public:
    WindowBox(string messagebox);
    WindowBox(const WindowBox& orig);
    virtual ~WindowBox();
    void initialize();
    void loadcontent();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool active;

private:
    Sprite sprite;
    Text text;
    Vector2f eventPosition;
    Vector2f position;
    sf::Time time = sf::seconds(4);
    Clock gameTime;
    int speed, textMarge;
    unsigned char count;
    float lastTime;
    SoundBuffer sndMessage;
    Sound sound;
    bool sndPlayed;
    sf::Font font;
};

#endif	/* WINDOWBOX_H */

