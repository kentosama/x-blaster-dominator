/* 
 * File:   Menu.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 1 mars 2013, 14:24
 */

#include "Menu.h"

Menu::Menu() {
    
    if (Language::Instance()->language != "english") {
        language = Language::Instance()->french[0];
        languageChange = Language::Instance()->french[1];
        strHowTo = Language::Instance()->french[7];
        creditLanguage = Language::Instance()->french[8];
    } else {
        language = Language::Instance()->english[0];
        languageChange = Language::Instance()->english[1];
        strHowTo = Language::Instance()->english[7];
        creditLanguage = Language::Instance()->english[8];
    }
    howtoMin.reserve(4);
    sprites.reserve(12);
    selectMarge = 3;
    text.reserve(32);
    howto.reserve(5);
    creditText.reserve(13);
    messageControl.reserve(4);
    highscoreText.reserve(80);
    enemies.reserve(5);
    move = 0;
    menu.reserve(7);
    controlTexture = false;
    for (unsigned char i = 0; i < 7; i++) {
        menu.emplace_back();
        menu[i] = 0;
    }
    loadProfil();
    loadContent();
    initialize();
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

void Menu::initialize() {
    transition.initialize(2);
    if (!menu[0])
        controlActive = true;
    else controlActive = false;
    enemies.clear();
    startGame = false;
    clearStart = false;
    setPadControl = false;
    setKeyboardControl = false;
    count = 0;
    loadProfil();
    loadHighscore();
    logo.initialize();
    time = time.Zero;
    if (Profil::Instance()->newProfil)
    menu[6] = 1;
    else menu[0] = 1;
    GameTime::Instance()->restart();
    lastTime = 0;
    startDelay = 0;
    previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
}

void Menu::loadProfil() {

    WindowGame::Instance()->fullScreen = Profil::Instance()->fullscreen;
    gameDifficulty = Profil::Instance()->mode;
    int totalTime = Profil::Instance()->totalTime;
    int totalHours, totalMinutes, totalSeconds;
    totalMinutes = (totalTime % (1000 * 60 * 60)) / (1000 * 60);
    totalHours = totalTime / (1000 * 60 * 60);
    totalSeconds = ((totalTime % (1000 * 60 * 60)) % (1000 * 60)) / 1000;

    if (totalHours > 0 && totalMinutes > 0)
        this->totalTime = to_string(totalHours) + " " + language[17] + " " + language[20] + " " + to_string(totalMinutes) + " " + language[18];
    else if (totalHours > 0 && totalMinutes == 0)
        this->totalTime = language[16] + " " + to_string(totalHours) + " " + language[17] + ".";
    else if (totalMinutes > 0 && totalHours == 0)
        this->totalTime = language[16] + " " + to_string(totalMinutes) + " " + language[18] + " " + language[20] + " " + to_string(totalSeconds) + " " + language[19] + ".";
    else if (totalSeconds > 0)
        this->totalTime = language[16] + " " + to_string(totalSeconds) + " " + language[19] + ".";
    else if (totalSeconds == 0)
        this->totalTime = language[21] + " " + Profil::Instance()->playername + " " + language[22] + ".";

    strprofil = this->totalTime + " " + language[23] + " " + to_string(Profil::Instance()->enemyDead) + " " + language[24] + " " + to_string(Profil::Instance()->lastScore) + ".";

    if (Profil::Instance()->lastScore < 10000 && Profil::Instance()->totalTime > 1000)
        strprofil = strprofil + " " + language[25];
    else if (Profil::Instance()->totalTime > 36000000)
        strprofil = strprofil + " " + language[26];
    else if (Profil::Instance()->enemyDead >= 50000)
        strprofil = strprofil + +" " + language[27];
    else if (Profil::Instance()->gameover >= 30)
        strprofil = strprofil + " " + language[28];

    profilInformation.setString(strprofil);
}

void Menu::saveProfil() {

    Profil::Instance()->fullscreen = WindowGame::Instance()->fullScreen;
    Profil::Instance()->mode = gameDifficulty;
    Profil::Instance()->save();

}

void Menu::loadContent() {

    if (!contentLoaded) {

        for (unsigned char i = 0; i < 12; i++) {
            if (i < 4) {
                howtoMin.emplace_back();
                howtoMin[i].setTexture(FileManager::Instance()->howtoMin[i]);
            }

            sprites.emplace_back();
            sprites[i].setTexture(FileManager::Instance()->menu[i]);
        }
        

        sprites[9].setPosition(170, 300);
        


        if (font.loadFromFile(FileManager::Instance()->font)) {
            profilInformation.setPosition(800, 580);
            profilInformation.setFont(font);
            profilInformation.setColor(sf::Color::White);
            profilInformation.setScale(0.4, 0.4);

            for (unsigned char i = 0; i < 80; i++) {
                if (i < 30) {
                    text.emplace_back();
                    text[i].setFont(font);
                    text[i].setColor(sf::Color::White);
                    text[i].setScale(0.4, 0.4);
                }

                if (i < 5) {
                    howto.emplace_back();
                    howto[i].setFont(font);
                    howto[i].setColor(sf::Color::White);
                    howto[i].setScale(0.4, 0.4);
                }

                if (i < 13) {
                    creditText.emplace_back();
                    creditText[i].setFont(font);
                    creditText[i].setColor(sf::Color::White);
                    creditText[i].setScale(0.4, 0.4);
                }

                highscoreText.emplace_back();
                highscoreText[i].setFont(font);
                highscoreText[i].setColor(sf::Color::White);
                highscoreText[i].setScale(0.4, 0.4);

                if (i == 30 || i == 31) {
                    text.emplace_back();
                    text[i].setFont(font);
                    text[i].setString(language[i + 5]);
                }
            }

        } else exit(EXIT_FAILURE);


        setLanguage();

        sprites[10].setPosition(153, 10);
        sprites[11].setPosition(163,140);

        howto[0].setPosition(sprites[10].getPosition().x + 32, sprites[10].getPosition().y + 80);

        howtoMin[0].setPosition(howto[0].getPosition().x - 5, howto[0].getPosition().y + 45);

        howto[1].setPosition(howtoMin[0].getPosition().x + 116, howtoMin[0].getPosition().y + 10);

        howtoMin[1].setPosition(howto[0].getPosition().x + 340, howto[1].getPosition().y + 90);

        howto[2].setPosition(howto[0].getPosition().x, howtoMin[1].getPosition().y + 10);

        howtoMin[2].setPosition(howto[0].getPosition().x + 340, howto[2].getPosition().y + 90);

        howto[3].setPosition(howto[0].getPosition().x, howtoMin[2].getPosition().y + 10);

        howtoMin[3].setPosition(howto[0].getPosition().x + 340, howto[3].getPosition().y + 90);

        howto[4].setPosition(howto[0].getPosition().x, howtoMin[3].getPosition().y + 10);

        sprites[0].setPosition(160, 0);
        text[30].setPosition(sprites[0].getPosition().x + (sprites[0].getTexture()->getSize().x / 2), 550);
        text[31].setPosition(sprites[0].getPosition().x + (sprites[0].getTexture()->getSize().x / 2), 520);
        for (unsigned char i = 29; i < 32; i++) {

            text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
            text[i].setColor(sf::Color::White);
            if (i == 30)
                text[i].setScale(0.5, 0.5);
            else text[i].setScale(0.4, 0.4);
        }

        sprites[1].setPosition(160, 0);


        sprites[2].setPosition(160, 0);


        sprites[3].setPosition(menuPosition - 10, 300);

        sprites[4].setPosition(180, 100);


        sprites[5].setPosition(230, 80);


        sprites[6].setPosition(233, 180);

        creditText[0].setPosition(sprites[5].getPosition().x + 25, sprites[5].getPosition().y + 60); // Programmation
        creditText[6].setPosition(creditText[0].getPosition().x, creditText[0].getPosition().y + 20); // Le développeur
        creditText[9].setPosition(creditText[0].getPosition().x, creditText[6].getPosition().y + 20); // E-mail
        creditText[1].setPosition(creditText[0].getPosition().x, creditText[9].getPosition().y + 35); // Graphiste
        creditText[7].setPosition(creditText[0].getPosition().x, creditText[1].getPosition().y + 20); // etc.
        creditText[10].setPosition(creditText[0].getPosition().x, creditText[7].getPosition().y + 20); // E-mail
        creditText[11].setPosition(creditText[0].getPosition().x, creditText[10].getPosition().y + 20); // Web
        creditText[2].setPosition(creditText[0].getPosition().x, creditText[11].getPosition().y + 35); // Musique
        creditText[4].setPosition(creditText[0].getPosition().x, creditText[2].getPosition().y + 20);
        creditText[3].setPosition(creditText[0].getPosition().x, creditText[4].getPosition().y + 35); // Musique
        creditText[8].setPosition(creditText[0].getPosition().x, creditText[3].getPosition().y + 20); // Testeur
        creditText[12].setPosition(creditText[0].getPosition().x, creditText[8].getPosition().y + 20); // Testeur

        sprites[8].setPosition(428, text[gameDifficulty + 6].getPosition().y + 3.5);

        sndMove.setBuffer(FileManager::Instance()->sound[0]);
        sndMove.setVolume(70);
        sndStart.setBuffer(FileManager::Instance()->sound[6]);

        contentLoaded = true;
    }

}

void Menu::setLanguage() {

    unsigned int position = 300;
    for (unsigned char i = 0; i < 29; i++) {
        if (i < 6) {
            position += 20;
            text[i].setPosition(menuPosition, position);
        }
        text[i].setString(language[i]);
    }

    for (unsigned char i = 0; i < 5; i++)
        howto[i].setString(strHowTo[i]);

    if (WindowGame::Instance()->fullScreen)
        text[11].setString(language[11]);
    else text[11].setString(language[10]);

    if (Language::Instance()->language == "english") {
        text[10].setString(languageChange[0]);
    } else {
        text[10].setString(languageChange[1]);
    }

    messageControl.clear();
    for (unsigned char i = 0; i < 4; i++) {
        messageControl.emplace_back();
        messageControl[i].setPosition(sprites[9].getPosition().x + (sprites[9].getTexture()->getSize().x / 2), sprites[9].getPosition().y + 28);
        messageControl[i].setFont(font);
        messageControl[i].setColor(sf::Color::White);
        messageControl[i].setString(language[i + 31]);
        messageControl[i].setOrigin(messageControl[i].getGlobalBounds().width / 2, messageControl[i].getGlobalBounds().height / 2);
        messageControl[i].setScale(0.4, 0.4);
    }

    text[6].setPosition(360, 260); // Hard
    text[7].setPosition(360, 280); // Normal
    text[8].setPosition(360, 300); // Easy

    text[9].setPosition(280, 260); // Mode

    text[10].setPosition(280, 340); // Le langage
    text[11].setPosition(280, 360); // FullScreen on / off
    text[12].setPosition(280, 380); // Configurer la manette
    text[13].setPosition(280, 400); // Configurer le clavier

    text[14].setPosition(280, 420); // Effacer le profil
    text[15].setPosition(280, 440); // Effacer le classement

    for (unsigned char i = 0; i < 6; i++)
        creditText[i].setString(creditLanguage[i]);

    creditText[6].setString(Language::Instance()->names[0]);
    creditText[7].setString("Patrice-M");
    creditText[8].setString("Sylvain Leconte");
    creditText[9].setString(creditLanguage[4] + " shingo-san@live.jp");
    creditText[10].setString(creditLanguage[4] + " doomhammer80@gmail.com");
    creditText[11].setString(creditLanguage[5] + " http://www.patrice-m.fr/");
    creditText[12].setString(Language::Instance()->names[2]);
    creditText[4].setString(creditText[6].getString());

    if (menu[1]) {
        text[29].setString(language[29] + " " + to_string(GamePadManager::Instance()->buttons[1] + 1) + " " + language[30]);
        if (Language::Instance()->language == "english")
            text[29].setPosition(425, 465);
        else text[29].setPosition(285, 465);

    }
}

void Menu::enemyManager() {
    int t;
    if (enemies.size() == 0) {
        for (int i = 0; i < 5; i++) {
            int texture = rand() % 70;
            int positionX = rand() % 400;
            if (positionX < 160)
                positionX = 160;
            int positionY = -50;
            int startTime = rand() % 7000;

            if (texture < 10) {

                t = 0;
            }

            if (texture >= 10 && texture < 20) {

                t = 3;
            }
            if (texture >= 20 && texture < 40) {

                t = 7;
            }
            if (texture >= 40 && texture < 50) {

                t = 0;
            }
            if (texture >= 50 && texture <= 70) {

                t = 0;
            }


            enemies.emplace_back(Vector2f(positionX, positionY), t, startTime, false, 0, 0, 0, false, false);
        }
    } else {

        for (unsigned char i = 0; i < enemies.size(); i++) {
            enemies[i].update();
            if (!enemies[i].active)
                enemies.erase(enemies.begin() + i);

        }
    }
}

void Menu::moveSelect(int button) {

    if (button == 0)
        move += 1;
    else if (button == 1)
        move -= 1;

    sndMove.play();
    previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
}

void Menu::menuMove() {
    previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();

    if (move == 0) {
        sndStart.play();
        controlActive = false;
        MusicManager::Instance()->fadingOut = true;
        transition.initialize(1);
        clearStart = true;
    } else if (move == 1) {
        text[29].setString(language[29] + " " + to_string(GamePadManager::Instance()->buttons[1] + 1) + " " + language[30]);
        if (Language::Instance()->language == "english")
            text[29].setPosition(463, 490);
        else
            text[29].setPosition(320, 490);
        loadHighscore();
        menu[3] = 1;
    } else if (move == 2) {
        menu[4] = 1;
    } else if (move == 3) {
        text[29].setString(language[29] + " " + to_string(GamePadManager::Instance()->buttons[1] + 1) + " " + language[30]);
        if (Language::Instance()->language == "english")
            text[29].setPosition(425, 465);
        else
            text[29].setPosition(285, 465);
        sprites[3].setPosition(270, text[8].getPosition().y);
        move = 0;
        menu[1] = 1;
    } else if (move == 4) {
        menu[5] = 1;
        text[29].setString(language[29] + " " + to_string(GamePadManager::Instance()->buttons[1] + 1) + " " + language[30]);
        if (Language::Instance()->language == "english")
            text[29].setPosition(425, 485);
        else
            text[29].setPosition(285, 485);
    } else if (move == 5)
        WindowGame::Instance()->window.close();
}

void Menu::optionsMove(unsigned char action) {

    if (action == 0) { // Configurer le mode
        sprites[3].setPosition(350, text[3].getPosition().y);
        menu[2] = 1;
    } else if (action == 6) { // Nouveau classement
        Highscore::Instance()->create();
    } else if (action == 2) { // Changer le mode d'affichage
        if (WindowGame::Instance()->fullScreen) {
            WindowGame::Instance()->fullScreen = false;
            text[11].setString(language[11]);
        } else {
            WindowGame::Instance()->fullScreen = true;
            text[11].setString(language[10]);
        }
        WindowGame::Instance()->changeScreen = true;

    } else if (action == 1) { // Changer la langue

        if (Language::Instance()->language == "english") {
            language = Language::Instance()->french[0];
            languageChange = Language::Instance()->french[1];
            strHowTo = Language::Instance()->french[7];
            Language::Instance()->language = "french";

        } else if (Language::Instance()->language == "french") {

            language = Language::Instance()->english[0];
            languageChange = Language::Instance()->english[1];
            Language::Instance()->language = "english";
            strHowTo = Language::Instance()->english[7];
        }
        Profil::Instance()->setLanguage();
        setLanguage();
        loadProfil();

    } else if (action == 3) { // Configurer la manette (sauvegarde auto)
        setPadControl = true;
    } else if (action == 4) { // Configurer le clavier (sauvegarde auto)
        setKeyboardControl = true;
    } else if (action == 5) {
        Profil::Instance()->create();
    } else if (action == 7) { // Retour aux options
        sprites[3].setPosition(270, text[9].getPosition().y);
        menu[2] = 0;
        move = 0;
    } else if (action == 8) { // Configurer le mode de difficulté

        gameDifficulty = move;
        sprites[8].setPosition(428, text[move + 6].getPosition().y + 3.5);

    } else if (action == 9) { // Enregistrer le profil
        saveProfil();
        Language::Instance()->save();
        menu[1] = 0;
        menu[2] = 0;
        sprites[3].setPosition(menuPosition - 10, text[3].getPosition().y);
        move = 3;
    }

    previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();

}

void Menu::pressStart() {

    if (GamePadManager::Instance()->gamepadConnected) {
        if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[3]) && GameTime::Instance()->getElapsedTime().asMilliseconds() > 3000) {
            menu[0] = 0;
            controlActive = true;
            previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
    }
    if (WindowGame::Instance()->focus) {
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            menu[0] = 0;
            controlActive = true;
            previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
    }
}

