/* 
 * File:   TitleScreen.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 1 mars 2013, 13:19
 */

#include "TitleScreen.h"
#include "GamePadManager.h"
#include "Profil.h"

TitleScreen::TitleScreen() {

    injection.setTexture(FileManager::Instance()->title[1]);
    injection.setPosition(0, 0);
    screen = 0;
    sound.setBuffer(FileManager::Instance()->sound[7]);
    sound.setVolume(5);
    linux.setTexture(FileManager::Instance()->title[0]);
    linux.setPosition(0, 0);
    sfml.setTexture(FileManager::Instance()->title[2]);
    sfml.setPosition(0, 0);
    lastTime = 0;
    a = false;
    b = false;
    c = false;
    d = false;
    transition.autoActive = false;

}

TitleScreen::TitleScreen(const TitleScreen& orig) {
}

TitleScreen::~TitleScreen() {

}

void TitleScreen::initialize() {

}

void TitleScreen::update() {

    transition.update();

    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    if (screen == 0) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 5000) {
            lastTime = 0;
            if (!a) {
                transition.initialize(1);
                a = true;
            } else if (transition.finish) {
                transition.initialize(2);
                screen = 1;
            }

        }
    } else if (screen == 1) {

        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 5000) {
            lastTime = 0;
            if (!b) {
                transition.initialize(1);
                b = true;
            } else if (transition.finish) {
                transition.initialize(2);
                screen = 2;
            }
        }

        if (!c) {
            sound.play();
            c = true;
        }


    } else if (screen == 2) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 5000) {
            lastTime = 0;
            if (!d) {
                transition.initialize(1);
                d = true;
            } else if (transition.finish) {
                transition.initialize(2);
                screen = 3;
            }
        }
    } else if (screen == 3 && GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 1000) {
        transition.initialize(2);
        title_end = true;
    }

    if (Profil::Instance()->newProfil == false) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() > 2000) {

            if (GamePadManager::Instance()->gamepadConnected) {
                if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[3])) {
                    transition.initialize(2);
                    title_end = true;
                }
            }
            if (WindowGame::Instance()->focus) {
                if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[3])) {
                    transition.initialize(2);
                    title_end = true;
                }
            }
        }
    }
}

void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (screen < 3) {
        if (screen == 0)
            target.draw(linux, states);
        else if (screen == 1)
            target.draw(injection, states);
        else if (screen == 2)
            target.draw(sfml, states);
    }

    target.draw(transition, states);
}