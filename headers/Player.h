/* 
 * File:   Player.h
 * Author: jacques belosoukinski
 *
 * Created on 2 mars 2013, 12:57
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GamePadManager.h"
#include "Animation.h"
#include "GameTime.h"
#include "FileManager.h"
#include "Profil.h"
#include "Replay.h"

using sf::Texture;
using sf::Sprite;
using sf::Keyboard;
using sf::Joystick;
using sf::Vector2f;
using sf::Color;
using sf::IntRect;
using sf::RectangleShape;
using sf::VertexArray;
using sf::Time;
using sf::Font;
using sf::Text;
using std::string;
using std::vector;

class Player : public sf::Drawable {
public:
    Player();
    Player(const Player& orig);
    void initialize(bool a);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual ~Player();
    void setNewCredit();
    Vector2f getPosition();
    Vector2f getSize();
    Vector2f getOrigin();
    const unsigned char getHealthPortion();
    bool gameover();
    bool getCredits();
    Sprite sprite;
    int health;
    unsigned char lives, credits, weapon, bullet, module, lostLives, countSuperAttack; 
    bool active, control, dead, startMission, collision, goldCollision, inZone, activeSuperAttack;
    float lastShot;
    Time secondaryShotTime;
    Time shotTime;
    vector<IntRect> rect;
    vector<Sprite> modules;
    vector<Sprite> shadowModules;
    Clock moduleClock;
#ifdef _DEBUG
    bool showRectangle, godMode, unlimitedAttack;
#endif
private:
    void liveManager();
    void setLive();
    void setBullet();
    void keyboardControl();
    void joystickControl();
    void updateModule();

    const unsigned int limitRight = 602, limitDown = 530;
    const unsigned char limitLeft = 160, limitUp = 0;

    Sprite shadow, bulle;
    Animation animation, animationShadow;
    Color color;
    Time deadTime, moduleTime, SuperAttackTime;
    vector<RectangleShape> rectShape;
    
    bool newLive, collisionTime_restart, setFrame;
    unsigned char const speed = 4;
    float lastModule, previousDead, previousSetBullet, previousCollision, lastTime;
    unsigned char playerMove, gameDifficulty;
    char axisUp, axisDown, axisMax, axisMin;
    
    
    
    sf::Sound sndSuperAttack;
    
    class SuperAttack : public sf::Drawable {
    public:
        SuperAttack();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void initialize();
        IntRect rectangle;
    private:
        RectangleShape flasher;
        Time time;
        float lastTime;
        bool active;
        sf::Font font;
        sf::Text text;
    };
    
    class Target : public sf::Drawable {
    public:
        Target();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool active;
        RectangleShape rect;
    private:
        float lastTime, trans;
        unsigned char count;
        
    };
    
public:
    SuperAttack SuperAttack;
    Target target;

};

#endif	/* PLAYER_H */

