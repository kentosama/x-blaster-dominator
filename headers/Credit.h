/* 
 * File:   Credit.h
 * Author: jacques belosoukinski
 *
 * Created on 10 avril 2013, 23:30
 */

#ifndef CREDIT_H
#define	CREDIT_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Background.h"
#include "FileManager.h"
#include "GameTime.h"
#include "Language.h"
#include "Transition.h"
#include "Profil.h"
#include "MusicManager.h"

using sf::Sprite;
using sf::Text;
using sf::Vector2f;
using sf::Font;
using std::vector;
using std::string;

class Credit : public sf::Drawable {
public:
    Credit();
    Credit(const Credit& orig);
    virtual ~Credit();
    void initialize();
    void update();    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool finished, initialized;
private:
    void loadMusic();
    Transition transition = Transition(2,0);
    Background background;
    Sprite fade;
    Font font;
    vector<string> language;
    unsigned int stage;
    float lastTime;
    
    class textCredit {
    public :
        textCredit(string text, float startTime, Vector2f position);
        bool active = false;
        float startTime;
        unsigned char trans = 255;
        Text text;
    };
    
    vector<textCredit> credit;
    
    

};

#endif	/* CREDIT_H */

