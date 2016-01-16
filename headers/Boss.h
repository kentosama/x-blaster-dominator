/* 
 * File:   Boss.h
 * Author: jacques belosoukinski
 *
 * Created on 26 mars 2013, 09:21
 */

#ifndef BOSS_H
#define	BOSS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "GameTime.h"
#include "FileManager.h"
#include "Animation.h"
#include "Profil.h"

using sf::Sprite;
using sf::Time;
using sf::Vector2f;
using sf::IntRect;
using std::vector;
using sf::Music;
using sf::RectangleShape;
using sf::Color;
using sf::Clock;

class Boss : public sf::Drawable {
public:
    Boss(const unsigned char stage, Vector2f position, float time);
    Boss(const Boss& orig);
    virtual ~Boss();
    void initialize(const unsigned char stage);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Vector2f setOrigin();
    Vector2f getSize();
    Vector2f getPosition();
    unsigned char getCurrentFrame();
    unsigned char getCurrentFrameLine();
    bool destroyed, inZone, initialized, activeShotA, activeShotB;
    bool active, activeCanonA, activeCanonB;
    unsigned char modeShotA, modeShotB, currentWave, activeWave, countFire;
    vector<IntRect> rect;
    vector<unsigned char> collision;
    vector<float> lastTime;
    float lastTimeA = 0, lastTimeB = 0;
 
#ifdef _DEBUG
    vector<RectangleShape> rectShape;
    RectangleShape rectOrigin;
    bool showRectangle = false;
#endif
    vector<int> health;
    float lastShotA, lastShotB, startTime;
    Time shotTimeA;
    Time shotTimeB;
private:
    void scenario(const unsigned char stage);
    void movementManager();
    void dead();
    Animation animation, shadow;
    Sprite sprite;
    vector<Sprite> energy;
    Vector2f position;
    vector<Color> color;
    bool activeMovement, leftMovement, rightMovement, activeTarget, activeDead;
    float speed, lastCollision, lastEvent, lastTrans, lastDead;
    unsigned char countEvent, stage, movement, trans, countTrans, frameCount, frameLine, portionEnergy, gameDifficulty;
    unsigned int energyfix;
    Time deadTime;
    RectangleShape target;
    
    class RedShape : public sf::Drawable {
    public:
        RedShape();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        float lastTime;
        unsigned char trans, count;
        RectangleShape rect;
        
    };

public:
    RedShape redShape;
    
};

#endif	/* BOSS_H */

