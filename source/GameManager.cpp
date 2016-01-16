/* 
 * File:   GameManager.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 1 mars 2013, 12:28
 */

#include "GameManager.h"

GameManager::GameManager() {

#if defined _DEBUG || _BETA
    if (font.loadFromFile(FileManager::Instance()->font)) {
        version.setFont(font);
        version.setScale(0.55, 0.55);
        version.setColor(sf::Color::White);

        textFPS.setFont(font);
        textFPS.setScale(0.45, 0.45);
        textFPS.setColor(sf::Color::White);
        textFPS.setPosition(730, 560);
        textFPS.setString("FPS: ");
    } else ErrorManager::Instance()->save(4, "File missing : content/font/font.dat");

    currentTime = 0;
    lastTime = 0;
    lastRefresh = 0;
    fps = 0;
    showFPS = false;

#ifdef _DEBUG
    version.setString("DEBUG VERSION");
    version.setPosition(7, 560);
#elif defined _BETA
    version.setString("BETA VERSION");
    version.setPosition(12, 560);
#endif

#endif

    Highscore::Instance()->open();
    s_interface.setPosition(0, 0);
    s_interface.setTexture(FileManager::Instance()->general);


}

GameManager::GameManager(const GameManager& orig) {
}

GameManager::~GameManager() {
}

void GameManager::update() {
    if (WindowGame::Instance()->focus) {

        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 300) {
            if (Keyboard::isKeyPressed(Keyboard::F4)) {
                if (showFPS)
                    showFPS = false;
                else if (!showFPS)
                    showFPS = true;
                lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            }
        }

        if (showFPS) {
            currentTime = clock.restart().asSeconds();
            fps = 1.0f / currentTime;
            if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastRefresh > 300) {
                textFPS.setString("FPS: " + to_string((int) fps));
                lastRefresh = GameTime::Instance()->getElapsedTime().asMilliseconds();
            }
        }

        if (gameStatut == _title) {
            titleScreen.update();

            if (titleScreen.title_end)
                gameStatut = _menu;
        } else if (gameStatut == _menu) {
            if (stage.finished) {
                stage.transition.initialize(1);
                menu.initialize();
                stage.finished = false;
            }
            if (!menu.startGame) {
                menu.update();
            } else {
                stage.initialize(1);
                gameStatut = _stage;
            }

        } else if (gameStatut == _stage) {
            stage.update();
            if (stage.finished && stage.stage == 5 && stage.stateStage.back().finished && !stage.gameoverActive) {
                credit.initialize();
                gameStatut = _credit;
            } else if (stage.finished)
                gameStatut = _menu;

        } else if (gameStatut == _credit) {

            if (credit.finished) {
                menu.initialize();
                gameStatut = _menu;
            } else credit.update();

        }
        MessageManager::Instance()->update();
    }
    MusicManager::Instance()->update();
}

void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (gameStatut == _title)
        target.draw(titleScreen, states);
    else if (gameStatut == _menu)
        target.draw(menu, states);
    else if (gameStatut == _stage)
        target.draw(stage, states);
    else if (gameStatut == _credit) {
        target.draw(credit, states);
    }

    if (!gameStatut == _title) {
        target.draw(s_interface, states);
    }

    if (showFPS)
        target.draw(textFPS, states);

    if (gameStatut == _stage) {
        target.draw(stage.hud, states);
    }

    if(MessageManager::Instance()->windowsbox.size() > 0){
        target.draw(MessageManager::Instance()->windowsbox.back(), states);
    }

#if defined _DEBUG || _BETA
    target.draw(version);
#endif

}

std::string GameManager::to_string(int string) {
    std::stringstream ss;
    ss << string;
    return ss.str();
}
