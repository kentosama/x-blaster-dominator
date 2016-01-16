/* 
 * File:   dynaText.h
 * Author: jacques belosoukinski
 *
 * Created on 10 mars 2013, 11:59
 */

#ifndef DYNATEXT_H
#define	DYNATEXT_H
#include <SFML/Graphics.hpp>
#include "FileManager.h"
using sf::Sprite;
using sf::Texture;
using sf::Vector2f;

class dynaText : public sf::Drawable {
public:
    dynaText();
    dynaText(const dynaText& orig);
    virtual ~dynaText();
    void initialize(unsigned char stage,Vector2f position, unsigned char direction, float speed);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Sprite sprite;
private:
    int direction;
    float speed;
    bool active;

};

#endif	/* DYNATEXT_H */

