/* 
 * File:   Explosion.h
 * Author: jacques belosoukinski
 *
 * Created on 4 mars 2013, 13:23
 */

#ifndef EXPLOSION_H
#define	EXPLOSION_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "FileManager.h"

using sf::Sprite;
using sf::Vector2f;
using sf::Color;
class Explosion : public sf::Drawable {
public:
    Explosion(Vector2f position, Vector2f origin, float rotation, Vector2f scale);
    Explosion(const Explosion& orig);
    virtual ~Explosion(); 
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Vector2f getPosition();
    Vector2f setOrigin();
    Sprite sprite;
    bool active;
private:
    
    Vector2f position, origin, scale;
    float rotation;
    Animation animation;

};

#endif	/* EXPLOSION_H */

