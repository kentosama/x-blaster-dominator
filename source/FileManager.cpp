/* 
 * File:   FileManager.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 22 mars 2013, 22:05
 */

#include "FileManager.h"

FileManager* FileManager::m_pInstance = NULL;

FileManager* FileManager::Instance() {
    if (!m_pInstance)
        m_pInstance = new FileManager;
    return m_pInstance;
}

FileManager::FileManager() {
    artworks.reserve(3);
    title.reserve(3);
    player.reserve(3);
    howtoMin.reserve(4);
    boss.reserve(4);
    backgrounds.reserve(5);
    sndStage.reserve(5);
    logo.reserve(5);
    bullets.reserve(5);
    text.reserve(6);
    ecumes.reserve(6);
    sound.reserve(9);
    items.reserve(9);
    menu.reserve(13);
    enemies.reserve(16);
    

    for (unsigned char i = 0; i < 16; i++) {
        if (i < 3) {
            artworks.reserve(3); 
            title.emplace_back();
             player.emplace_back();
        }

        if (i < 4) {
            howtoMin.emplace_back();
            
            boss.emplace_back();
        }

        if (i < 5) {
            backgrounds.emplace_back();
            sndStage.emplace_back();
            logo.emplace_back();
            bullets.emplace_back();
        }

        if (i < 6) {
            text.emplace_back();
            ecumes.emplace_back();
        }
        
        if (i < 9) {
            sound.emplace_back();
            items.emplace_back();
        }

        if (i < 13) {
            menu.emplace_back();
        }

        if (i < 16) {
            enemies.emplace_back();
        }
    }

    backgrounds[0].reserve(5);

    for (unsigned char i = 1; i < 5; i++)
        backgrounds[i].reserve(4);

    for (unsigned char i = 0; i < 5; i++)
        backgrounds[0].emplace_back();

    for (unsigned char i = 1; i < 5; i++) {
        for (unsigned char a = 0; a < 4; a++)
            backgrounds[i].emplace_back();
    }
}

FileManager::FileManager(const FileManager& orig) {
}

FileManager::~FileManager() {

}

void FileManager::loadcontent() {

    unsigned char count = 0;
    for (unsigned char i = 0; i < 16; i++) {
        count += 1;
        
        if (i < 3) {
            if (!artworks[i].loadFromFile(pathArtworks + "artwork-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : artwork-" + to_string(count) + dat);
            
            if (!title[i].loadFromFile(pathTitle + "title-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : title-" + to_string(count) + dat);
            
            if (!player[i].loadFromFile(pathPlayer + "player-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : player-" + to_string(count) + dat);
        }

        if (i < 4) {
           
            if (!howtoMin[i].loadFromFile(pathMenu + "thumb-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : thumb-" + to_string(count) + dat);
            if (!backgrounds[1][i].loadFromFile(pathBackground + "file-2-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : file-2-" + to_string(count) + dat);
            if (!backgrounds[2][i].loadFromFile(pathBackground + "file-3-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : file-3-" + to_string(count) + dat);
            if (!backgrounds[3][i].loadFromFile(pathBackground + "file-4-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : file-4-" + to_string(count) + dat);
            if (!backgrounds[4][i].loadFromFile(pathBackground + "file-5-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathBackground + "file-5-" + to_string(count) + dat);
            if (!boss[i].loadFromFile(pathBoss + "boss-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : boss-" + to_string(count) + dat);
            
        }
        if (i < 5) {
            if (!backgrounds[0][i].loadFromFile(pathBackground + "file-1-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathBackground + "file-1-" + to_string(count) + dat);

            if (!logo[i].loadFromFile(pathMenu + "logo-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathMenu + "logo-" + to_string(count) + dat);

            if (!sndStage[i].loadFromFile(pathSound + "voice-" + to_string(count) + dat))
                ErrorManager::Instance()->save(2, "File missing : " + pathSound + "stage" + to_string(count) + dat);

            if (!bullets[i].loadFromFile(pathBullet + "bullet-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathBullet + "bullet-" + to_string(count) + dat);
        }

        if (i < 6) {
            if (!ecumes[i].loadFromFile(pathBackground + "effect-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathBackground + "effect-" + to_string(count) + dat);

            if (!text[i].loadFromFile(pathText + "text-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathText + "text-" + to_string(count) + dat);
        }

        if (i < 9) {
            if (!sound[i].loadFromFile(pathSound + "sound-" + to_string(count) + dat))
                ErrorManager::Instance()->save(2, "File missing : " + pathSound + "sound-" + to_string(count) + dat);
            
            if (!items[i].loadFromFile(pathItem + "item-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathItem + "item" + to_string(count) + dat);
        }

        if (i < 13) {
            if (!menu[i].loadFromFile(pathMenu + "item-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathMenu + "item-" + to_string(count) + dat);
        }

        if (i < 16) {
            if (!enemies[i].loadFromFile(pathEnemies + "enemy-" + to_string(count) + dat))
                ErrorManager::Instance()->save(1, "File missing : " + pathEnemies + "enemy-" + to_string(count) + dat);
        }
    }

    windowbox.loadFromFile(pathTextures + "texture-1.dat");
    general.loadFromFile(pathTextures + "texture-2.dat");
    fade.loadFromFile(pathTextures + "texture-3.dat");
    hud.loadFromFile(pathTextures + "texture-4.dat");
    pilot.loadFromFile(pathTextures + "texture-5.dat");
   
    
    loaded = true;
    
}

std::string FileManager::to_string(int string) {
    std::stringstream ss;
    ss << string;
    return ss.str();
}