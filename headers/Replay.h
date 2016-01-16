/* 
 * File:   Replay.h
 * Author: jacques belosoukinski
 *
 * Created on 31 mars 2013, 22:18
 */

#ifndef REPLAY_H
#define	REPLAY_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SFML/Graphics.hpp>
#include "GameTime.h"

using sf::Joystick;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::vector;

class Replay {
public:
    static Replay* Instance();
    std::vector<vector<unsigned int>> action;
    vector<float> time;
    void getData();
    void saveData();

private:
    Replay();
    Replay(const Replay& orig);
    virtual ~Replay();
    static Replay* m_pInstance;
    int count;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & action;
        ar & time;
    }
    std::string replayFile;
};

#endif	/* REPLAY_H */

