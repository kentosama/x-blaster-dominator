/* 
 * File:   Capture.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 26 avril 2013, 19:12
 */

#include <sstream>

#include "Capture.h"

Capture::Capture() {
    count = 1;
    randCount = rand() % 10000 + 29999;
    loop = false;
    lastTime = 0;
    time = sf::seconds(5);
#ifdef _DEBUG
    version = "-debug";
#elif _BETA
    version = "-beta";
#else 
    version = "-release";

#endif

#ifdef _WIN32
    version = version + "-win32";
#elif _WIN64
    version = version + "-win64";
#elif __linux
    version = version + "-linux";
#endif
#if defined _WIN32 || WIN64
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    pathFile = strcat(path, "\\Games\\X-Blaster Dominator\\screenshots");
    boost::filesystem::path dir(pathFile);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);
    
#elif __linux
    path = "screenshots/capture-" + std::to_string(count) + std::to_string(randCount) + version + ".png";
#endif
}

Capture::Capture(const Capture& orig) {
}

Capture::~Capture() {
}

void Capture::update() {
    
            if (WindowGame::Instance()->event.type == WindowGame::Instance()->event.KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
                    save();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) {
                    save();
                    if (!loop)
                    loop = true;
                    else loop = false;
                }
            }
            
            if (loop) {
                
                if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {
                    lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
                    save();
                }
            }
}

void Capture::save() {
#if defined _WIN32 || defined _WIN64
    if (boost::filesystem::exists(pathFile)) {
        count += 1;
       
        
        path = pathFile + "\\capture-" + to_string(count) + to_string(randCount) + version + ".png";
    }
#elif __linux

    if (boost::filesystem::exists(path)) {
        count += 1;
        path = "screenshots/capture-" + std::to_string(count) + std::to_string(randCount) + version + ".png";
    }
#endif

    if (WindowGame::Instance()->window.capture().saveToFile(path));
                std::cout << "Image saved at " + path << std::endl;
}

std::string Capture::to_string(int string) {
    std::stringstream ss;
    ss << string;
    return ss.str();
}