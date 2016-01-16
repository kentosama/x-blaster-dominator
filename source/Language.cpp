/* 
 * File:   Language.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 26 mars 2013, 09:13
 */

#include "Language.h"

Language* Language::m_pInstance = NULL;

Language* Language::Instance() {
    if (!m_pInstance)
        m_pInstance = new Language;
    return m_pInstance;
}

Language::Language() {
#ifdef __linux 
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    string pathFile = string(homedir) + "/.config/x-blasterdominator/";
#elif _WIN32 || _WIN64
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string pathFile = strcat(path, "\\My Games\\X-Blaster Dominator\\");
#endif
    boost::filesystem::path dir(pathFile);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);
    languageFile = pathFile + "language.dat";
    english.reserve(11);
    french.reserve(11);
    
    for (unsigned char i = 0; i < 11; i++) {
        english.emplace_back();
        french.emplace_back();
    }
        
    // Menu
    unsigned char const menu = 37;
    english[0].reserve(menu);
    french[0].reserve(menu);

    for (unsigned char i = 0; i < menu; i++) {
        english[0].emplace_back();
        french[0].emplace_back();
    }

    // Langues
    english[1].reserve(2);
    french[1].reserve(2);

    for (unsigned char i = 0; i < 2; i++) {
        english[1].emplace_back();
        french[1].emplace_back();
    }

    // MessageBox du profil
    english[2].reserve(5);
    french[2].reserve(5);

    for (unsigned char i = 0; i < 5; i++) {
        english[2].emplace_back();
        french[2].emplace_back();
    }

    // Hud
    english[3].reserve(5);
    french[3].reserve(5);
    
    english[7].reserve(5);
    french[7].reserve(5);
    
    

    for (unsigned char i = 0; i < 5; i++) {
        english[3].emplace_back();
        french[3].emplace_back();
        english[7].emplace_back();
        french[7].emplace_back();
    }

    // Messages en cours de jeu
    english[4].reserve(2);
    french[4].reserve(2);

    for (unsigned char i = 0; i < 2; i++) {
        english[4].emplace_back();
        french[4].emplace_back();
    }

    // Pause
    english[5].reserve(4);
    french[5].reserve(4);

    for (unsigned char i = 0; i < 4; i++) {
        english[5].emplace_back();
        french[5].emplace_back();
    }

    english[6].reserve(6);
    french[6].reserve(6);

    for (unsigned char i = 0; i < 6; i++) {
        english[6].emplace_back();
        french[6].emplace_back();
    }


    english[8].reserve(8);
    french[8].reserve(8);

    for (unsigned char i = 0; i < 9; i++) {

        english[8].emplace_back();
        french[8].emplace_back();


    }

    names.reserve(7);
    for (unsigned char i = 0; i < 7; i++)
        names.emplace_back();

    names[0] = "Jacques BELOSOUKINSKI";
    names[1] = "Patrice M";
    names[2] = "Syvlain DEURVEILHER";
    names[3] = "Sylvain LECONTE";
    names[4] = "Pierre-Emmanuel Zirou";
    names[5] = "Justine MAISONNEUVE";
    names[6] = "Eloy BELOSOUKINSKI";
    
    english[9].reserve(14);
    french[9].reserve(14);
    for (unsigned char i = 0; i < 14; i++) {

        english[9].emplace_back();
        french[9].emplace_back();
    }
    
    english[10].reserve(3);
    french[10].reserve(3);
    for (unsigned char i = 0; i < 3; i++) {
        english[10].emplace_back();
        french[10].emplace_back();
    }

    load();
}

Language::Language(const Language& orig) {
}

Language::~Language() {
}