void Menu::control() {
    
    
    if (menu[0])
        return;

    // Control avec la manette de jeu
    if (GamePadManager::Instance()->gamepadConnected) { // Mouvements dans les menus

        if (GamePadManager::Instance()->gamepadMoved()) {

            if (Joystick::getAxisPosition(0, Joystick::Y) > GamePadManager::Instance()->axisUp)
                moveSelect(0);
            else if (Joystick::getAxisPosition(0, Joystick::Y) < GamePadManager::Instance()->axisDown)
                moveSelect(1);
            else {
#ifdef __linux
                if (Joystick::getAxisPosition(0, Joystick::PovY) == 100)
                    moveSelect(0);
                else if (Joystick::getAxisPosition(0, Joystick::PovY) == -100)
                    moveSelect(1);
#elif defined _WIN32 || _WIN64
                if (Joystick::getAxisPosition(0, Joystick::PovX) == -100)
                    moveSelect(0);
                else if (Joystick::getAxisPosition(0, Joystick::PovX) == 100)
                    moveSelect(1);
#endif
            }
        }

        if (menu[1] == 0 && menu[3] == 0) { // Menu principal
            if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0]))
                menuMove();
        } else if (menu[1] == 1 && menu[2] == 0 && menu[3] == 0) { // Menu des options uniquement
            if (GamePadManager::Instance()->gamepadMoved()) {
                if (Joystick::getAxisPosition(0, Joystick::X) > GamePadManager::Instance()->axisUp) {
                    if (move < 3)
                        optionsMove(move);
                } else {
#ifdef __linux 
                    if (Joystick::getAxisPosition(0, Joystick::PovX) > 1)
#elif defined _WIN32 || _WIN64
                    if (Joystick::getAxisPosition(0, Joystick::PovY) > 1)
#endif                        
                        if (move < 3)
                            optionsMove(move);
                }
            } else if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0])) {
                
                if (move > 2)
                    optionsMove(move);
            }

        } else if (menu[1] == 1 && menu[2] == 1) { // Sélection du mode de difficulté
            // Quitter la configuration du mode
            if (GamePadManager::Instance()->gamepadMoved()) {
                if (Joystick::getAxisPosition(0, Joystick::X) < GamePadManager::Instance()->axisDown)
                    optionsMove(7);
                else {
#ifdef __linux 
                    if (Joystick::getAxisPosition(0, Joystick::PovX) < -4)
#elif defined _WIN32 || _WIN64
                    if (Joystick::getAxisPosition(0, Joystick::PovY) < -4)
#endif                        
                        optionsMove(7);
                }
            } else if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0]))
                optionsMove(8);
        }
        if (menu[1] == 1 || menu[2] == 1) { // Quitter les options
            if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[1]))
                optionsMove(9);
        } else if (menu[5] == 1) { // Fermer la fenêtre des credits
            if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[1]))
                menu[5] = 0;
        } else if (menu[3] == 1) { // Fermer la fenêtre du classement
            if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[1]))
                menu[3] = 0;
        } else if (menu[4] == 1) {
            if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[1]))
                menu[4] = 0;
        }
    }

    // Contrôle avec le clavier
    if (WindowGame::Instance()->focus) {

        if (menu[1] == 1 || menu[2] == 1 || menu[1] == 0 && menu[3] == 0 && menu[4] == 0 && menu[5] == 0) {
        if (Keyboard::isKeyPressed(Keyboard::Down))
            moveSelect(0);
        else if (Keyboard::isKeyPressed(Keyboard::Up))
            moveSelect(1);
        }

        if (menu[1] == 0 && menu[3] == 0) { // Menu principal

            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0]))
                menuMove();
        } else if (menu[1] == 1 && menu[2] == 0 && menu[3] == 0) { // Menu des options
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (move < 4)
                    optionsMove(move);
            } else if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0])) {
                if (move > 2)
                    optionsMove(move);
                std::cout << to_string(move) << std::endl;
            }
        } else if (menu[1] == 1 && menu[2] == 1) {
            if (Keyboard::isKeyPressed(Keyboard::Left))
                optionsMove(7);

            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0]))
                optionsMove(8);
        }

        if (menu[1] == 1 || menu[2] == 1) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1]))
                optionsMove(9);
        } else if (menu[5] == 1) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1]))
                menu[5] = 0;
        } else if (menu[3] == 1) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1]))
                menu[3] = 0;
        } else if (menu[4] == 1) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1]))
                menu[4] = 0;
        }
    }
}

