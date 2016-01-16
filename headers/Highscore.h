/* 
 * File:   Highscore.h
 * Author: jacques belosoukinski
 *
 * Created on 19 mars 2013, 20:28
 */

#ifndef HIGHSCORE_H
#define	HIGHSCORE_H
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
#ifdef __linux
#include <sys/types.h>
#include <pwd.h>
#else
#include <shlobj.h>
#include <windows.h>
#endif
#include "Profil.h"
#include "MessageManager.h"

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::vector;

class Highscore {
public:
    static Highscore* Instance();

    class Scoring {
    public:
    string playername, stage;
    int score, enemydead;
    unsigned char mode;
    
    };
    
    void open();
    void save();
    void create();
    vector<Scoring> scoring;
    vector<string> language;
    
private:
    Highscore();
    Highscore(const Highscore& orig);
    virtual ~Highscore();
    static Highscore* m_pInstance;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & scoring;
        
    }
    
    string highscore;


};

#endif	/* HIGHSCORE_H */

