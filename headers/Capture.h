/* 
 * File:   Capture.h
 * Author: jacques belosoukinski
 *
 * Created on 26 avril 2013, 19:12
 */

#ifndef CAPTURE_H
#define	CAPTURE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#ifdef __linux
#include <sys/types.h>
#include <pwd.h>
#include <boost/filesystem.hpp>
#elif defined _WIN32 || _WIN64
#include <shlobj.h>
#include <windows.h>
#include <boost/filesystem.hpp>
#endif
#include "GameTime.h"
#include "WindowGame.h"

class Capture {
public:
    Capture();
    Capture(const Capture& orig);
    virtual ~Capture();
    void update();
    void save();
    
private:
    std::string to_string(int string);
    bool loop;
    unsigned char count;
    unsigned int randCount;
    float lastTime;
    sf::Time time;
    std::string version;
    std::string path, pathFile;
};



#endif	/* CAPTURE_H */

