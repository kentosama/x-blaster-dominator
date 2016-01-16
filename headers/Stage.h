/* 
 * File:   Stage.h
 * Author: jacques belosoukinski
 *
 * Created on 1 mars 2013, 18:05
 */

#ifndef STAGE_H
#define	STAGE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "dynaText.h"
#include "Bullet.h"
#include "BulletEnemy.h"
#include "Explosion.h"
#include "PowerUp.h"
#include "Transition.h"
#include "Hud.h"
#include "Profil.h"
#include "Highscore.h"
#include "GameTime.h"
#include "Wave.h"
#include "GamePadManager.h"
#include "Pause.h"
#include "Language.h"
#include "MusicManager.h"
#include "WindowGame.h"
using sf::Sprite;
using sf::SoundBuffer;
using sf::Sound;
using sf::Time;
using sf::Joystick;
using sf::Keyboard;
using sf::Vector2f;
using sf::Clock;
using std::string;
using std::vector;

class Stage : public sf::Drawable {
public:
    Stage();
    Stage(const Stage& orig);
    virtual ~Stage();
    void initialize(unsigned char stage);
    void restart(unsigned char stage);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool endWave();
    bool initialized, gameoverActive, finished;
    unsigned char stage;
    Transition transition = Transition(1, 0);
    Hud hud;

    class StateText : public sf::Drawable {
    public:
        StateText(string value, float startTime, Vector2f position);
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Text text;
        Font font;
        bool active;
        float startTime, lastTime;
        unsigned char trans;
    };

    class StateStage : public sf::Drawable {
    public:
        StateStage(unsigned char stage);
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        vector<StateText> stateText;
        vector<string> language;
        sf::Time const time = sf::seconds(30);
        float lastTime, lastTime2;
        bool finished, initialize;
        unsigned int score, enemyDead, bonnus;
        unsigned char lostLives, countText;
        sf::RectangleShape rectangle;
        Text text;
        Font font;

    };

    vector<StateStage> stateStage;

protected:
    void setLanguage();
    void messagebox();
    void backgroundUpdate();
    void bulletUpdate();
    void playerUpdate();
    void playerControl();
    void playerFire(unsigned char type);
    void moduleFire();
    void creditUpdate();
    
    void enemyUpdate();
    void bossUpdate();
    void bossInitialize();
    
    void setPause();
    void gameover();
    void saveScore();
    void setNewScore();
    void nextStage();
    void saveProfil();
    
    int getBonnus();

    Background background;
    int enemyDead, enemyMissed, score, newscore, lastScore, totalEnemyDead;
    unsigned char lastLives, lastSuperAttack, gameDifficulty;

    Player player;
    dynaText textStage;

    Pause pauseMenu;
    Wave wave;

    Sprite textGameover;

    
    // Vector
    vector<int>messagesStatut;
    vector<string> messages;
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    vector<BulletEnemy> bulletsEnemy;
    vector<Explosion> explosions;
    vector<PowerUp> powerups;
    vector<Sound> sound;

    bool pause, creditPause, snd_voice_played, activeNextStage, setBonnus, finishedVolumeOut, finishedVolumeIn, initializedBoss;
     
#if defined _DEBUG
    bool goNextStage = false;
#endif

    unsigned const int startStage = 10000;
    unsigned char bulletPortion;
    unsigned char limitCredit, lostLives;
    
    float lastTimeLimit, lastTime, lastBossSoundExplosion, time, lastPressedBouton;
    sf::Time const pressBouton = sf::seconds(0.3);
    sf::Time const fireShot = sf::seconds(0.13);
    sf::Time elapsedTime;
    sf::Time const timeLimit = sf::seconds(1);
    
    Clock clock;
    
private:
    static string to_string(int value);
    class Story : public sf::Drawable {
    public:
        Story();
        void initialize();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool finished;
    private:
        Font font;
        vector<Sprite> sprites;
        vector<string> strStory;
        vector<Text> text;
        float lastTime;
        
    };
    
    
    class DebugOption : public sf::Drawable {
    public:
        DebugOption();
        void initialize();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool active;
        vector<unsigned char> option;
        unsigned int stage, wave, move, keyAction;
    private:
        void control();
        void action(unsigned char count);
        vector<string> str;
        vector<Text> text;
        vector<Sprite> sprite;
        Font font;
        Time time;
        Clock clock;
        bool restart;
        float lastTime = 0;
        
    };
public:
    DebugOption debug;



};

#endif	/* STAGE_H */

