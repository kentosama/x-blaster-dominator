/* 
 * File:   GameManager.h
 * Author: jacques belosoukinski
 *
 * Created on 1 mars 2013, 12:28
 */

#ifndef GAMEMANAGER_H
#define	GAMEMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "Stage.h"
#include "Profil.h"
#include "Highscore.h"
#include "FileManager.h"
#include "MusicManager.h"
#include "MessageManager.h"
#include "Credit.h"

using std::cout;
using std::endl;
using sf::Time;
using sf::Texture;
using sf::Sprite;

class GameManager : public sf::Drawable {
public:
    GameManager();
    GameManager(const GameManager& orig);
    virtual ~GameManager();
    void selectStage();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void loadcontent();
    std::string to_string(int string);
#if defined _DEBUG || _BETA
    sf::Font font;
    sf::Text version;
    
    sf::Clock clock;
    float currentTime, fps, lastTime, lastRefresh;
    bool showFPS;
    sf::Text textFPS;
#endif
    
protected:
    enum GameStatut {_title, _menu, _stage, _credit};
#if defined _RELEASE || defined _BETA
    GameStatut gameStatut = _title;
#elif defined _DEBUG
    GameStatut gameStatut = _menu;
#endif
    TitleScreen titleScreen;
    Menu menu;
    Stage stage;
    Time time;
    Sprite s_interface;
    Credit credit;
    
};

#endif	/* GAMEMANAGER_H */

