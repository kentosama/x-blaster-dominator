/* 
 * File:   Profil.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 8 mars 2013, 09:18
 */

#include "Profil.h"

Profil* Profil::m_pInstance = NULL;

Profil* Profil::Instance() {
    if (!m_pInstance)
        m_pInstance = new Profil;
    return m_pInstance;
}

Profil::Profil() {

    setLanguage();

#ifdef __linux
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    string pathProfil = string(homedir) + "/.config/x-blasterdominator/";
#else
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string pathProfil = strcat(path, "\\My Games\\X-Blaster Dominator\\");
#endif

    boost::filesystem::path dir(pathProfil);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);
    profil = pathProfil + "profil.dat";

    bestScore.reserve(5);
    for (unsigned char i = 0; i < 5; i++)
        bestScore.emplace_back();

    newProfil = false;
}

Profil::Profil(const Profil& orig) {
}

Profil::~Profil() {

}

void Profil::setLanguage() {

    if (Language::Instance()->language != "english")
        messageText = Language::Instance()->french[2];
    else messageText = Language::Instance()->english[2];

}

void Profil::open() {
    ifstream file(profil);
    if (file.is_open()) {
#ifdef _DEBUG
        boost::archive::text_iarchive open(file);
#elif defined _RELEASE || _BETA
        boost::archive::binary_iarchive open(file);
#endif
        open >> playername;
        open >> mode;
        open >> fullscreen;
        open >> credits;
        open >> lastScore;
        open >> enemyDead;
        open >> gameover;
        open >> totalTime;

        for (int i = 0; i < 5; i++)
            open >> bestScore[i];
        file.close();
       
            MessageManager::Instance()->addMessage(1, 0);
    } else {
        newProfil = true;
        create();
    }

}

void Profil::save() {

    ifstream file(profil);
    if (file.is_open()) {
        ofstream file(profil);
#ifdef _DEBUG
        boost::archive::text_oarchive save(file);
#elif defined _RELEASE || _BETA
        boost::archive::binary_oarchive save(file);
#endif
        save << playername;
        save << mode;
        save << fullscreen;
        save << credits;
        save << lastScore;
        save << enemyDead;
        save << gameover;
        save << totalTime;
        for (int i = 0; i < 5; i++)
            save << bestScore[i];
        MessageManager::Instance()->addMessage(2, 0);
    } else {
        create();
    }

    file.close();
}

void Profil::create() {
#ifdef __linux
    struct passwd *pw = getpwuid(getuid());
    playername = pw->pw_name;
#elif defined _WIN32 || _WIN64
    char username[255];
    DWORD USERNAME = sizeof (username);
    if (GetUserName(username, &USERNAME))
        playername = username;
#endif

    mode = 1;
    fullscreen = false;
    credits = 0;
    lastScore = 0;
    enemyDead = 0;
    gameover = 0;
    totalTime = 0;
    for (int i = 0; i < 5; i++)
        bestScore[i] = 0;

    ofstream file(profil);
#ifdef _DEBUG
    boost::archive::text_oarchive save(file);
#elif defined _RELEASE || _BETA
    boost::archive::binary_oarchive save(file);
#endif

    save << playername;
    save << mode;
    save << fullscreen;
    save << credits;
    save << lastScore;
    save << enemyDead;
    save << gameover;
    save << totalTime;
    for (int i = 0; i < 5; i++)
        save << bestScore[i];
   
       MessageManager::Instance()->addMessage(0, 0);
    file.close();
}