void Menu::clearMenu() {

    if (transition.finish && !MusicManager::Instance()->fadingOut) {
        startGame = true;
        clearStart = false;
    }
}

void Menu::loadHighscore() {

    int position = 170; // Important !
    for (int i = 0; i < 14; i++) {
        position += 20;
        highscoreText[i].setString(Highscore::Instance()->scoring[i].playername);
        highscoreText[i].setPosition(200, position);
    }

    position = 170; // Important !
    for (int i = 14; i < 28; i++) {
        position += 20;
        highscoreText[i].setString(Highscore::Instance()->scoring[i - 14].stage);
        highscoreText[i].setPosition(311, position);
    }

    position = 170; // Important !
    string mode;
    for (int i = 28; i < 42; i++) {
        position += 20;
        if (Highscore::Instance()->scoring[i - 28].mode == 0)
            mode = language[6];
        else if (Highscore::Instance()->scoring[i - 28].mode == 1)
            mode = language[7];
        else if (Highscore::Instance()->scoring[i - 28].mode == 2)
            mode = language[8];
        highscoreText[i].setString(mode);
        highscoreText[i].setPosition(387, position);
    }

    position = 170; // Important !
    for (int i = 42; i < 56; i++) {
        position += 20;
        highscoreText[i].setString(to_string(Highscore::Instance()->scoring[i - 42].score));
        highscoreText[i].setPosition(468, position);
    }

    position = 170; // Important !
    for (int i = 56; i < 70; i++) {
        position += 20;
        highscoreText[i].setString(to_string(Highscore::Instance()->scoring[i - 56].enemydead));
        highscoreText[i].setPosition(555, position);
    }
}

