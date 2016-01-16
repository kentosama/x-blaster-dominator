/* 
 * File:   Replay.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 31 mars 2013, 22:18
 */

#include "Replay.h"


Replay* Replay::m_pInstance = NULL;

Replay* Replay::Instance() {
    if (!m_pInstance)
        m_pInstance = new Replay;
    return m_pInstance;
}

Replay::Replay() {
    
    for (unsigned char i = 0; i < 100; i++) {
        action.emplace_back();
        action[i].emplace_back();
        time.emplace_back();
    }
    count = 0;
    replayFile = "replay.dat";
}

Replay::Replay(const Replay& orig) {
}

Replay::~Replay() {
}

void Replay::getData() {
    
    if (Joystick::isConnected(0)) {
        
        if (Joystick::getAxisPosition(0, Joystick::X) > 0) {
            count +=1;
            action[count][count] = 1;
            time[count] = GameTime::Instance()->getElapsedTime().asMilliseconds();
            std::cout << action[count][count] << std::endl;
            saveData();

        }
    }
}

void Replay::saveData() {
    
   
        ofstream file(replayFile);
        boost::archive::text_oarchive save(file);
        
        for (unsigned char i = 0; i < 100; i++) { 
        save << action[i][i];
        save << time[i];
        }
    
    
    file.close();
}

