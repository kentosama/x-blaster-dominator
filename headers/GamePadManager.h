/* 
 * File:   GamePadManager.h
 * Author: jacques belosoukinski
 *
 * Created on 24 mars 2013, 07:33
 */

#ifndef GAMEPADMANAGER_H
#define	GAMEPADMANAGER_H
#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#elif defined _RELEASE || _BETA
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#ifdef __linux
#include <sys/types.h>
#include <pwd.h>
#elif defined _WIN32 || _WIN64
#include <shlobj.h>
#include <windows.h>
#include <boost/filesystem.hpp>
#endif
#include "GameTime.h"
#include "WindowGame.h"
#include "MessageManager.h"

using sf::Joystick;
using sf::Keyboard;
using sf::Time;
using sf::Event;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

class GamePadManager {
public:
    static GamePadManager* Instance();
    void setButtons();
    void setControl();
    void setKeyboard();
    void open();
    void save();
    void create();
#ifdef __linux
    void fakeKey();
#endif
    unsigned int getButtons();
    bool gamepadMoved();
    bool gamepadPressed();
    bool keyboardPressed();
    void update();
    vector<int> buttons;
    vector<sf::Keyboard::Key> keys;
    unsigned char setting, gameStatut, nbrButtons;
    float previousTime;
    bool gamepadConnected, gamepadIgnored, gamepad, newState;

    vector<WindowBox> windowsbox;
    int axisUp, axisDown;
private:
    GamePadManager();
    GamePadManager(const GamePadManager& orig);
    std::string to_string(int string);
    virtual ~GamePadManager();
    static GamePadManager* m_pInstance;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & buttons;
        ar & keys;
        ar & gamepad;
        ar & nbrButtons;
    }
    sf::RenderWindow window;
    Time time;
#ifdef __linux
    float fakeKeyLastTime;
    sf::Clock fakeKeyClock;
#endif
    string controlFile;

};

#endif	/* GAMEPADMANAGER_H */

