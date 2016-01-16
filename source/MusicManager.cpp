/* 
 * File:   MusicManager.cpp
 * Author: belosoukinski jacques (shingo san)
 * 
 * Created on 3 septembre 2013, 10:31
 */

#include "MusicManager.h"

MusicManager* MusicManager::mp_Instance = NULL;

MusicManager* MusicManager::Instance() {
    if (!mp_Instance)
        mp_Instance = new MusicManager;
    return mp_Instance;
}

MusicManager::MusicManager() {
    player.setLoop(true);
    files.reserve(10);
    std::string path = "content/music/";
    for (unsigned char i = 0; i < 10; i++) {
        files.emplace_back();
        files[i] = path + "music-" + to_string(i+1) + ".dat";
    }
    
    creditPlayer.openFromFile(files[8]);
    creditPlayer.setVolume(100);
    creditPlayer.setLoop(false);
    lastTime = 0;
    volume = 0;
    fadingOut = false;
    fadingIn = false;
    gamePause = false;
}

MusicManager::MusicManager(const MusicManager& orig) {
}

MusicManager::~MusicManager() {
}

bool MusicManager::stopped() {
    if(player.getStatus() == 0)
        return true;
    else return false;
}

bool MusicManager::paused() {
    if(player.getStatus() == 1)
        return true;
    else return false;
}

unsigned char MusicManager::getVolume() {
    return player.getVolume();
}

unsigned char MusicManager::getCurrentMusic() {
    return music;
}

void MusicManager::play(unsigned char music, unsigned char volume, bool fading = true) {
    
    player.stop();

    if(!player.openFromFile(files[music]))
        ErrorManager::Instance()->save(3, "File missing : " + files[music]);
    
    if(!fading) {
        player.setVolume(volume);
    } else {
        this->volume = 0;
        player.setVolume(this->volume);
        setVolume = volume;
        fadingIn = true;
        lastTime = 0;
    }
    
    this->music = music;
    player.play();
}

void MusicManager::playCredit() {
    gamePause = true;
    creditPlayer.play();
}

void MusicManager::stopCredit() {
    creditPlayer.stop();
    gamePause = false;
}

void MusicManager::fadeOut() {
    if (!stopped()) {
        if(this->volume <= 0) {
            fadingOut = false;
            volume = 0;
        } else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 20) {
            this->volume -= 1;
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            player.setVolume(this->volume);
        }
    }
}

void MusicManager::fadeIn(unsigned char setVolume) {
    if (this->volume == setVolume) {
        fadingIn = false;
    } else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 20) {
        this->volume += 1;
        player.setVolume(this->volume);
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    } 
}

void MusicManager::update() {
    if (WindowGame::Instance()->focus && paused() && !gamePause) {
        player.play();
    } else if ((!WindowGame::Instance()->focus && !paused()) || gamePause)
        player.pause();
    
    if(fadingOut)
        fadeOut();
    else if(fadingIn)
        fadeIn(setVolume);
    
    
}

std::string MusicManager::to_string(int string) {
    std::stringstream ss;
    ss << string;
    return ss.str();
}