void Language::generate() {

    
    // Menu
    english[0][0] = "Arcade Mode";
    english[0][1] = "Highscore";

    english[0][2] = "How to play";
    english[0][3] = "Options";
    english[0][4] = "Credits";
    english[0][5] = "Exit";
    english[0][6] = "Hard";
    english[0][7] = "Normal";
    english[0][8] = "Easy";
    english[0][9] = "Mode";

    english[0][10] = "Display in fullscreen mode";
    english[0][11] = "Display in windowed mode";
    english[0][12] = "Configure the GamePad";
    english[0][13] = "Configure the Keyboard";

    english[0][14] = "Clear the profile";
    english[0][15] = "Clear the highscore";

    english[0][16] = "You played";
    english[0][17] = "hours";
    english[0][18] = "minutes";
    english[0][19] = "seconds";
    english[0][20] = "and";
    english[0][21] = "Welcome";
    english[0][22] = "in the world of X-Blaster Dominator";
    english[0][23] = "You Killed";
    english[0][24] = "enemies and your last score is";
    english[0][25] = "Improve your score!";
    english[0][26] = "Thank you for playing so long!";
    english[0][27] = "You're a serial killer !";
    english[0][28] = "You died many times. You are brave!";
    english[0][29] = "Push on";
    english[0][30] = "to back";
    english[0][31] = "Press a button to configure the primary fire";
    english[0][32] = "Press a button to configure the secondary fire";
    english[0][33] = "Press a button to set the pause mode";
    english[0][34] = "Press a button to set the select mode";
    english[0][35] = "Press start";
    english[0][36] = "2013 All Rights Reserved";


    // Langues disponibles
    english[1][0] = "English";
    english[1][1] = "French";

    // Messages du profil
    english[2][0] = "Profile created";
    english[2][1] = "Profile loaded";
    english[2][2] = "Profile saved";
    english[2][3] = "Profile created";
    english[2][4] = "Gamepad connected";

    // Hud
    english[3][0] = "Credits";
    english[3][1] = "Lives";
    english[3][2] = "Push Start";
    english[3][3] = "Energy";
    english[3][4] = "Second Weapon";

    // Messages du stage
    english[4][0] = "Beat your best score :";
    english[4][1] = "You have unlocked an credit ";


    // Menu pause
    english[5][0] = "Resume";
    english[5][1] = "Restart";
    english[5][2] = "Return to the menu";
    english[5][3] = "Exit the game";

    // Erreur
    english[6][0] = "Error : The screen resolution is less than 800x600. Please check your resolution before launching the game.\n";
    english[6][1] = "Error : loading texture failed.";
    english[6][2] = "Error : loading sound failed.";
    english[6][3] = "Error : loading music failed.";
    english[6][4] = "Error : loading font failed.";
    english[6][5] = "If the error persists, please reinstall the game or contact the developer. \n";
    
    // How To
    english[7][0] = "The objective is to destroy enemy ships and the boss of\neach level in order to win the game and improve your\nscore. You should also avoid projectiles to maintain\nyour energy and your life.";
    english[7][1] = "If you're hit, your energy bar decreases.\nIf it drops to zero, your ship will be\ndestroyed and you lose a life. If you do\nnot possess more lives and that you have\nno credit unlocked, the party will end.\nPlaying several times, you can unlock\ncredit for your next party";
    english[7][2] = "The primary fire button allows you to\nlaunch projectiles to destroy enemies.\nAmmunition is available in unlimited\nquantities and you can make evolve the\nweapon on three levels in order to gain a\npowerful strike force";
    english[7][3] = "The secondary fire button launches two\npowerful shots but it has a low rate of fire.\nWhen you have exhausted its power, it will\ntake a few seconds before you can use the\nsecondary fire.";
    english[7][4] = "Along the way, you can recover up to power\nmodules or equip you to change your main\nweapon. If you possess 2 modules or your\nweapon is already at its maximum level of\nevolution, you earn instead of extra points.";

    english[8][0] = "Programming >>";
    english[8][1] = "Graphics >>";
    english[8][2] = "Musical composition >>";
    english[8][3] = "Test >>";
    english[8][4] = "Contact :";
    english[8][5] = "Web :";
    english[8][6] = "Special Thanks >>";
    english[8][7] = "Developped and built on >>";
#ifdef WIN32
    english[8][8] = "Thank you for playing !";
#else
    english[8][8] = "Thank you for playing on Linux !";
#endif

    english[9][0] = "Stage";
    english[9][1] = "Finished";
    english[9][2] = "Enemies destroyed >>";
    english[9][3] = "Lives lost >>";
    english[9][4] = "Bonnus >>";
    english[9][5] = "Base Score >>";
    english[9][6] = "Total Score >>";
    english[9][7] = "Judgment >>";
    english[9][8] = "Little better";
    english[9][9] = "On track";
    english[9][10] = "A true samurai";
    english[9][11] = "Can you do better?";
    english[9][12] = "Prepare you for the next stage";
    english[9][13] = "Congrulation, the mission is end";

    french[0][0] = "Arcade";
    french[0][1] = "Classement";
    french[0][2] = "Comment jouer";
    french[0][3] = "Options";
    french[0][4] = "Credits";
    french[0][5] = "Quitter";
    french[0][6] = "Difficile";
    french[0][7] = "Normal";
    french[0][8] = "Facile";
    french[0][9] = "Mode";


    french[0][10] = "Affichage en mode plein ecran";
    french[0][11] = "Affichage en mode fenetre";
    french[0][12] = "Configurer la manette";
    french[0][13] = "Configurer le clavier";

    french[0][14] = "Effacer le profil";
    french[0][15] = "Effacer le classement";


    french[0][16] = "Tu as joue";
    french[0][17] = "heures";
    french[0][18] = "minutes";
    french[0][19] = "secondes";
    french[0][20] = "et";
    french[0][21] = "Bienvenue";
    french[0][22] = "dans le monde de X-Blaster Dominator";
    french[0][23] = "Tu as tue";
    french[0][24] = "ennemis et ton dernier score est";
    french[0][25] = "Ameliore ton score !";
    french[0][26] = "Merci d'avoir joue aussi longtemps !";
    french[0][27] = "Tu es un tueur en serie !";
    french[0][28] = "Tu es mort beaucoup de fois. Tu es courageux !";
    french[0][29] = "Appuie sur";
    french[0][30] = "pour revenir en arriere";

    french[0][31] = "Appuie sur un bouton pour configurer le tir principal";
    french[0][32] = "Appuie sur un bouton pour configurer le tir secondaire";
    french[0][33] = "Appuie sur un bouton pour configurer le mode pause";
    french[0][34] = "Appuie sur un bouton pour configurer le mode select";
    french[0][35] = "Appuie sur start";
    french[0][36] = "2013 Tous droits reserves";

    french[1][0] = "Englais";
    french[1][1] = "Francais";

    french[2][0] = "Profil cree";
    french[2][1] = "Profil charge";
    french[2][2] = "Profil sauvegarde";
    french[2][3] = "Highscore cree";
    french[2][4] = "Manette branchee";

    french[3][0] = "Credits";
    french[3][1] = "Vies";
    french[3][2] = "Presse Start";
    french[3][3] = "Energie";
    french[3][4] = "Arme secondaire";

    french[4][0] = "Ameliore ton meilleur score : ";
    french[4][1] = "Tu as debloque un credit ";


    french[5][0] = "Reprendre";
    french[5][1] = "Redemarrer";
    french[5][2] = "Retour au menu principal";
    french[5][3] = "Quitter le jeu";

    // Système
    french[6][0] = "Erreur : La résolution de l'écran est inférieur à 800x600. S'il vous plait, vérifiez votre résolution avant de lancer le jeu.\n";
    french[6][1] = "Erreur : chargement d'une texture echoué.";
    french[6][2] = "Erreur : chargemennt d'un fichier audio échoué";
    french[6][3] = "Erreur : chargement d'une musique échoué";
    french[6][4] = "Erreur : chargement d'une font échoué";
    french[6][5] = "Si l'erreur persiste, veuillez réinstaller le jeu ou contacter le développeur \n";

    // How To
    french[7][0] = "Le but est de detruire les vaisseaux ennemis ainsi que le\nboss de chaque niveau afin de remporter la partie tout\nen ameliorant ton score. Tu dois aussi eviter les\nprojetiles afin de preserver ton energie et tes vies.";
    french[7][1] = "Si tu es touche, ta barre denergie diminue.\nSi elle  descend a zero, ton appareil sera\ndetruit et tu perdras une vie. Dans le cas\nou tu ne possedes plus de vies et que tu\nas aucun credit debloque, la partie\nprendra fin.En jouant plusieurs fois, tu\npeux debloquer des credits pour tes\nprochaines parties.";
    french[7][2] = "La touche de tir principal permet de lancer\ndes projectiles pour detruire les ennemis.\nLes munitions sont disponibles en quantite\nillimitee et tu peux faire evoluer ton tir\nprincipal sur trois niveaux afin dacquerir\nune puissante force de frappe";
    french[7][3] = "La touche de tir secondaire lance deux\npuissants projectiles mais ils disposent\ndune faible cadence de tir. Lorsque tu as\nepuise sa puissance, il faudra attendre\nquelque secondes avant de pouvoir\nreutiliser le tir secondaire.";
    french[7][4] = "En cours de chemin, tu peux recuperer\ndes power up afin de tequiper de modules\nou faire evoluer ton arme principale. Si tu\npossedes 2 modules ou que ton arme\nprincipale est deja a son niveau devolution\nmaximale, tu gagneras a la place des\npoints supplementaires.";

    french[8][0] = "Programmation >>";
    french[8][1] = "Graphismes >>";
    french[8][2] = "Composition musicale >>";
    french[8][3] = "Test >>";
    french[8][4] = "Contact :";
    french[8][5] = "Web :";
    french[8][6] = "Remerciements >>";
    french[8][7] = "Developpe et construit avec >>";
#ifdef WIN32
    french[8][8] = "Merci davoir joue !";
#else
    french[8][8] = "Merci davoir joue sur Linux !";
#endif

    french[9][0] = "Stage";
    french[9][1] = "Termine";
    french[9][2] = "Enemis detruits >>";
    french[9][3] = "Vies perdues >>";
    french[9][4] = "Bonnus >>";
    french[9][5] = "Score de base >>";
    french[9][6] = "Score total >>";
    french[9][7] = "Jugement >>";
    french[9][8] = "Peux mieux faire";
    french[9][9] = "Sur la bonne voie";
    french[9][10] = "Un vrai samourai";
    french[9][11] = "Peux-tu faire mieux ?";
    french[9][12] = "Prepares toi pour le prochain stage";
    french[9][13] = "Felication, la mission est termine";
    
    french[10][0] = "Le 22 aout 2033, le gouvernement americain decide de lancer une operation militaire top secrete visant le Japon.\n";
    french[10][1] = "Cette attaque a pour objectif de derober une technologie pouvant generer un puissant carburant a partir de déchets.\n";
    french[10][2] = "";
    
    ofstream file(languageFile, std::ios::binary);
    boost::archive::binary_oarchive save(file);
    
#ifdef _WIN32
    LANGID lid = (*GetProcAddress(GetModuleHandle("kernel32.dll"), "GetSystemDefaultUILanguage"))();
    if((lid & 0xff) == 0x0c)
    language = "french";
    else language = "english";
    save << language;
#elif defined __linux
    language = "english";
    save << language;
#endif

    // Menu
    for (unsigned char i = 0; i < 37; i++) {

        save << english[0][i];
        save << french[0][i];
    }

    for (unsigned char i = 0; i < 2; i++) {

        save << english[1][i];
        save << french[1][i];
    }

    for (unsigned char i = 0; i < 4; i++) {

        save << english[2][i];
        save << french[2][i];
    }

    for (unsigned char i = 0; i < 5; i++) {

        save << english[3][i];
        save << french[3][i];
    }

    for (unsigned char i = 0; i < 2; i++) {

        save << english[4][i];
        save << french[4][i];
    }

    for (unsigned char i = 0; i < 4; i++) {

        save << english[5][i];
        save << french[5][i];
    }

    for (unsigned char i = 0; i < 6; i++) {

        save << english[6][i];
        save << french[6][i];
    }

    for (unsigned char i = 0; i < 5; i++) {

        save << english[7][i];
        save << french[7][i];
    }

    for (unsigned char i = 0; i < 9; i++) {

        save << english[8][i];
        save << french[8][i];
    }

    for (unsigned char i = 0; i < 14; i++) {

        save << english[9][i];
        save << french[9][i];
    }
    
    file.close();

}

