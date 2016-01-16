/* 
 * File:   Hud.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 10 mars 2013, 09:18
 */

#include "Hud.h"

Hud::Hud() {
    countEnergy = 0;
    countWeapon = 0;
    trans_pushstart = 0;
    transPilot = 255;
    countLives = 0;
    transPilot = 0;
    lastTime = 0;
    if (Language::Instance()->language != "english") {
        text = Language::Instance()->french[3];
    } else text = Language::Instance()->english[3];
    
    hud.reserve(2);
    m_text.reserve(8);
    lives.reserve(5);
    energy.reserve(10);
    weapon.reserve(10);
    
    int position = 640;
    int position2 = 650;
    for (unsigned char i = 0; i < 10; i++) {
        if (i < 2) {
            hud.emplace_back();
            hud[i].setTexture(FileManager::Instance()->hud);
        }        
        if (i < 5) {
        position += 20;
        lives.emplace_back();
        lives[i].setPosition(Vector2f(position,60));
        }
        
        if (i < 8) 
            m_text.emplace_back();
        
        position2 += 10;
        energy.emplace_back();
        energy[i].setPosition(Vector2f(position2,100));
        
        weapon.emplace_back();
        weapon[i].setPosition(Vector2f(position2,135));
  
    }
    hud[0].setPosition(640,10);
    hud[1].setPosition(0,10);
    time = sf::milliseconds(500);
    last = 0;
    count = 0;
    collision = false;
    goldCollision = false;
    loadcontent();
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::setLanguage() {
    
    if (Language::Instance()->language != "english") {
        text = Language::Instance()->french[3];
    } else text = Language::Instance()->english[3];
    
    for (unsigned char i = 0; i < 8; i++) {
            if (i <= 4)
            m_text[i].setString(text[i]);
        }
}

void Hud::pushStart() {
   
    if (pushstart) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - last > time.asMilliseconds()) {
            count +=1;
             if (count > 2)
                count = 0;
            last = GameTime::Instance()->getElapsedTime().asMilliseconds();
            }
        
        if (count == 1) {
                trans_pushstart = 0;
            } 
        else if (count == 2) {
                trans_pushstart = 255;  
        }
    }
    
    m_text[2].setColor(sf::Color(255, 255, 255, trans_pushstart));
}

void Hud::loadcontent() {
    
    if(font.loadFromFile(FileManager::Instance()->font))
    {
        for (unsigned char i = 0; i < 8; i++) {
            m_text[i].setFont(font);
            m_text[i].setScale(0.4,0.4);
            m_text[i].setColor(sf::Color::White);
        }
        
        
        m_text[0].setPosition(660,20); // Credits
        m_text[1].setPosition(660,40); // Lives
        
        // Push Start
        trans_pushstart = 255;
        m_text[2].setPosition(660,60); 
        
        
        m_text[3].setPosition(660,80); // Energy
        m_text[4].setPosition(660,115); // Second Weapon
        
        m_text[5].setPosition(730,20); // Nombre de credits
        
        int a = (m_text[2].getPosition().x + m_text[2].getCharacterSize()) + 75;
        m_text[6].setPosition(a,60); // Compteur
        
        // Score
        m_text[7].setPosition(660,150); 
        m_text[7].setScale(0.6,0.6);
        m_text[7].setString("0");

    } else ErrorManager::Instance()->save(3, "File Missing : " + FileManager::Instance()->font);
    
        for (unsigned char i = 0; i < lives.size(); i++)
            lives[i].setTexture(FileManager::Instance()->items[8]);
        for (unsigned char i = 0; i < energy.size(); i++)
            energy[i].setTexture(FileManager::Instance()->items[6]);
        for (unsigned char i = 0; i < weapon.size(); i++)
            weapon[i].setTexture(FileManager::Instance()->items[5]);
}

void Hud::update() {
    
    if (pushstart)
    pushStart();
    
    pilot.energy = countEnergy;
    pilot.lives = countLives;
    pilot.collision = collision;
    pilot.goldCollision = goldCollision;
    pilot.update();

}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned char i = 0; i < 2; i++)
        target.draw(hud[i], states);
    
    for (unsigned char i = 0; i < m_text.size(); i ++) {
        if (i != 2 && i != 6)
            target.draw(m_text[i], states);
    } 
    
    if (pushstart) {
        target.draw(m_text[2], states);
        target.draw(m_text[6], states);
    }

    for (unsigned char i = 0; i < countLives; i++)
        target.draw(lives[i], states);
    
    for (unsigned char i = 0; i < countWeapon; i++)
        target.draw(weapon[i], states);
    
    for (unsigned char i = 0; i < countEnergy; i++)
        target.draw(energy[i], states);
  
    target.draw(pilot, states);

}

Hud::Pilot::Pilot() {
    sprite.setTexture(FileManager::Instance()->pilot);
    sprite.setPosition(15,25);
    frameSize = Vector2f(sprite.getTexture()->getSize().x / frameCount, sprite.getTexture()->getSize().y);
    sourceRect = IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y);
    sprite.setTextureRect(sourceRect);
    color = Color(236, 13, 13,135);
    initialize();
}

void Hud::Pilot::initialize() {
    energy = 0;
    lives = 0;
    trans = 255;
    lastTime = 0;
    count = 0;
    currentFrame = 0;
    collision = false;
    goldCollision = false;
}

void Hud::Pilot::update() {
    
    sourceRect = IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y);
    sprite.setTextureRect(sourceRect);
    
    // Mort du pilote
    if (lives > 0)
        trans = 255;
    else {
        if (lastTime == 0)
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 100 && trans > 0) {
            trans -= 5;
            lastTime = 0;
        }
    }
    
    // Niveau de vie faible
    if ((energy < 3 && lives > 0) || collision || goldCollision) {
        if (lastTime == 0) {
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
            if (energy > 2) {
                if (!goldCollision) {
                    sprite.setColor(color);
                } else if (goldCollision) {
                    sprite.setColor(Color(255, 223, 0, 150));
                }
            }
        }
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 100) {
            if (count < 2)
                count += 1;
            else count = 0;
            
            if (count == 0) {
                sprite.setColor(color);
            } else if (count == 1) {
                sprite.setColor(sf::Color::White);
                if (energy > 2) {
                if (collision)
                    collision = false;
                else if (goldCollision)
                    goldCollision = false;
                }
            }
            lastTime = 0;
        }
    } else sprite.setColor(sf::Color(255,255,255,trans));
    
    // Changement d'état
    if (energy > 7)
        currentFrame = 0;
    else if (energy < 7 && energy > 5)
        currentFrame = 1;
    else if (energy < 5 && energy > 3)
        currentFrame = 2;
    else if (energy < 3)
        currentFrame = 3;
}

void Hud::Pilot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}