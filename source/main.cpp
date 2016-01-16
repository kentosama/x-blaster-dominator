/* 
 * File:   main.cpp
 * Author: Jacques Belosoukinski <shingosan@genku.net>
 *
 * Created on 1 mars 2013, 11:21
 */

#include <cstdlib>
#if defined _WIN32 || _WIN64
//#define  _WIN32_WINNT 0x0501
#include <windows.h>    
#endif
#include "Profil.h"
#include "GameManager.h"
#include "GamePadManager.h"
#include "Language.h"
#include "MessageManager.h"
#include "Capture.h"
#include "ErrorManager.h"
#include "WindowGame.h"

using namespace std;

static std::string to_string(int value){
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int main() {
    MessageManager::Instance()->setLanguage();
    FileManager::Instance()->loadcontent();
    Profil::Instance()->open();
    GameManager gameManager;
    Capture capture;

    unsigned int maxTexture = sf::Texture::getMaximumSize();
    if (maxTexture < 500) {
#if defined _WIN32
        std::string message;
        message = "Your graphic card is not supported.\nMaximum texture size: " + to_string(maxTexture)+"x"+to_string(maxTexture);
        MessageBox(NULL, message.c_str(), NULL, 0x00000000L);
#endif
        ErrorManager::Instance()->save(1, "Your graphic card is not supported. Texture size : " + to_string(maxTexture) );
    }

#if defined _WIN32
    bool screensaver = false;
    if (!SystemParametersInfo(SPI_GETSCREENSAVEACTIVE, 0, NULL, SPIF_UPDATEINIFILE)) {
        SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 0, NULL, SPIF_UPDATEINIFILE);
        screensaver = true;
    }
#endif

#if (_WIN32_WINNT >= 0x0500 || _WIN32_WINDOWS >= 0x0410)
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
#endif

    std::vector<string> language;
    std::string title = "X-Blaster Dominator";

#ifdef _DEBUG
    title = title + " [DEBUG]";
#elif _BETA
    title = title + " [BETA]";
#endif

    if (Language::Instance()->language != "english") {
        language = Language::Instance()->french[6];
    } else language = Language::Instance()->english[6];

    sf::VideoMode videomode = sf::VideoMode(800, 600, 32);

    // Check the resolution of the desktop
    if (videomode > sf::VideoMode::getFullscreenModes()[0])
        ErrorManager::Instance()->save(0, "");
    else if (!Profil::Instance()->fullscreen)
        WindowGame::Instance()->window.create(videomode, title, sf::Style::Close);
    else WindowGame::Instance()->window.create(videomode, title, sf::Style::Fullscreen);
    WindowGame::Instance()->window.setVerticalSyncEnabled(true);
    WindowGame::Instance()->window.setMouseCursorVisible(false);
    WindowGame::Instance()->window.setFramerateLimit(60);

    GamePadManager::Instance()->open();

#ifdef __linux
    if (Language::Instance()->language != "french")
        std::cout << Language::Instance()->english[8][8] << endl;
    else std::cout << Language::Instance()->french[8][8] << endl;
#endif

    while (WindowGame::Instance()->window.isOpen()) {
        gameManager.update();
        while (WindowGame::Instance()->window.pollEvent(WindowGame::Instance()->event)) {
            GamePadManager::Instance()->update();
            if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.Closed) {
                WindowGame::Instance()->window.close();
            } else if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
                    WindowGame::Instance()->window.close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    if (WindowGame::Instance()->fullScreen)
                        WindowGame::Instance()->fullScreen = false;
                    else if (!WindowGame::Instance()->fullScreen)
                        WindowGame::Instance()->fullScreen = true;
                    WindowGame::Instance()->changeScreen = true;
                }
            }
#ifdef __linux
            else if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickButtonPressed || WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickMoved) {
                if (GamePadManager::Instance()->gamepadConnected)
                    GamePadManager::Instance()->fakeKey();
            }
#endif

            if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.LostFocus) {
                WindowGame::Instance()->focus = false;
                GameTime::Instance()->pause();
            } else if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.GainedFocus) {
                WindowGame::Instance()->focus = true;
                GameTime::Instance()->start();
            }
        }

        //#if defined _DEBUG || _BETA
        capture.update();
        //#endif

        WindowGame::Instance()->window.clear();
        WindowGame::Instance()->window.draw(gameManager);
        WindowGame::Instance()->window.display();

        if (WindowGame::Instance()->changeScreen) {
            if (!WindowGame::Instance()->fullScreen)
                WindowGame::Instance()->window.create(videomode, title, sf::Style::Close);
            else WindowGame::Instance()->window.create(videomode, title, sf::Style::Fullscreen);
            WindowGame::Instance()->window.setFramerateLimit(60);
            WindowGame::Instance()->window.setVerticalSyncEnabled(true);
            WindowGame::Instance()->window.setMouseCursorVisible(false);
            WindowGame::Instance()->changeScreen = false;
        }
    }
    
    MusicManager::Instance()->player.stop();

// Restore energy configuration for Windows System
#if defined _WIN32 || _WIN64
    if (screensaver)
        SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 1, NULL, SPIF_UPDATEINIFILE);
#endif

#if (_WIN32_WINNT >= 0x0500 || _WIN32_WINDOWS >= 0x0410)
    SetThreadExecutionState(ES_CONTINUOUS);
#endif
    
    return 0;
}