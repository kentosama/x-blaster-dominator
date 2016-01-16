/* 
 * File:   Profil.h
 * Author: jacques belosoukinski
 *
 * Created on 8 mars 2013, 09:18
 */

#ifndef PROFIL_H
#define	PROFIL_H
#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#elif defined _RELEASE || _BETA
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include "Language.h"

#ifdef __linux
#include <sys/types.h>
#include <pwd.h>
#else
#include <shlobj.h>
#include <windows.h>
#endif
#include "MessageManager.h"

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using sf::Sprite;
using sf::Texture;

class Profil {
public:
    static Profil* Instance();
    void setLanguage();
    void save();
    void open();
    void create();
    string playername, language;
    bool fullscreen, newProfil;
    int lastScore, enemyDead, gameover;
    int totalTime;
    unsigned char mode, credits;
    vector<int> bestScore;
    vector<string> messageText;
    
private:
    Profil();
    Profil(const Profil& orig);
    virtual ~Profil();
    static Profil* m_pInstance;
    string getGenericDirectory(const char* ENVVAR, const string fallback);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & language;
        ar & mode;
        ar & playername;
        ar & fullscreen;
        ar & credits;
        ar & lastScore;
        ar & enemyDead;
        ar & gameover;
        ar & totalTime;
        ar & bestScore;

    }
    string profil;
    
    
        
        

};

#endif	/* PROFIL_H */

