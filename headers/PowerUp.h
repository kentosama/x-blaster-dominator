/* 
 * File:   PowerUp.h
 * Author: jacques belosoukinski
 *
 * Created on 15 mars 2013, 21:32
 */

#ifndef POWERUP_H
#define	POWERUP_H
#include <SFML/Graphics.hpp>
#include "FileManager.h"

using sf::Sprite;
using sf::IntRect;
using sf::Vector2f;


class PowerUp : public sf::Drawable {
public:
    PowerUp(Vector2f position);
    PowerUp(const PowerUp& orig);
    virtual ~PowerUp();
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int powerup;
    bool active;
    IntRect rectangle;
private:
    Sprite sprite;
    
    Vector2f position;

};

#endif	/* POWERUP_H */

