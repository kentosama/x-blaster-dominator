/* 
 * File:   MusicManager.h
 * Author: shingo
 *
 * Created on 3 septembre 2013, 10:31
 */

#ifndef MUSICMANAGER_H
#define	MUSICMANAGER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#include "GameTime.h"
#include "ErrorManager.h"

class MusicManager {
public:
    static MusicManager* Instance();
    void play(unsigned char music, unsigned char volume, bool fading);
    void playCredit();
    void stopCredit();
    void fadeOut();
    void fadeIn(unsigned char volume);
    void update();
    bool stopped();
    bool paused();
    unsigned char getVolume();
    unsigned char getCurrentMusic();
    sf::Music player;
    sf::Music creditPlayer;
    bool fadingOut, fadingIn, gamePause;
private:
    std::string to_string(int string);
    MusicManager();
    MusicManager(const MusicManager& orig);
    virtual ~MusicManager();
    static MusicManager* mp_Instance;
    std::vector<std::string> files;
    float lastTime;
    unsigned char volume, setVolume, music;

};

#endif	/* MUSICMANAGER_H */