void Menu::update() {
   
    if (menu[6]) {
        if (!controlTexture) {

            if (GamePadManager::Instance()->gamepadConnected)
                sprites[11].setTexture(FileManager::Instance()->menu[12]);
            else sprites[11].setTexture(FileManager::Instance()->menu[11]);
            controlTexture = true;
        } else {

            if (GamePadManager::Instance()->keyboardPressed()) {
                menu[6] = 0;
                menu[0] = 1;
                previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
                Profil::Instance()->newProfil = false;
            } else if (GamePadManager::Instance()->gamepadConnected) {
                if (GamePadManager::Instance()->gamepadPressed()) {
                    menu[6] = 0;
                    menu[0] = 1;
                    previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
                    Profil::Instance()->newProfil = false;
                }
            }
        }
    }
    
    transition.update();

    if (!menu[0] == 1 && !menu[6] == 1) {
        enemyManager();
        logo.update();
    } else if (menu[0] == 1) {

        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - startDelay > 500) {
            count += 1;
            if (count > 2)
                count = 0;
            startDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }

        if (count == 1) {
            text[30].setColor(sf::Color(255, 255, 255, 0));
        } else if (count == 2) {
            text[30].setColor(sf::Color(255, 255, 255, 255));
        }
    }

    if (setPadControl)
        setControl(0);
    else if (setKeyboardControl)
        setControl(1);


    if ((!menu[6] && MusicManager::Instance()->stopped()) || (!menu[6] && MusicManager::Instance()->getCurrentMusic() != 0))
        MusicManager::Instance()->play(0,100,true);
  
    if (previousDelay == 0)
        previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - previousDelay > delay.asMilliseconds()) {

        if (menu[0] == 1)
            pressStart();

        else if (controlActive && !setPadControl && !setKeyboardControl && menu[6] == 0)
            control();
    }

    if (menu[1] == 0 && menu[3] == 0 && menu[2] == 0 && menu[4] == 0) { // primary menu
            sprites[3].setPosition(sprites[3].getPosition().x, text[move].getPosition().y);

        if (move < 0)
            move = 5;
        else if (move > 5)
            move = 0;
       
    } else if (menu[1] == 1 && menu[2] == 0 && menu[3] == 0 && menu[4] == 0) {
            sprites[3].setPosition(sprites[3].getPosition().x, text[move + 9].getPosition().y);

        if (move < 0)
            move = 6;
        else if (move > 6)
            move = 0;
    } else if (menu[1] == 1 && menu[2] == 1 && menu[3] == 0 && menu[4] == 0) {
            sprites[3].setPosition(sprites[3].getPosition().x, text[move + 6].getPosition().y);

        if (move < 0)
            move = 2;
        else if (move > 2)
            move = 0;
    }

    sprites[3].setPosition(sprites[3].getPosition().x, sprites[3].getPosition().y + selectMarge);

    if (clearStart)
        clearMenu();

    if (menu[0] == 0) {
        if (profilInformation.getPosition().x > -1000)
            profilInformation.move(-1, 0);
        else profilInformation.setPosition(800, 580);
    }
}

