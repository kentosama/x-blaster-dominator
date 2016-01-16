/* 
 * File:   Pause.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 25 mars 2013, 07:10
 */

#include "Pause.h"
#include "Language.h"

Pause::Pause() {
    font.loadFromFile(FileManager::Instance()->font);
    if (Language::Instance()->language == "english")
        language = Language::Instance()->english[5];
    else language = Language::Instance()->french[5];

    select.setTexture(FileManager::Instance()->menu[3]);
    window.setTexture(FileManager::Instance()->menu[7]);
    window.setPosition(270, 200);
    sound.setBuffer(FileManager::Instance()->sound[0]);
    move = 0;
    marge = 3;
    active = false;
    lastTime = 0;
    time = sf::seconds(0.1);
    text.reserve(5);
    useraction = 0;
    short int position = 245;
    for (char i = 0; i < 5; i++) {
        position += 20;
        text.emplace_back();
        text[i].setColor(sf::Color::White);
        text[i].setFont(font);
        text[i].setPosition(310, position);
        text[i].setScale(0.4, 0.4);
    }
    for (unsigned char i = 0; i < 4; i++)
        text[i].setString(language[i]);

    select.setPosition(300, text[0].getPosition().y + marge);
    gameTime.restart();
}

Pause::Pause(const Pause& orig) {
}

Pause::~Pause() {
}

void Pause::moveUp() {

    move -= 1;
    sound.play();
    lastTime = gameTime.getElapsedTime().asMilliseconds();
}

void Pause::moveDown() {
    move += 1;
    sound.play();
    lastTime = gameTime.getElapsedTime().asMilliseconds();
}

void Pause::update() {
    if (active) {
        
        if (lastTime == 0)
            lastTime = gameTime.getElapsedTime().asMilliseconds();
        if (gameTime.getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {

            if (GamePadManager::Instance()->gamepadConnected) {

                if (GamePadManager::Instance()->gamepadMoved()) {
                    if (Joystick::getAxisPosition(0, Joystick::Y) > GamePadManager::Instance()->axisUp)
                        moveDown();

                    else if (Joystick::getAxisPosition(0, Joystick::Y) < GamePadManager::Instance()->axisDown)
                        moveUp();

                    else {

#ifdef __linux
                        if (Joystick::getAxisPosition(0, Joystick::PovY) == -100)
                            moveUp();
                        else if (Joystick::getAxisPosition(0, Joystick::PovY) == 100)
                            moveDown();
#elif defined _WIN32 || _WIN64
                        if (Joystick::getAxisPosition(0, Joystick::PovX) == -100)
                            moveDown();
                        else if (Joystick::getAxisPosition(0, Joystick::PovX) == 100)
                            moveUp();
#endif
                    }
                }

                if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0])) {

                    lastTime = gameTime.getElapsedTime().asMilliseconds();
                    useraction = move + 1;
                    move = 0;

                } else if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[2])) {
                    lastTime = gameTime.getElapsedTime().asMilliseconds();
                    useraction = 1;
                    move = 0;
                }
            }
            if (WindowGame::Instance()->focus) {

                if (Keyboard::isKeyPressed(Keyboard::Down))
                    moveDown();
                else if (Keyboard::isKeyPressed(Keyboard::Up))
                    moveUp();
                if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0])) {

                    lastTime = gameTime.getElapsedTime().asMilliseconds();
                    useraction = move + 1;
                    if (useraction != 4)
                        move = 0;
                } else if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1])) {
                    lastTime = gameTime.getElapsedTime().asMilliseconds();
                    useraction = 1;
                    move = 0;
                }
            }

            if (move < 0)
                move = 3;
            else if (move > 3)
                move = 0;
 
            for (unsigned char i = 0; i < 4; i++) {
                if (move == i)
                    select.setPosition(select.getPosition().x, text[i].getPosition().y + marge);
            }
        }
    }
}

void Pause::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (active) {
        target.draw(window, states);
        target.draw(select, states);
        for (unsigned char i = 0; i < 5; i++)
            target.draw(text[i], states);
    }

}

