/* 
 * File:   FileManager.h
 * Author: jacques belosoukinski
 *
 * Created on 22 mars 2013, 22:05
 */

#ifndef FILEMANAGER_H
#define	FILEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "ErrorManager.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::vector;
using sf::Texture;
using sf::Font;
using sf::SoundBuffer;

class FileManager {
public:
    static FileManager* Instance();
    void create();
    void loadcontent();
    Texture general;
    Texture windowbox;
    Texture fade;
    Texture hud;
    Texture pilot;
    vector<Texture> title;
    vector<Texture> menu;
    vector<Texture> logo;
    vector<Texture> enemies;
    vector<Texture> boss;
    vector<Texture> items;
    vector<Texture> player;
    vector<Texture> bullets;
    vector<Texture> ecumes;
    vector<Texture> text;
    vector<Texture> howtoMin;
    vector<vector<Texture>> backgrounds;
    vector<Texture> artworks;
    vector<SoundBuffer>sound;
    vector<SoundBuffer> sndStage;
    bool loaded = false;
    string font = "content/font/font.dat";
private:
    FileManager();
    FileManager(const FileManager& orig);
    virtual ~FileManager();
    static FileManager* m_pInstance;
    std::string to_string(int string);
    // Répertoires
    string pathContent = "content/";
    string pathTextures = pathContent + "textures/";
    string pathEnemies = pathTextures + "enemies/";
    string pathBoss = pathTextures + "boss/";
    string pathPlayer = pathTextures + "player/";
    string pathBullet = pathTextures + "bullets/";
    string pathTitle = pathTextures + "titles/";
    string pathMenu = pathTextures + "menu/";
    string pathSound = pathContent + "sound/";
    string pathBackground = pathTextures + "backgrounds/";
    string pathText = pathTextures + "text/";
    string pathItem = pathTextures + "items/";
    string pathArtworks = pathTextures + "artworks/";
    string png = ".png";
    string wav = ".wav";
    string dat = ".dat";
};

#endif	/* FILEMANAGER_H */

