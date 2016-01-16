/* 
 * File:   GamePadManager.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 24 mars 2013, 07:33
 */

#include "GamePadManager.h"

GamePadManager* GamePadManager::m_pInstance = NULL;

GamePadManager* GamePadManager::Instance() {
    if (!m_pInstance)
        m_pInstance = new GamePadManager;
    return m_pInstance;
}

GamePadManager::GamePadManager() {
#ifdef __linux
    fakeKeyLastTime = 0;
#endif
    axisDown = -50;
    axisUp = 50;
    newState = false;
    windowsbox.reserve(1);
    time = sf::seconds(0.2);
    previousTime = 0;
    setting = 0;
    gamepadConnected = false;
    gamepadIgnored = false;
#ifdef __linux
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    controlFile = string(homedir) + "/.config/x-blasterdominator/control.dat";
#elif defined _WIN32 || _WIN64
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string pathFile = strcat(path, "\\My Games\\X-Blaster Dominator\\");
    boost::filesystem::path dir(pathFile);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);

    controlFile = pathFile + "control.dat";

#endif

    buttons.reserve(4);
    keys.reserve(4);
    for (unsigned char i = 0; i < 4; i++) {
        buttons.emplace_back();
        keys.emplace_back();
    }
}

GamePadManager::GamePadManager(const GamePadManager& orig) {
}

GamePadManager::~GamePadManager() {
}

unsigned int GamePadManager::getButtons() {
    int buttons;
    if (Joystick::isConnected(0)) {
        buttons = Joystick::getButtonCount(0);
    } else buttons = 0;
    return buttons;
}

bool GamePadManager::gamepadMoved() {
    if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickMoved)
        return true;
    else return false;
}

bool GamePadManager::gamepadPressed() {
    if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickButtonPressed)
            return true;
        else return false;
}

bool GamePadManager::keyboardPressed() {
    while (WindowGame::Instance()->window.pollEvent(WindowGame::Instance()->event)) {
        if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.KeyPressed)
            return true;
        else return false;
    }
}

void GamePadManager::setButtons() {
    unsigned char buttons = getButtons();
    if (Joystick::isConnected(0)) {
        gamepad = true;
        nbrButtons = getButtons();
        if (buttons >= 12) {
            this->buttons[0] = 0;
            this->buttons[1] = 1;
            this->buttons[2] = 8;
            this->buttons[3] = 9;
        } else if (buttons < 12 && buttons > 3) {
            this->buttons[0] = 1;
            this->buttons[1] = 2;
            this->buttons[2] = 3;
            this->buttons[3] = 0;
        } else if (buttons < 4) {
            std::cout << "Your controller is not compatible. It has buttons " << to_string(buttons) << "." << std::endl;
            gamepadIgnored = true;
            gamepad = false;
            gamepadConnected = false;
        }
    }
    else {
        std::cout << "No controller detected." << std::endl;
        gamepad = false;
        gamepadConnected = false;
    }
    keys[0] = Keyboard::LControl;
    keys[1] = Keyboard::LShift;
    keys[2] = Keyboard::Space;
    keys[3] = Keyboard::Return;
}

void GamePadManager::setControl() {
    if (previousTime == 0)
        previousTime = GameTime::Instance()->getElapsedTime().asMilliseconds();

    if (GameTime::Instance()->getElapsedTime().asMilliseconds() - previousTime > 500) {

        if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickButtonPressed) {
            if (setting == 0) {
                buttons[0] = WindowGame::Instance()->event.joystickButton.button;
#ifdef _DEBUG
                std::cout << "Fire Button : " << WindowGame::Instance()->event.joystickButton.button << std::endl;
#endif
                setting += 1;
            } else if (setting == 1) {
                if (WindowGame::Instance()->event.joystickButton.button != buttons[0]) {
                    buttons[1] = WindowGame::Instance()->event.joystickButton.button;
#ifdef _DEBUG
                    std::cout << "Secondary Fire Button : " << WindowGame::Instance()->event.joystickButton.button << std::endl;
#endif
                    setting += 1;
                }

            } else if (setting == 2) {
                if (WindowGame::Instance()->event.joystickButton.button != buttons[1] && WindowGame::Instance()->event.joystickButton.button != buttons[0]) {
                    buttons[3] = WindowGame::Instance()->event.joystickButton.button;
#ifdef _DEBUG
                    std::cout << "Start Button : " << WindowGame::Instance()->event.joystickButton.button << std::endl;
#endif
                    setting += 1;
                }

            } else if (setting == 3) {
                if (WindowGame::Instance()->event.joystickButton.button != buttons[0] && WindowGame::Instance()->event.joystickButton.button != buttons[1] && WindowGame::Instance()->event.joystickButton.button != buttons[3]) {
                    buttons[2] = WindowGame::Instance()->event.joystickButton.button;
#ifdef _DEBUG
                    std::cout << "Select Button : " << WindowGame::Instance()->event.joystickButton.button << std::endl;
#endif
                    setting += 1;
                }

            }

            previousTime = 0;

        }

    }
}

