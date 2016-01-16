/* 
 * File:   GameTime.h
 * Author: jacques belosoukinski
 *
 * Created on 20 mars 2013, 19:30
 */

#ifndef GAMETIME_H
#define	GAMETIME_H
#include <SFML/Graphics.hpp>

using sf::Clock;
using sf::Time;

class GameTime {
public:
    static GameTime* Instance();
    void restart();
    void start();
    void pause();
    void resume();
    Time getElapsedTime();
private:
    GameTime();
    GameTime(const GameTime& orig);
    virtual ~GameTime();
    static GameTime* m_pInstance;
    Time time;
    Time lastTime;
    Clock clock;
    bool run;

};


#endif	/* GAMETIME_H */