void Language::load() {

    ifstream file(languageFile, std::ios::binary);
    if (file.is_open()) {
        boost::archive::binary_iarchive open(file);

        open >> language;

        // Menu
        for (unsigned char i = 0; i < 37; i++) {

            open >> english[0][i];
            open >> french[0][i];
        }

        for (unsigned char i = 0; i < 2; i++) {

            open >> english[1][i];
            open >> french[1][i];
        }

        for (unsigned char i = 0; i < 4; i++) {

            open >> english[2][i];
            open >> french[2][i];
        }

        for (unsigned char i = 0; i < 5; i++) {

            open >> english[3][i];
            open >> french[3][i];
        }

        for (unsigned char i = 0; i < 2; i++) {

            open >> english[4][i];
            open >> french[4][i];
        }

        for (unsigned char i = 0; i < 4; i++) {

            open >> english[5][i];
            open >> french[5][i];
        }

        for (unsigned char i = 0; i < 6; i++) {

            open >> english[6][i];
            open >> french[6][i];
        }

        for (unsigned char i = 0; i < 5; i++) {

            open >> english[7][i];
            open >> french[7][i];
        }

        for (unsigned char i = 0; i < 9; i++) {

            open >> english[8][i];
            open >> french[8][i];
        }

        for (unsigned char i = 0; i < 14; i++) {

            open >> english[9][i];
            open >> french[9][i];
        }

        file.close();
    } else generate();

}

