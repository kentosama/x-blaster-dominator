/* 
 * File:   WindowGame.cpp
 * Author: jacques
 * 
 * Created on 4 juin 2013, 11:36
 */

#include "WindowGame.h"
#include "Profil.h"

WindowGame* WindowGame::m_pInstance = NULL;

WindowGame* WindowGame::Instance() {
    if (!m_pInstance)
        m_pInstance = new WindowGame;
    return m_pInstance;
}

WindowGame::WindowGame() {
    focus = true;
    fullScreen = Profil::Instance()->fullscreen;
}

WindowGame::WindowGame(const WindowGame& orig) {
}

WindowGame::~WindowGame() {
}




