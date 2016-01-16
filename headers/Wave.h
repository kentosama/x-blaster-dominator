/* 
 * File:   Wave.h
 * Author: jacques belosoukinski
 *
 * Created on 23 mars 2013, 10:16
 */

#ifndef WAVE_H
#define	WAVE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "FileManager.h"
#include "Profil.h"
#include "Boss.h"
#include <iostream>


class Wave : public sf::Drawable {
public:
    Wave();
    Wave(const Wave& orig);
    virtual ~Wave();
    void initialize(unsigned char stage, unsigned char startWave);
    void waveBoss(const unsigned char currentWave);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<Enemy> enemies;
    std::vector<Boss> boss;
    bool finished, test, initialized;
    bool comingBoss;
    unsigned char currentWave, countWaveBoss, stage;
private:
    unsigned char gameDifficulty; 
    

};

#endif	/* WAVE_H */