void Menu::setControl(unsigned char control) {
    if (control == 0) {
        if (Joystick::isConnected(0)) {

            GamePadManager::Instance()->setControl();

            if (GamePadManager::Instance()->setting > 3) {
                previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
                GamePadManager::Instance()->save();
                GamePadManager::Instance()->setting = 0;
                GamePadManager::Instance()->previousTime = 0;
                setPadControl = false;
            }
        }
    } else if (control == 1) {
        GamePadManager::Instance()->setKeyboard();
        if (GamePadManager::Instance()->setting == 1)
            text[16].setString(language[29]);
        else if (GamePadManager::Instance()->setting == 2)
            text[16].setString(language[30]);
        else if (GamePadManager::Instance()->setting == 3)
            text[16].setString(language[31]);
        else if (GamePadManager::Instance()->setting > 3) {
            previousDelay = GameTime::Instance()->getElapsedTime().asMilliseconds();
            GamePadManager::Instance()->save();
            GamePadManager::Instance()->setting = 0;
            GamePadManager::Instance()->previousTime = 0;
            setKeyboardControl = false;
            text[16].setString(language[28]);
        }
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    target.draw(sprites[1], states); // show the background
    if (!menu[6]) {
    for (unsigned char i = 0; i < enemies.size(); i++)
        target.draw(enemies[i], states);

    target.draw(sprites[2], states); // show the background 2

    target.draw(logo, states);
    for (unsigned char i = 0; i < 6; i++) {
        target.draw(text[i], states);
    }

    target.draw(profilInformation, states);

    if (menu[1] == 0) // Options
        target.draw(sprites[3], states); // show select sprite

    if (menu[3] == 1) { // Highscore
        target.draw(sprites[4], states);
        for (unsigned char i = 0; i < 70; i++)
            target.draw(highscoreText[i], states);
        if(GamePadManager::Instance()->gamepadConnected)
        target.draw(text[29], states);

    } else if (menu[4] == 1) { // show the howto menu
        target.draw(sprites[10], states);

        for (unsigned char i = 0; i < 5; i++) {
            if (i < 4)
                target.draw(howtoMin[i], states);
            target.draw(howto[i], states);
        }
    } else if (menu[5] == 1) { // if show the credit menu
        target.draw(sprites[5], states);
        for (unsigned char i = 0; i < 13; i++)
            target.draw(creditText[i], states);
        if(GamePadManager::Instance()->gamepadConnected)
        target.draw(text[29], states);
    } else if (menu[1] == 1) { // if show the option menu
        target.draw(sprites[6], states);

        for (unsigned char i = 6; i < 16; i++)
            target.draw(text[i], states);
        
        target.draw(text[15], states);
        target.draw(text[17], states);
        target.draw(sprites[3], states); // target select sprite
        target.draw(sprites[8], states); // target cross sprite
        
        if (setPadControl || setKeyboardControl) {
            target.draw(sprites[9], states);
            target.draw(messageControl[GamePadManager::Instance()->setting], states);
        }
        if(GamePadManager::Instance()->gamepadConnected)
        target.draw(text[29], states);
    }

    if (menu[0]) { // Title
        target.draw(sprites[0], states);
        target.draw(text[30], states);
        target.draw(text[31], states);
    }
    }
    else if (menu[6]) {
        target.draw(sprites[2], states); // target the background 2
        target.draw(sprites[11], states);
    }

    target.draw(transition, states);
}

Menu::Logo::Logo() {
    time = sf::milliseconds(200);
    position = Vector2f(215, 0);
    sprite.setTexture(FileManager::Instance()->logo[0]);
    sprite.setPosition(position);
}

void Menu::Logo::initialize() {
    count = 0;
    decount = 4;
    lastTime = 0;
}

void Menu::Logo::update() {

    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        if (decount == 0)
            initialize();

        if (count < 5)
            count += 1;
        else if (count == 5)
            decount -= 1;

        if (count < 4)
            sprite.setTexture(FileManager::Instance()->logo[count]);
        else sprite.setTexture(FileManager::Instance()->logo[decount]);
    }

}

void Menu::Logo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

string Menu::to_string(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
