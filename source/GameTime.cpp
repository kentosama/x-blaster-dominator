/* 
 * File:   GameTime.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 20 mars 2013, 19:30
 */

#include "GameTime.h"

GameTime* GameTime::m_pInstance = NULL;

GameTime* GameTime::Instance() {
    if (!m_pInstance)
        m_pInstance = new GameTime;
    return m_pInstance;
}

GameTime::GameTime() {
    
    run = true;
}

GameTime::GameTime(const GameTime& orig) {
}

GameTime::~GameTime() {
}

Time GameTime::getElapsedTime() {
    return time + clock.getElapsedTime();
}

void GameTime::start() {
    if (!run)
    {
        run = true;
        clock.restart();
    }
}

void GameTime::restart() {
    
    time = Time::Zero;
    clock.restart();
}

void GameTime::pause() {
    
    time += clock.getElapsedTime();
    run = false;
}

void GameTime::resume() {
   
}