void Language::save() {

    ifstream file(languageFile);
    if (file.is_open()) {
        ofstream file(languageFile, std::ios::binary);
        boost::archive::binary_oarchive save(file);

        save << language;

        // Menu
        for (unsigned char i = 0; i < 37; i++) {

            save << english[0][i];
            save << french[0][i];
        }

        for (unsigned char i = 0; i < 2; i++) {

            save << english[1][i];
            save << french[1][i];
        }

        for (unsigned char i = 0; i < 4; i++) {

            save << english[2][i];
            save << french[2][i];
        }

        for (unsigned char i = 0; i < 5; i++) {

            save << english[3][i];
            save << french[3][i];
        }

        for (unsigned char i = 0; i < 2; i++) {

            save << english[4][i];
            save << french[4][i];
        }

        for (unsigned char i = 0; i < 4; i++) {

            save << english[5][i];
            save << french[5][i];
        }

        for (unsigned char i = 0; i < 6; i++) {

            save << english[6][i];
            save << french[6][i];
        }

        for (unsigned char i = 0; i < 5; i++) {

            save << english[7][i];
            save << french[7][i];
        }

        for (unsigned char i = 0; i < 9; i++) {

            save << english[8][i];
            save << french[8][i];
        }
        for (unsigned char i = 0; i < 14; i++) {

            save << english[9][i];
            save << french[9][i];
        }

        file.close();
    } else generate();
 
}