void GamePadManager::setKeyboard() {
    while (WindowGame::Instance()->window.pollEvent(WindowGame::Instance()->event)) {

        if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.KeyPressed) {
            if (setting == 0) {
                keys[0] = WindowGame::Instance()->event.key.code;
#ifdef _DEBUG
                std::cout << "Fire Key : " << WindowGame::Instance()->event.key.code << std::endl;
#endif
                setting += 1;
            } else if (setting == 1) {
                if (WindowGame::Instance()->event.key.code != keys[0]) {
                    keys[1] = WindowGame::Instance()->event.key.code;
#ifdef _DEBUG
                    std::cout << "Secondary Fire Button : " << WindowGame::Instance()->event.key.code << std::endl;
#endif
                    setting += 1;
                }
            } else if (setting == 2) {
                if (WindowGame::Instance()->event.key.code != keys[1] && WindowGame::Instance()->event.key.code != keys[0]) {
                    keys[3] = WindowGame::Instance()->event.key.code;
#ifdef _DEBUG
                    std::cout << "Secondary Fire Button : " << WindowGame::Instance()->event.key.code << std::endl;
#endif
                    setting += 1;
                }
            } else if (setting == 3) {
                if (WindowGame::Instance()->event.key.code != keys[1] && WindowGame::Instance()->event.key.code != keys[0] && WindowGame::Instance()->event.key.code != keys[3]) {
                    keys[2] = WindowGame::Instance()->event.key.code;
#ifdef _DEBUG
                    std::cout << "Secondary Fire Button : " << WindowGame::Instance()->event.key.code << std::endl;
#endif
                    setting += 1;
                }
            }

        }
    }
}

void GamePadManager::open() {
    if (Joystick::isConnected(0))
        gamepadConnected = true;
    else gamepadConnected = false;

    ifstream file(controlFile);
    if (file.is_open()) {
#ifdef _DEBUG
        boost::archive::text_iarchive open(file);
#elif defined _RELEASE || _BETA
        boost::archive::binary_iarchive open(file);
#endif

        for (unsigned char i = 0; i < 4; i++) {
            open >> gamepad;
            open >> nbrButtons;
            open >> buttons[i];
            open >> keys[i];
        }
        file.close();
    } else create();
    
    if (!gamepad) {
        setButtons();
        save();
    }
}

void GamePadManager::save() {

    ifstream file(controlFile);
    if (file.is_open()) {
        ofstream file(controlFile);
#ifdef _DEBUG
    boost::archive::text_oarchive save(file);
#elif defined _RELEASE || _BETA
    boost::archive::binary_oarchive save(file);
#endif
        for (unsigned char i = 0; i < 4; i++) {
            save << gamepad;
            save << nbrButtons;
            save << buttons[i];
            save << keys[i];
        }
    }
    file.close();
}

void GamePadManager::create() {

    ofstream file(controlFile);
#ifdef _DEBUG
    boost::archive::text_oarchive save(file);
#elif defined _RELEASE || _BETA
    boost::archive::binary_oarchive save(file);
#endif


    setButtons();

    for (unsigned char i = 0; i < 4; i++) {
        save << gamepad;
        save << nbrButtons;
        save << buttons[i];
        save << keys[i];
    }

    file.close();
}

void GamePadManager::update() {
    
    if (!gamepadConnected) {

        if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickConnected) {
            unsigned char buttons = getButtons();
            if ((buttons < 4 && buttons > 0) || buttons == 0) {
#ifdef _DEBUG
                std::cout << "Your controller is not compatible. He has buttons " << to_string(buttons) << "." << std::endl;
#endif
                if (!gamepadIgnored)
                gamepadIgnored = true;
            } else {
                MessageManager::Instance()->addMessage(4, 0);
                if(gamepad == false || buttons != nbrButtons)
                    setButtons();
                gamepadConnected = true;
                newState = false;
            }
        }
    } else if (gamepadConnected) {

        if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.JoystickDisconnected) {
            MessageManager::Instance()->addMessage(4, 0);
            gamepadConnected = false;
            newState = true;
        }
    } 
} 

#ifdef __linux 
void GamePadManager::fakeKey() {
    if (fakeKeyClock.getElapsedTime().asMilliseconds() - fakeKeyLastTime > 5000) {
        system("xscreensaver-command -deactivate > /dev/null");
        fakeKeyLastTime = fakeKeyClock.getElapsedTime().asMilliseconds();
    }
}
#endif

std::string GamePadManager::to_string(int string) {
    std::stringstream ss;
    ss << string;
    return ss.str();
}
