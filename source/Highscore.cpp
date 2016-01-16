/* 
 * File:   Highscore.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 19 mars 2013, 20:28
 */

#include "Highscore.h"

Highscore* Highscore::m_pInstance = NULL;

Highscore* Highscore::Instance() {
    if (!m_pInstance)
        m_pInstance = new Highscore;
    return m_pInstance;
}

Highscore::Highscore() {
#ifdef __linux
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    string pathFile = string(homedir) + "/.local/share/x-blasterdominator/";
    highscore = "highscore.dat";
    
#elif defined _WIN32 || _WIN64
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string pathFile = strcat(path, "\\my games\\X-Blaster Dominator\\");
#endif
    boost::filesystem::path dir(pathFile);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);
    highscore = pathFile + "highscore.dat";
    
    if (Profil::Instance()->language == "English")
        language = Language::Instance()->english[2];
    else language = Language::Instance()->french[2];
   
    scoring.reserve(14);
    for (int i = 0; i < 14; i++)
        scoring.emplace_back();
}

Highscore::Highscore(const Highscore& orig) {
}

Highscore::~Highscore() {
}

void Highscore::open() {
    ifstream file(highscore);
    if (file.is_open()) {

#ifdef _DEBUG
            boost::archive::text_iarchive open(file);
#elif defined _RELEASE || _BETA
            boost::archive::binary_iarchive open(file);
#endif

            for (int i = 0; i < 14; i++) {
                open >> scoring[i].playername;
                open >> scoring[i].stage;
                open >> scoring[i].mode;
                open >> scoring[i].score;
                open >> scoring[i].enemydead;
            }

        } else create();
    }

void Highscore::create() {
    scoring[0].playername = "Shingo";
    scoring[0].stage = "Stage 5";
    scoring[0].mode = 0;
    scoring[0].score = 789550;
    scoring[0].enemydead = 1000;

    scoring[1].playername = "Lordy";
    scoring[1].stage = "Stage 5";
    scoring[1].mode = 0;
    scoring[1].score = 761900;
    scoring[1].enemydead = 1000;

    scoring[2].playername = "Bunta";
    scoring[2].stage = "Stage 5";
    scoring[2].mode = 0;
    scoring[2].score = 731100;
    scoring[2].enemydead = 1000;

    scoring[3].playername = "DanteDMC1";
    scoring[3].stage = "Stage 5";
    scoring[3].mode = 0;
    scoring[3].score = 719800;
    scoring[3].enemydead = 1000;

    scoring[4].playername = "Gosuke";
    scoring[4].stage = "Stage 5";
    scoring[4].mode = 0;
    scoring[4].score = 705200;
    scoring[4].enemydead = 1000;

    scoring[5].playername = "Galax";
    scoring[5].stage = "Stage 5";
    scoring[5].mode = 1;
    scoring[5].score = 6613510;
    scoring[5].enemydead = 1000;

    scoring[6].playername = "Eiko";
    scoring[6].stage = "Stage 4";
    scoring[6].mode = 1;
    scoring[6].score = 652200;
    scoring[6].enemydead = 1000;

    scoring[7].playername = "Jason";
    scoring[7].stage = "Stage 4";
    scoring[7].mode = 1;
    scoring[7].score = 643400;
    scoring[7].enemydead = 1000;

    scoring[8].playername = "Eloyz";
    scoring[8].stage = "Stage 4";
    scoring[8].mode = 1;
    scoring[8].score = 564000;
    scoring[8].enemydead = 1000;

    scoring[9].playername = "Philips";
    scoring[9].stage = "Stage 4";
    scoring[9].mode = 1;
    scoring[9].score = 525530;
    scoring[9].enemydead = 1000;

    scoring[10].playername = "Shingo";
    scoring[10].stage = "Stage 3";
    scoring[10].mode = 1;
    scoring[10].score = 507500;
    scoring[10].enemydead = 1000;

    scoring[11].playername = "Shingo";
    scoring[11].stage = "Stage 3";
    scoring[11].mode = 1;
    scoring[11].score = 487500;
    scoring[11].enemydead = 1000;

    scoring[12].playername = "Shingo";
    scoring[12].stage = "Stage 3";
    scoring[12].mode = 2;
    scoring[12].score = 479100;
    scoring[12].enemydead = 1000;

    scoring[13].playername = "Shingo";
    scoring[13].stage = "Stage 2";
    scoring[13].mode = 2;
    scoring[13].score = 426900;
    scoring[13].enemydead = 1000;

    ofstream file(highscore);
#ifdef _DEBUG
    boost::archive::text_oarchive save(file);
#elif defined _RELEASE || _BETA
    boost::archive::binary_oarchive save(file);
#endif
    for (int i = 0; i < 14; i++) {
        save << scoring[i].playername;
        save << scoring[i].stage;
        save << scoring[i].mode;
        save << scoring[i].score;
        save << scoring[i].enemydead;
    }
    
    MessageManager::Instance()->addMessage(3,0);
    
    file.close();
    

}

void Highscore::save() {

    ifstream file(highscore);
    if (file.is_open()) {
        ofstream file(highscore);
#ifdef _DEBUG
        boost::archive::text_oarchive save(file);
#elif _RELEASE || _BETA
        boost::archive::binary_oarchive save(file);
#endif

        for (int i = 0; i < 14; i++) {
            save << scoring[i].playername;
            save << scoring[i].stage;
            save << scoring[i].mode;
            save << scoring[i].score;
            save << scoring[i].enemydead;
        }
    } else {
        create();
    }

    file.close();
}
