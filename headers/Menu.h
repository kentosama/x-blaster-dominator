/* 
 * File:   Menu.h
 * Author: jacques belosoukinski
 *
 * Created on 1 mars 2013, 14:24
 */

#ifndef MENU_H
#define	MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Profil.h"
#include "Highscore.h"
#include "Transition.h"
#include "FileManager.h"
#include "GamePadManager.h"
#include "Language.h"
#include "Animation.h"
#include "MusicManager.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using sf::Texture;
using sf::Sprite;
using sf::Font;
using sf::Text;
using sf::Joystick;
using sf::Keyboard;
using sf::Sound;
using sf::SoundBuffer;
using sf::Music;
using sf::Clock;
using sf::Time;
using sf::IntRect;
using sf::RectangleShape;
using sf::Vector2f;

class Menu : public sf::Drawable {
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
    void loadContent();
    void initialize();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool contentLoaded = false, initialized = false;
    bool startGame = false;

private:
    void moveSelect(int button);
    void menuMove();
    void optionsMove(unsigned char action);
    void modeMove();
    void pressStart();
    void setLanguage();
    void loadProfil();
    void saveProfil();
    void loadHighscore();
    void enemyManager();
    void control();
    void saveOption();
    void clearMenu();
    void musicFadeOut();
    void setControl(unsigned char control);
    string to_string(int value);
    Font font;
    string strprofil, totalTime;
    Text profilInformation;
    Transition transition = Transition(2, 0);
    vector<unsigned char> menu;
    vector<Text> messageControl;
    vector<Text> howto;
    vector<Text> creditText;
    vector<string>creditLanguage;
    vector<string> strHowTo;
    vector<Sprite> howtoMin;
    vector<Enemy> enemies;
    vector<Text> text;
    vector<Text> highscoreText;
    vector<string> language;
    vector<string> languageChange;
    vector<Sprite> sprites;
    vector<SoundBuffer> sound;

    sf::Time delay = sf::seconds(0.15);
    sf::Time time = sf::seconds(1);
    float previousDelay = 0, lastTime = 0, startDelay = 0;
    bool clearStart, musicFading, controlActive, setPadControl, setKeyboardControl, controlTexture;
    const int menuPosition = 365;
    unsigned char volume, selectMarge, count, gameDifficulty;
    char move;
    Sound sndMove;
    Sound sndStart;
    
    class Logo : public sf::Drawable {
    public:
        Logo();
        void initialize();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        Sprite sprite;
        unsigned char count, decount;
        sf::Time time;
        float lastTime;
        Vector2f position;
    };
    Logo logo;
};

#endif	/* MENU_H */