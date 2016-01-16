/* 
 * File:   WindowGame.h
 * Author: jacques belosoukinski
 *
 * Created on 4 juin 2013, 11:36
 */

#ifndef WINDOWGAME_H
#define	WINDOWGAME_H
#include <SFML/Graphics.hpp>

class WindowGame {
public:
    static WindowGame* Instance();
    WindowGame();
    WindowGame(const WindowGame& orig);
    virtual ~WindowGame();
    bool focus;
    sf::RenderWindow window;
    sf::Event event;
    bool fullScreen = false;
    bool changeScreen = false;
private:
    static WindowGame* m_pInstance;
};

#endif	/* WINDOWGAME_H */

