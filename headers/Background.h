/* 
 * File:   Background.h
 * Author: jacques belosoukinski
 *
 * Created on 1 mars 2013, 19:22
 */

#ifndef BACKGROUND_H
#define	BACKGROUND_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "FileManager.h"
#include "GameTime.h"

using sf::Vector2f;
using sf::Sprite;
using sf::Texture;
using std::cout;
using std::endl;
using std::vector;

class Background : public sf::Drawable {
public:
    Background();
    Background(const Background& orig);
    virtual ~Background();
    void initialize(unsigned char stage);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool active = true;
    vector<Sprite> background;
    vector<Animation> animation;
    vector<float> speed;

private:

    class Ecume : public sf::Drawable {
    public:
        Ecume(unsigned char mode);
        void initialize();
        void loadcontent();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        vector<Texture> ecumes;
        Sprite sprite;
        unsigned int count, mode;
        float speed;
        float lastTime;
    };

public:
    vector<Ecume> ecumes;

private:
    unsigned char stage;
    unsigned char countBackground;
    int position = 0;
    int limitPosition;
    float Speed = 0;
    int newposition = 640;



};

#endif	/* BACKGROUND_H */

