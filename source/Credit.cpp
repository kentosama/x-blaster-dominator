/* 
 * File:   Credit.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 10 avril 2013, 23:30
 */

#include "Credit.h"

Credit::Credit() {
    credit.reserve(10);
    
    fade.setTexture(FileManager::Instance()->fade);
    fade.setPosition(160, 0);
    
}

Credit::Credit(const Credit& orig) {
}

Credit::~Credit() {
}

Credit::textCredit::textCredit(string text, float startTime, Vector2f position) {
    
    this->text.setString(text);
    this->startTime = startTime;
    this->text.setPosition(position);
    this->text.setScale(0.5, 0.5);
    this->text.setColor(sf::Color(255, 255, 255, trans));
}

void Credit::initialize() {
    transition.initialize(2);
    finished = false;
        stage = rand() % 500;
    if (stage <= 100)
        stage = 1;
    else if (stage > 100 && stage <= 200)
        stage = 2;
    else if (stage > 200 && stage <= 300)
        stage = 3;
    else if (stage > 300 && stage <= 400)
        stage = 4;
    else if (stage > 400 && stage <= 500)
        stage = 5;
    
    background.initialize(stage);
    
    lastTime = 0;

    if (Language::Instance()->language != "french")
        language = Language::Instance()->english[8];
    else language = Language::Instance()->french[8];
    
    credit.clear();
    unsigned const int position = 500;
    credit.emplace_back(language[0], 10000, Vector2f(250, position));
    credit.emplace_back(Language::Instance()->names[0], 10000, Vector2f(250, position + 20));

    credit.emplace_back(language[1], 20000, Vector2f(250, position));
    credit.emplace_back(Language::Instance()->names[1], 20000, Vector2f(250, position + 20));

    credit.emplace_back(language[2], 30000, Vector2f(250, position));
    credit.emplace_back(Language::Instance()->names[0], 30000, Vector2f(250, position + 20));

    credit.emplace_back(language[3], 40000, Vector2f(250, position));
    credit.emplace_back(Language::Instance()->names[2], 40000, Vector2f(250, position + 20));
    credit.emplace_back(Language::Instance()->names[3], 40000, Vector2f(250, position + 40));

    credit.emplace_back(language[6], 50000, Vector2f(250, position));
    credit.emplace_back(Language::Instance()->names[4], 50000, Vector2f(250, position + 20));
    credit.emplace_back(Language::Instance()->names[5], 50000, Vector2f(250, position + 40));
    credit.emplace_back(Language::Instance()->names[6], 50000, Vector2f(250, position + 60));

    credit.emplace_back(language[7], 60000, Vector2f(250, position));
    credit.emplace_back("ArchLinux", 60000, Vector2f(250, position + 20));

    credit.emplace_back(Profil::Instance()->playername + " " + ">>", 85000, Vector2f(250, position));
    credit.emplace_back(language[8], 85000, Vector2f(250, position + 20));
    
    if (font.loadFromFile(FileManager::Instance()->font)) {

        for (unsigned char i = 0; i < credit.size(); i++)
            credit[i].text.setFont(font);
    }

    MusicManager::Instance()->play(1, 100, true);
    MusicManager::Instance()->player.setLoop(false);
}

void Credit::update() {

    transition.update();
    background.update();

    for (unsigned char i = 0; i < credit.size(); i++) {
        if (lastTime == 0)
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > credit[i].startTime)
            credit[i].active = true;

        if (credit[i].active) {
            if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > credit[i].startTime + 5000)
                credit[i].trans -= 15;
            credit[i].text.setColor(sf::Color(255, 255, 255, credit[i].trans));
            if (credit[i].trans == 0) {
                credit[i].active = false;
                credit.erase(credit.begin() + i);
            }
        }

    }

    if (MusicManager::Instance()->stopped()) {
        if (transition.action == 2)
            transition.initialize(1);
        else if (transition.finish) {
            finished = true;
            MusicManager::Instance()->player.setLoop(true);
        }
    }
}

void Credit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned char i = 0; i < background.background.size(); i++) {
        target.draw(background.background[i], states);
        if (stage == 5) {
            for (unsigned char a = 0; a < 2; a++)
                target.draw(background.animation[a], states);
        }
    }
    target.draw(fade, states);

    for (unsigned char i = 0; i < credit.size(); i++) {
        if (credit[i].active)
            target.draw(credit[i].text, states);
    }
    target.draw(transition, states);
}