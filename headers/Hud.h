/* 
 * File:   Hud.h
 * Author: jacques belosoukinski
 *
 * Created on 10 mars 2013, 09:18
 */

#ifndef HUD_H
#define	HUD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameTime.h"
#include "Language.h"
#include "FileManager.h"

using sf::Sprite;
using sf::Texture;
using sf::Text;
using sf::Font;
using sf::Vector2f;
using sf::IntRect;
using sf::Time;
using sf::Color;
using std::vector;
using std::string;


class Hud : public sf::Drawable {
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();
    void setLanguage();
    void pushStart();
    void loadcontent();
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    unsigned char countLives, countWeapon, trans_pushstart;
    char countEnergy;
    bool pushstart, collision, goldCollision;
    vector<Text> m_text;
   
private:
    unsigned char count;
    unsigned char transPilot, redPilot;
    float last, lastTime;
    Font font;
    vector<Sprite> hud;
    vector<string> text;
    vector<Sprite> lives;
    vector<Sprite> energy;
    vector<Sprite> weapon;
    Time time;
    
    class Pilot : public sf::Drawable {
    public:
        Pilot();
        void initialize();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        Sprite sprite;
        Vector2f frameSize;
        bool collision, goldCollision;
        char energy;
        const unsigned char frameCount = 4;
        unsigned char currentFrame, warning, trans, credit, count, lives;
        float lastTime;
        IntRect sourceRect, destinationRect;
        Color color;
        
    };
    
    Pilot pilot;
    
    

};

#endif	/* HUD_H */

