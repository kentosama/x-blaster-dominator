    /* 
 * File:   Stage.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 1 mars 2013, 18:05
 */

#include "Stage.h"

Stage::Stage() {
    score = 0;
    newscore = 0;
    totalEnemyDead = 0;
    initialized = false;
    lostLives = 0;
    sound.reserve(5);
    
    // Setbuffer
    // sound[1] = Explosion
    // sound[2] = Shot
    // sound[3] = Pause
    // sound[4] = Power Up
    
    for (unsigned char i = 0; i < 6; i++) {
        sound.emplace_back();
    }

    sound[1].setVolume(75);
    sound[2].setVolume(45);
    sound[5].setVolume(85);
    
    messagesStatut.reserve(3);
    for (unsigned char i = 0; i < 3; i++) {
        messagesStatut.emplace_back();
        messagesStatut[i] = 0;
    }
    
    textGameover.setTexture(FileManager::Instance()->text[5]);
}

Stage::Stage(const Stage& orig) {
}

Stage::~Stage() {
}

string Stage::to_string(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void Stage::initialize(unsigned char stage) {
    gameDifficulty = Profil::Instance()->mode;
    this->stage = stage;
    if (stage == 1) {
        enemyDead = 0;
        totalEnemyDead = 0;
        setLanguage();
        hud.setLanguage();
        elapsedTime = Time::Zero;
        textGameover.setPosition(270, -300);
        // Initialisation du joueur
        player.initialize(true);
        player.lives -= lostLives;
        bulletPortion = player.bullet / 10;
        hud.countLives = player.lives;
        hud.countEnergy = player.health / 10;
        hud.countWeapon = player.bullet / bulletPortion;
        
        for (unsigned char i = 1; i < 5; i++)
        sound[i].setBuffer(FileManager::Instance()->sound[i +1]);
        MusicManager::Instance()->play(stage +1, 60, true);
    } else {
        MusicManager::Instance()->play(stage +1, 80, true);
        player.initialize(false);
    }

    sound[0].setBuffer(FileManager::Instance()->sndStage[stage - 1]); // Stage voice
    sound[5].setBuffer(FileManager::Instance()->sound[2]);

    textStage.initialize(stage, Vector2f(0, 300), 0, +6);

    // Initialisation des vectors
    bullets.clear();
    bulletsEnemy.clear();
    explosions.clear();
    powerups.clear();
    stateStage.clear();

    bullets.reserve(80);
    bulletsEnemy.reserve(200);
    explosions.reserve(20);
    powerups.reserve(10);
    stateStage.reserve(1);
    stateStage.emplace_back(stage);

    // Messages
    messagesStatut.clear();
    for (unsigned char i = 0; i < 3; i++) {
        messagesStatut[i] = 0;
    }

  
    snd_voice_played = false;
    creditPause = false;
    
    lastPressedBouton = 0;
    lastTime = 0;
    lastBossSoundExplosion = 0;
    time = 0;
    pause = false;
    
    if (stage == 1) {
        score = 0;
        newscore = 0;
    }
    
    gameoverActive = false;
    finished = false;
    setBonnus = false;
    limitCredit = 60;
    lastTimeLimit = 0;
    activeNextStage = false;
    background.initialize(stage);

#ifdef _DEBUG
    goNextStage = false;
    debug.stage = stage;
    debug.wave = wave.currentWave;
    debug.initialize();
#endif
    
    transition.initialize(2);
    GameTime::Instance()->restart();
    clock.restart();
    wave.initialize(stage, 1);
    lastLives = player.lives;
    lastSuperAttack = player.countSuperAttack;
    lastScore = score;
    
    if (!initialized)
        initialized = true;
}

bool Stage::endWave() {
    if (wave.enemies.size() > 0)
        return true;
    else return false;   
}

void Stage::setLanguage() {

    if (Language::Instance()->language != "english") {
        messages = Language::Instance()->french[4];
    } else messages = Language::Instance()->english[4];
}

void Stage::playerFire(unsigned char type) {

    if (type == 0) {
        if (time - player.lastShot > player.shotTime.asMilliseconds()) {
            player.lastShot = time;
            moduleFire();
            if (player.weapon == 0 || player.weapon >= 2)
                bullets.emplace_back(Vector2f(player.sprite.getPosition().x + player.sprite.getTexture()->getSize().x / 8.5, player.sprite.getPosition().y), 0);
            if (player.weapon >= 1) {
                bullets.emplace_back(Vector2f(player.sprite.getPosition().x + 2, player.sprite.getPosition().y), 0);
                bullets.emplace_back(Vector2f(player.sprite.getPosition().x + 28, player.sprite.getPosition().y), 0);
            }
            sound[2].play();
        }

    } else if (type == 1) {
        if (time - player.lastShot > player.secondaryShotTime.asMilliseconds()) {
            player.lastShot = time;
            if (player.bullet > 0) {
                bullets.emplace_back(Vector2f(player.sprite.getPosition().x + 2, player.sprite.getPosition().y), 1);
                bullets.emplace_back(Vector2f(player.sprite.getPosition().x + 28, player.sprite.getPosition().y), 1);
                sound[2].play();
                player.bullet -= 1;
            }
        }

    }
}

void Stage::moduleFire() {

    if (player.module >= 1)
        bullets.emplace_back(Vector2f(player.modules[0].getPosition().x + 4, player.modules[0].getPosition().y), 0);
    if (player.module >= 2)
        bullets.emplace_back(Vector2f(player.modules[1].getPosition().x + 4, player.modules[1].getPosition().y), 0);
}

void Stage::enemyUpdate() {
    for (unsigned char i = 0; i < wave.enemies.size(); i++) {
        if (player.active && wave.enemies[i].active) {
             if ((wave.enemies[i].getPosition().y < player.getPosition().y && player.inZone && wave.enemies[i].fire && wave.enemies[i].getPosition().y > 20) || (wave.enemies[i].enemyType == 12 && wave.enemies[i].fire && player.inZone)) {
                if (GameTime::Instance()->getElapsedTime().asMilliseconds() - wave.enemies[i].lastShot > wave.enemies[i].shotTime.asMilliseconds()) {
                    wave.enemies[i].lastShot = GameTime::Instance()->getElapsedTime().asMilliseconds();
                    if (wave.enemies[i].enemyType == 0)
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                    else if (wave.enemies[i].enemyType == 1) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 15, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 15, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 2) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 15, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 10, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 3) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y - 10), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y - 10), 1, 2, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 4) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 2, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 5) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 2, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 10, wave.enemies[i].getPosition().y), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 10, wave.enemies[i].getPosition().y), 1, 2, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 6) {
                        if (wave.enemies[i].count == 0) {
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 10, wave.enemies[i].getPosition().y), 0, 3, player.getPosition());
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x, wave.enemies[i].getPosition().y), 0, 3, player.getPosition());
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 10, wave.enemies[i].getPosition().y), 0, 3, player.getPosition());
                        } else if (wave.enemies[i].count == 1)
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x, wave.enemies[i].getPosition().y), 1, 3, player.getPosition());
                        wave.enemies[i].count++;
                    } else if (wave.enemies[i].enemyType == 7) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 3, player.getPosition());
                    } else if (wave.enemies[i].enemyType == 8) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 13, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 7, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 9) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 4, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 0, 5, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 10) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 5, wave.enemies[i].getPosition().y), 1, wave.enemies[i].count, Vector2f(0, 0));
                        wave.enemies[i].count += 1;
                    } else if (wave.enemies[i].enemyType == 11) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y + 20), 0, 0, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 12) {
                        if (wave.enemies[i].movement == 8)
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x, wave.enemies[i].getPosition().y -8), 1, 6, Vector2f(0, 0));
                        else if (wave.enemies[i].movement == 9)
                            bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x, wave.enemies[i].getPosition().y -8), 1, 7, Vector2f(0, 0));
                    } else if (wave.enemies[i].enemyType == 13) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 3, Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 1, Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y), 1, 2, Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y));
                    } else if (wave.enemies[i].enemyType == 14) {
                        char position = -30;
                        for (unsigned char a = 0; a < 5; a++) {
                             //bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 3, wave.enemies[i].getPosition().y +position), 0, 0, Vector2f(0,0));
                             
                             bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 20, wave.enemies[i].getPosition().y +position), 0, 0, Vector2f(0,0));
                             bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 30, wave.enemies[i].getPosition().y +position), 0, 0, Vector2f(0,0));
                             
                             bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 12, wave.enemies[i].getPosition().y +position), 0, 0, Vector2f(0,0));
                             bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 22, wave.enemies[i].getPosition().y +position), 0, 0, Vector2f(0,0));
                             position += 10;
                        }
                    } else if (wave.enemies[i].enemyType == 15) {
                        
                        if(wave.enemies[i].count < 2) {
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 33, wave.enemies[i].getPosition().y +30), 1, 1, Vector2f(0,0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 33, wave.enemies[i].getPosition().y +30), 1, 2, Vector2f(0,0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 33, wave.enemies[i].getPosition().y +30), 1, 3, player.sprite.getPosition());
                        
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 23, wave.enemies[i].getPosition().y +30), 1, 1, Vector2f(0,0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 23, wave.enemies[i].getPosition().y +30), 1, 2, Vector2f(0,0));
                        bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 23, wave.enemies[i].getPosition().y +30), 1, 3, player.sprite.getPosition());
                        } else {
                          bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x + 40, wave.enemies[i].getPosition().y +30), 1, 3, player.sprite.getPosition());
                          bulletsEnemy.emplace_back(Vector2f(wave.enemies[i].getPosition().x - 33, wave.enemies[i].getPosition().y +30), 1, 3, player.sprite.getPosition());
                        }
                        wave.enemies[i].count++;
                    }
                } 
            }

            // SuperAttack
            if (player.activeSuperAttack) {
                for(unsigned char b = 0; b < 3; b++) {
                  if (wave.enemies[i].rect[b].intersects(player.SuperAttack.rectangle))
                      wave.enemies[i].health = 0;
                }
            }
            // Gestion des collisions avec joueur
            for (unsigned char b = 0; b < 3; b++) {
                for (unsigned char a = 0; a < 4; a++) {
                    if (wave.enemies[i].rect[b].intersects(player.rect[a])) {
                        if (!player.dead)
#ifdef _DEBUG
                            if (!player.godMode)
                                 player.health -= wave.enemies[i].damage;
#else 
                        player.health -= wave.enemies[i].damage;
#endif
                        wave.enemies[i].health = 0;
                    }
                }
            }

            // Gestion des collisions avec les projectiles
            for (unsigned char b = 0; b < bullets.size(); b++) {
                for (unsigned char a = 0; a < wave.enemies[i].rect.size(); a++) {
                    if (wave.enemies[i].rect[a].intersects(bullets[b].rectangle)) {
                        if (wave.enemies[i].health > 0)
                            explosions.emplace_back(bullets[b].getPosition(), Vector2f(0, 0), 0.0f, Vector2f(0.2f, 0.2f));
                        wave.enemies[i].collision = true;
                        wave.enemies[i].health -= bullets[b].damage;
                        bullets[b].active = false;

                    }
                }
            }

            // Mort des ennemies
            if (wave.enemies[i].health <= 0) {
                sound[1].play();
                if (wave.enemies[i].enemyType < 14) {
                    if (wave.enemies[i].enemyType != 12) {
                        if (wave.enemies[i].getRotation() == 0.0f)
                            explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x - (wave.enemies[i].getSize().x / 2), wave.enemies[i].getPosition().y - (wave.enemies[i].getSize().y / 2)), wave.enemies[i].getOrigin(), wave.enemies[i].sprite.getRotation(), Vector2f(1.2, 1.2));
                        else if (wave.enemies[i].getRotation() > 0)
                            explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x + (wave.enemies[i].getSize().x / 2), wave.enemies[i].getPosition().y - (wave.enemies[i].getSize().y / 2)), wave.enemies[i].getOrigin(), wave.enemies[i].getRotation(), Vector2f(1.2, 1.2));
                        else if (wave.enemies[i].getRotation() < 0)
                            explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x - (wave.enemies[i].getSize().x / 2), wave.enemies[i].getPosition().y + (wave.enemies[i].getSize().y / 2)), wave.enemies[i].getOrigin(), wave.enemies[i].getRotation(), Vector2f(1.2, 1.2));
                    } else if (wave.enemies[i].getRotation() == 0.0f) {
                        explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x - (wave.enemies[i].getSize().x * 1.5), wave.enemies[i].getPosition().y  - (wave.enemies[i].getSize().y / 2)), wave.enemies[i].getOrigin(), wave.enemies[i].sprite.getRotation(), Vector2f(1.2, 1.2));
                    } else if (wave.enemies[i].getRotation() == -180.0f) {
                        explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x + (wave.enemies[i].getSize().x * 2), wave.enemies[i].getPosition().y  + (wave.enemies[i].getSize().y / 2)), wave.enemies[i].getOrigin(), wave.enemies[i].sprite.getRotation(), Vector2f(1.2, 1.2));
                    }
                } else explosions.emplace_back(Vector2f(wave.enemies[i].getPosition().x, wave.enemies[i].getPosition().y), wave.enemies[i].getOrigin(), wave.enemies[i].getRotation(), Vector2f(1.5, 1.5));

                if (wave.enemies[i].powerUp)
                    powerups.emplace_back(Vector2f(wave.enemies[i].sprite.getPosition().x + 5, wave.enemies[i].sprite.getPosition().y + 5));
                if (gameDifficulty == 2)
                newscore += wave.enemies[i].score;
                else if (gameDifficulty == 1)
                newscore += wave.enemies[i].score * 2;
                else newscore += (wave.enemies[i].score * 2) + 50;
                wave.enemies[i].active = false;
                enemyDead += 1;
            }
        } else if (!wave.enemies[i].active)
                wave.enemies.erase(wave.enemies.begin() + i);
    }
}

void Stage::bossUpdate() {

    // Target
    if (wave.boss.back().activeShotB && wave.boss.back().modeShotB == 1) {
        if (!player.target.active)
            player.target.active = true;
    } else if (player.target.active)
        player.target.active = false;

    // Fire

    if (wave.boss.back().activeShotA) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - wave.boss.back().lastTime[0] > wave.boss.back().shotTimeA.asMilliseconds()) {
            wave.boss.back().lastTime[0] = GameTime::Instance()->getElapsedTime().asMilliseconds();

            if (stage == 1) {
                if (wave.boss.back().modeShotA == 0) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 26, wave.boss.back().getPosition().y + 40), 0, 0, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 48, wave.boss.back().getPosition().y + 40), 0, 0, Vector2f(0, 0));

                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 20, wave.boss.back().getPosition().y + 40), 0, 0, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 42, wave.boss.back().getPosition().y + 40), 0, 0, Vector2f(0, 0));

                } else if (wave.boss.back().modeShotA == 1) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 26, wave.boss.back().getPosition().y + 40), 0, 1, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 48, wave.boss.back().getPosition().y + 40), 0, 2, Vector2f(0, 0));

                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 20, wave.boss.back().getPosition().y + 40), 0, 2, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 42, wave.boss.back().getPosition().y + 40), 0, 1, Vector2f(0, 0));
                }
            }
            
            else if (stage == 2) {
                if (wave.boss.back().modeShotA == 0) {

                    if (gameDifficulty == 2) {
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 30, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 20, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                    } else {
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 40, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 30, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 30, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 20, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y + 40), 0, 3, player.getPosition());
                    }
                     
                } else if (wave.boss.back().modeShotA == 1) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x, wave.boss.back().getPosition().y + 40), 1, 3, player.getPosition());
                    
                }
                
            } else if (stage == 3) {
                if (wave.boss.back().modeShotA == 0) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y + 10), 0, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 10, wave.boss.back().getPosition().y + 10), 0, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 25, wave.boss.back().getPosition().y + 10), 0, 1, Vector2f(0,0));
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y + 10), 0, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +5, wave.boss.back().getPosition().y + 10), 0, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 15, wave.boss.back().getPosition().y + 10), 0, 2, Vector2f(0,0));
                
                } else if (wave.boss.back().modeShotA == 1) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 60, wave.boss.back().getPosition().y + 10), 0, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y + 10), 0, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 45, wave.boss.back().getPosition().y + 10), 0, 1, Vector2f(0,0));
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 50, wave.boss.back().getPosition().y + 10), 0, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y + 10), 0, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 35, wave.boss.back().getPosition().y + 10), 0, 2, Vector2f(0,0));
                    
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 60, wave.boss.back().getPosition().y - 20), 0, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y - 20), 0, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 45, wave.boss.back().getPosition().y - 20), 0, 1, Vector2f(0,0));

                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 50, wave.boss.back().getPosition().y - 20), 0, 2, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y - 20), 0, 0, Vector2f(0, 0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 35, wave.boss.back().getPosition().y - 20), 0, 2, Vector2f(0, 0));


                } else if (wave.boss.back().modeShotA == 3) {
                         bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 20, wave.boss.back().getPosition().y + 10), 0, 3, player.getPosition());
                         bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y + 10), 0, 3, player.getPosition());
                }
            }
        }
    }

    if (wave.boss.back().activeShotB) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - wave.boss.back().lastTime[1] > wave.boss.back().shotTimeB.asMilliseconds()) {
            bool action = false;
            if (stage == 1) {
                if (wave.boss.back().modeShotB == 0) {
                    if (wave.boss.back().activeCanonA) {
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 70, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 70, wave.boss.back().getPosition().y + 40), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 70, wave.boss.back().getPosition().y + 40), 1, 2, Vector2f(0, 0));
                    }
                    if (wave.boss.back().activeCanonB) {
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 65, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 65, wave.boss.back().getPosition().y + 40), 1, 1, Vector2f(0, 0));
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 65, wave.boss.back().getPosition().y + 40), 1, 2, Vector2f(0, 0));
                    }
                } else if (wave.boss.back().modeShotB == 1) {
                    if (wave.boss.back().activeCanonA)
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 70, wave.boss.back().getPosition().y + 40), 1, 3, player.getPosition());
                    if (wave.boss.back().activeCanonB)
                        bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 65, wave.boss.back().getPosition().y + 40), 1, 3, player.getPosition());
                }
            } else if (stage == 2) {
                if (wave.boss.back().modeShotB == 0) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -100, wave.boss.back().getPosition().y + 40), 1, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -100, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -100, wave.boss.back().getPosition().y + 40), 1, 2, Vector2f(0,0));
                    
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +90, wave.boss.back().getPosition().y + 40), 1, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +90, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +90, wave.boss.back().getPosition().y + 40), 1, 2, Vector2f(0,0));
                    
                } else if (wave.boss.back().modeShotB == 1) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -110, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -100, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x -90, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                    
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +100, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +90, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x +80, wave.boss.back().getPosition().y + 40), 1, 0, player.getPosition());
                }
            } else if (stage == 3) {
                if (wave.boss.back().modeShotB == 0) {
                    action = true;
                    if (wave.boss.back().activeCanonA) {

                        if (wave.boss.back().getCurrentFrame() == 3 && wave.boss.back().getCurrentFrameLine() == 0) {
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 155, wave.boss.back().getPosition().y + 20), 1, 0, Vector2f(0, 0));
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 77, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                            wave.boss.back().countFire++;
                        } else if (wave.boss.back().getCurrentFrame() == 3 && wave.boss.back().getCurrentFrameLine() == 1) {
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 117, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                            wave.boss.back().countFire++;
                        }
                    }

                    if (wave.boss.back().activeCanonB) {
                        if (wave.boss.back().getCurrentFrame() == 3 && wave.boss.back().getCurrentFrameLine() == 0) {
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 145, wave.boss.back().getPosition().y + 20), 1, 0, Vector2f(0, 0));
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 67, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                            wave.boss.back().countFire++;
                        } else if (wave.boss.back().getCurrentFrame() == 3 && wave.boss.back().getCurrentFrameLine() == 1) {
                            bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 107, wave.boss.back().getPosition().y + 40), 1, 0, Vector2f(0, 0));
                            wave.boss.back().countFire++;
                        }
                    }
                    
                    if (wave.boss.back().countFire == 4) {
                        wave.boss.back().countFire = 0;
                        action = false;
                    }
                
                } else  if (wave.boss.back().modeShotB == 1) {
                    
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 90, wave.boss.back().getPosition().y - 20), 0, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 70, wave.boss.back().getPosition().y - 20), 0, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 80, wave.boss.back().getPosition().y - 20), 0, 1, Vector2f(0,0));
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 80, wave.boss.back().getPosition().y - 20), 0, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 60, wave.boss.back().getPosition().y - 20), 0, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 70, wave.boss.back().getPosition().y - 20), 0, 2, Vector2f(0,0));
                    
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 40, wave.boss.back().getPosition().y - 20), 2, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 30, wave.boss.back().getPosition().y - 20), 2, 3, player.getPosition());
                
                } else  if (wave.boss.back().modeShotB == 2) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 120, wave.boss.back().getPosition().y - 20), 2, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 100, wave.boss.back().getPosition().y - 20), 2, 1, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 80, wave.boss.back().getPosition().y - 20), 2, 1, Vector2f(0,0));
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 110, wave.boss.back().getPosition().y - 20), 2, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 90, wave.boss.back().getPosition().y - 20), 2, 2, Vector2f(0,0));
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 70, wave.boss.back().getPosition().y - 20), 2, 2, Vector2f(0,0));
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 120, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 100, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 80, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 110, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 90, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 70, wave.boss.back().getPosition().y - 60), 2, 3, player.getPosition());
                } else  if (wave.boss.back().modeShotB == 3) {
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 120, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 100, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x - 80, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 110, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 90, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                    bulletsEnemy.emplace_back(Vector2f(wave.boss.back().getPosition().x + 70, wave.boss.back().getPosition().y - 60), 1, 3, player.getPosition());
                }
                
            } else if (stage == 4) {
                
        }
        
        if (!action)
            wave.boss.back().lastTime[1] = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
    }
    // Collision with the bullets
    if (wave.boss.back().health[0] > 0) {
        for (int i = 0; i < 6; i++) {
            for (unsigned char b = 0; b < bullets.size(); b++) {
                if (wave.boss.back().rect[i].intersects(bullets[b].rectangle)) {
                    if (i < 4)
                        wave.boss.back().health[0] -= bullets[b].damage;
                    else if (i == 4)
                        wave.boss.back().health[1] -= bullets[b].damage;
                    else if (i == 5)
                        wave.boss.back().health[2] -= bullets[b].damage;
#ifdef _DEBUG                
                    //std::cout << "Energy : " << to_string(wave.boss.back().health[0]) << std::endl;
                    //std::cout << "Energy canon 1 : " << to_string(wave.boss.back().health[1]) << std::endl;
                    //std::cout << "Energy canon 2 : " << to_string(wave.boss.back().health[2]) << std::endl;
#endif
                    newscore += 10;
                    if(sound[5].getStatus() == 0) {
                       sound[5].play(); 
                    } else {
                        if(GameTime::Instance()->getElapsedTime().asMilliseconds() - lastBossSoundExplosion > 250) {
                            lastBossSoundExplosion = GameTime::Instance()->getElapsedTime().asMilliseconds();
                            sound[5].play();
                        }
                    }
                    explosions.emplace_back(Vector2f(bullets[b].getPosition().x - 20, bullets[b].getPosition().y - 20), Vector2f(0, 0), 0.0f, Vector2f(1.0f, 1.0f));
                    bullets.erase(bullets.begin() + b);
                    wave.boss.back().collision[i] = 1;
                }
            }
        }

        // Canons

        if (stage == 1) {

            if (wave.boss.back().health[1] == 0 && wave.boss.back().activeCanonA) {
                newscore += 2000;
                explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - (wave.boss.back().getSize().x / 2) - 66, wave.boss.back().getPosition().y), Vector2f(0, 0), 0.0f, Vector2f(2.0f, 2.0f));
                wave.boss.back().activeCanonA = false;
            } else if (wave.boss.back().health[2] == 0 && wave.boss.back().activeCanonB) {
                newscore += 2000;
                explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x + 88, wave.boss.back().getPosition().y), Vector2f(0, 0), 0.0f, Vector2f(2.0f, 2.0f));
                wave.boss.back().activeCanonB = false;
            }
        } else if (stage == 2) {

            if (wave.boss.back().health[1] == 0 && wave.boss.back().activeCanonA) {
                newscore += 3000;
                sound[1].play();
                explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 107, wave.boss.back().getPosition().y - 20), Vector2f(0, 0), 0.0f, Vector2f(2.0f, 2.0f));
                wave.boss.back().activeCanonA = false;
            } else if (wave.boss.back().health[2] == 0 && wave.boss.back().activeCanonB) {
                newscore += 3000;
                sound[1].play();
                explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x + 63, wave.boss.back().getPosition().y - 20), Vector2f(0, 0), 0.0f, Vector2f(2.0f, 2.0f));
                wave.boss.back().activeCanonB = false;
            }
        }
        
        // SuperAttack
        
        if (player.activeSuperAttack && wave.boss.back().inZone) {
            wave.boss.back().collision[0] = 1;
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 50, wave.boss.back().getPosition().y - 60), Vector2f(0, 0), 0.0f, Vector2f(1.8f, 1.8f));
            sound[1].play();
            for(unsigned char i = 0; i < 3; i++)
            wave.boss.back().health[i] -= 10;
            newscore += 30;
        }
    }

    if (wave.boss.back().destroyed) {
        sound[1].play();
        if (stage == 1) {

            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - (wave.boss.back().getSize().x / 2) - 70, wave.boss.back().getPosition().y - 70), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y - 70), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 50, wave.boss.back().getPosition().y - 60), Vector2f(0, 0), 0.0f, Vector2f(2.5f, 2.5f));

        } else if (stage == 2) {
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 120, wave.boss.back().getPosition().y - 60), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 10, wave.boss.back().getPosition().y - 60), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
        } else if (stage == 3) {
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - (wave.boss.back().getSize().x / 2) - 70, wave.boss.back().getPosition().y - 70), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x + 10, wave.boss.back().getPosition().y - 70), Vector2f(0, 0), 0.0f, Vector2f(2.2f, 2.2f));
            explosions.emplace_back(Vector2f(wave.boss.back().getPosition().x - 50, wave.boss.back().getPosition().y - 60), Vector2f(0, 0), 0.0f, Vector2f(2.5f, 2.5f));
        }
        wave.boss.back().destroyed = false;
        wave.boss.back().active = false;
    }

}

void Stage::playerControl() {

    if (GamePadManager::Instance()->gamepadConnected) {
        if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0]))
            playerFire(0);
        else if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[1]))
            playerFire(1);
    }
    
        if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0]))
            playerFire(0);
        else if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[1]))
            playerFire(1);
#if defined _DEBUG
        else if (Keyboard::isKeyPressed(Keyboard::C)) {
            goNextStage = true;
        }
#endif
}

void Stage::playerUpdate() {

    if (player.active && player.inZone) {
        playerControl();

        // Collision avec le boss
        if (!player.dead) {
            if (wave.boss.size() == 1) {
                for (unsigned char i = 0; i < 6; i++) {

                    for (unsigned char b = 0; b < 4; b++) {
                        if (wave.boss.back().rect[i].intersects(player.rect[b])) {
#ifdef _DEBUG
                            if(!player.godMode)
#endif
                            player.health -= 10;
                            player.collision = true;
                        }
                    }
                }
            }
        }

        for (unsigned char i = 0; i < powerups.size(); i++) {
            if (powerups[i].active) {
                for (unsigned char b = 0; b < player.rect.size(); b++) {
                    if (powerups[i].rectangle.intersects(player.rect[b])) {
                        player.goldCollision = true;
                        sound[4].play();
                        if (powerups[i].powerup == 0) {
                            if (player.weapon != 2)
                                player.weapon += 1;
                            else newscore += 4000;
                        } else if (powerups[i].powerup == 1) {
                            if (player.module != 2) {
                                player.module += 1;
                                player.moduleClock.restart();
                            } else newscore += 4000;
                        }
                        powerups[i].active = false;
                    }
                }
            }
        }

        if (player.health <= 0) {
            sound[1].play();
            explosions.emplace_back(Vector2f(player.getPosition()), Vector2f(35 / 2, 35 / 2), 0, Vector2f(1.2, 1.2));
        }
    } else if (player.gameover()) {
        if (!gameoverActive)
            gameover();
        else {
            transition.update();
            if (!transition.active) 
                finished = true;
        }
    }
}

void Stage::bulletUpdate() {
    // Mise à jour des projectiles du joueur
    for (unsigned char i = 0; i < bullets.size(); i++) {
        if (!bullets[i].active)
            bullets.erase(bullets.begin() + i);
        bullets[i].update();
    }

    // Mise à jour des projectiles des ennemis
    for (unsigned char i = 0; i < bulletsEnemy.size(); i++) {
        if (!bulletsEnemy[i].active)
            bulletsEnemy.erase(bulletsEnemy.begin() + i);
        else {
            if (!player.dead && player.inZone && player.active) {
                for (unsigned char b = 0; b < 4; b++) {
                    if (bulletsEnemy[i].rectangle.intersects(player.rect[b])) {
                        player.collision = true;
                        if (player.health > 0)
                            explosions.emplace_back(bulletsEnemy[i].getPosition(), Vector2f(0, 0), 0.0f, Vector2f(0.2f, 0.2f));
#ifdef _DEBUG
                        if (!player.godMode)
                            player.health -= bulletsEnemy[i].damage;
#else
                        player.health -= bulletsEnemy[i].damage;
#endif
                       
                        if (wave.boss.size() > 0) {
                            if (bulletsEnemy[i].damage == 50) {
                                if (gameDifficulty == 0)
                                    wave.boss.back().health[0] += 1000;
                                else if (gameDifficulty == 1)
                                    wave.boss.back().health[0] += 800;
                                else wave.boss.back().health[0] += 500;
                            }
                        }
                        bulletsEnemy[i].active = false;
                    }
                }
            }
        } bulletsEnemy[i].update();
    }
}

void Stage::messagebox() {

    
}

void Stage::creditUpdate() {
    if (player.getCredits() && explosions.size() <= 0) {

        if(MusicManager::Instance()->creditPlayer.getStatus() == 0)
        MusicManager::Instance()->playCredit();
        hud.pushstart = true;
        hud.m_text[6].setString(to_string(limitCredit));

        if (lastTimeLimit == 0) {
            GameTime::Instance()->pause();
            lastTimeLimit = time;
            pause = true;
        }

        if (time - lastTimeLimit > timeLimit.asMilliseconds()) {

            lastTimeLimit = time;
            limitCredit -= 1;
        }

        if (Joystick::isConnected(0)) {
            if (time - lastPressedBouton > pressBouton.asMilliseconds()) {

                if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[3])) {
                    lastTimeLimit = 0;
                    player.setNewCredit();
                    limitCredit = 60;
                    MusicManager::Instance()->stopCredit();
                    GameTime::Instance()->start();
                    pause = false;
                    lastPressedBouton = time;
                } else if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[0])) {
                    limitCredit -= 10;
                    lastPressedBouton = time;
                }
            }
        }

        if (time - lastPressedBouton > pressBouton.asMilliseconds()) {
            if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[3])) {
                lastTimeLimit = 0;
                player.setNewCredit();
                limitCredit = 60;
                MusicManager::Instance()->stopCredit();
                GameTime::Instance()->start();
                pause = false;
                lastPressedBouton = time;
            } else if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0])) {
                limitCredit -= 10;
                lastPressedBouton = time;
            }
        }

        if (limitCredit <= 0) {
            MusicManager::Instance()->stopCredit();
            player.credits = 0;
            GameTime::Instance()->start();
            lastTimeLimit = 0;
            pause = false;

        }
    } else
        hud.pushstart = false;

}

void Stage::gameover() {

    if (textGameover.getPosition().y < 250) {
        textGameover.move(0, +1);
    }
    else {
        if(MusicManager::Instance()->getVolume() != 0)
        MusicManager::Instance()->fadingOut = true;
        score = newscore;
        transition.initialize(1);
        Profil::Instance()->gameover += 1;
        totalEnemyDead += enemyDead;
        saveProfil();
        saveScore();
        gameoverActive = true;
    }

}

void Stage::saveProfil() {
Profil::Instance()->totalTime += elapsedTime.asMilliseconds();

if (stage == 5 || player.gameover()) {
        Profil::Instance()->lastScore = score;
        Profil::Instance()->enemyDead += totalEnemyDead;   
        if (player.gameover()) {
            if (Profil::Instance()->gameover == 3)
                Profil::Instance()->credits += 1;
            else if (Profil::Instance()->gameover == 6)
                Profil::Instance()->credits += 1;
            else if (Profil::Instance()->gameover == 10)
                Profil::Instance()->credits += 1;
            else if (Profil::Instance()->enemyDead == 10000)
                Profil::Instance()->credits += 1;
            else if (Profil::Instance()->enemyDead == 20000)
                Profil::Instance()->credits += 1;
        }
    }


    if (score > Profil::Instance()->bestScore[stage - 1])
        Profil::Instance()->bestScore[stage - 1] = score;

    Profil::Instance()->save();

}

void Stage::setPause() {

    sound[3].play();
    lastPressedBouton = time;
    pause = true;
    pauseMenu.active = pause;
    MusicManager::Instance()->gamePause = pause;
    GameTime::Instance()->pause();
}

void Stage::update() {

#ifdef _DEBUG
    if (goNextStage)
        nextStage();

    if (debug.active) {
        debug.update();

        if (debug.option[0] == 1) {
            wave.test = true;
            debug.wave = 0;
        }
        else wave.test = false;

        if (debug.option[1] == 1) {
            for (unsigned char i = 0; i < wave.enemies.size(); i++) {
                if (!wave.enemies[i].showRectangle)
                    wave.enemies[i].showRectangle = true;
            } 
        } else for (unsigned char i = 0; i < wave.enemies.size(); i++) {
                if (wave.enemies[i].showRectangle)
                    wave.enemies[i].showRectangle = false;
            }

        if (debug.option[2] == 1)
            player.showRectangle = true;
        else player.showRectangle = false;


        // Boss
        
        if(debug.option[3] == 1)
            wave.boss.back().showRectangle = true;
        else wave.boss.back().showRectangle = false;
        
        // Bullets rectangle
        if (debug.option[4] == 1)
            for (unsigned char i = 0; i < bullets.size(); i++) {
                if (!bullets[i].showRectangle)
                    bullets[i].showRectangle = true;
            } else for (unsigned char i = 0; i < wave.enemies.size(); i++) {
                if (bullets[i].showRectangle)
                    bullets[i].showRectangle = false;
            }
        // GodMode
        if (debug.option[5] == 1) {
            if (!player.godMode)
                player.godMode = true;

        } else player.godMode = false;

        if (debug.option[6] == 1) {
            if (!player.unlimitedAttack)
                player.unlimitedAttack = true;

        } else player.unlimitedAttack = false;
        
        if (debug.option[7] == 1) {
            if (wave.boss.size() == 1)
                wave.boss.back().health[0] = 0;
        }

        if (debug.keyAction == 1)
            restart(stage);
        else if (debug.keyAction == 2)
            restart(1);
        else if (debug.keyAction == 3) {
            if (debug.stage != stage) {
                restart(debug.stage);
            }

            if (debug.wave != wave.currentWave) {

                wave.initialize(stage, debug.wave);
                std::cout << "Update ! >> Stage : " + to_string(wave.stage) + " Wave : " + to_string(wave.currentWave) + " " + to_string(wave.enemies.size()) << std::endl;
            }

            GameTime::Instance()->start();
            debug.active = false;
            MusicManager::Instance()->gamePause = false;
            debug.keyAction = 0;

        }
    }
#endif

    time = clock.getElapsedTime().asMilliseconds();


    if (!pause) {
#ifdef _DEBUG
        if (debug.active)
            return;
#endif
        
        // Hud update
        hud.m_text[7].setString(to_string(score));
        hud.m_text[5].setString(to_string(player.credits));
        hud.countLives = player.lives;
        hud.countEnergy = player.getHealthPortion();
        hud.collision = player.collision;
        hud.goldCollision = player.goldCollision;
        hud.countWeapon = player.bullet / bulletPortion;
        hud.update();
        
        elapsedTime = GameTime::Instance()->getElapsedTime();

        background.update();
        transition.update();

        if (startStage > time) {

            if (textStage.sprite.getPosition().x < 460)
                textStage.update();
            else if (!snd_voice_played) {
                sound[0].play();
                snd_voice_played = true;
            }
        } else {
            if (!gameoverActive)
                messagebox();

            bulletUpdate(); // Important !
            playerUpdate();
            wave.update();
            if (wave.boss.size() == 1)
                bossUpdate();
            enemyUpdate();
            
            for (unsigned char i = 0; i < powerups.size(); i++) {
                powerups[i].update();
                if (!powerups[i].active)
                    powerups.erase(powerups.begin() + i);
            }
            
             for (unsigned char i = 0; i < explosions.size(); i++) {
                explosions[i].update();
                if (!explosions[i].active)
                    explosions.erase(explosions.begin() + i);
            }
        }

        player.update();

        // Changement de musique pour le boss
        if (stage < 5) {
            if (wave.boss.size() == 1) { // Vérifie si un boss est présent
                if (wave.currentWave == 5 && !wave.boss[0].inZone) {
                    if (MusicManager::Instance()->getCurrentMusic() != 7) {
                        if (!MusicManager::Instance()->fadingOut)
                            MusicManager::Instance()->fadingOut = true;
                        
                        if (MusicManager::Instance()->getVolume() <= 0) {
                            MusicManager::Instance()->play(7, 100, true);
                        }
                    }
                }
            }
        }

        if (player.active) {
            if (Joystick::isConnected(0)) {
                if (Joystick::isButtonPressed(0, GamePadManager::Instance()->buttons[3]) && !wave.finished) {
                    if (time - lastPressedBouton > pressBouton.asMilliseconds())
                        setPause();
                }
            }
            if (WindowGame::Instance()->focus && !wave.finished) {
                if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[3])) {
                    if (time - lastPressedBouton > pressBouton.asMilliseconds())
                        setPause();
                }

#ifdef _DEBUG
                else if (Keyboard::isKeyPressed(Keyboard::F2) || Joystick::isButtonPressed(0, 6)) {
                    MusicManager::Instance()->gamePause = false;
                    std::cout << "Information : There are " + to_string(wave.enemies.size()) + " enemies in the wave " + to_string(wave.currentWave) + "." << std::endl;

                    for (unsigned char i = 0; i < wave.enemies.size(); i++) {
                        std::cout << "Position of enemies " + to_string(i) + " ( " + to_string(wave.enemies[i].enemyType) + " ) " + " >> " + to_string(wave.enemies[i].getPosition().x) + " / " + to_string(wave.enemies[i].getPosition().y) << " [" + to_string(wave.enemies[i].startTime) + "]" << std::endl;
                    }

                    if (time - lastPressedBouton > pressBouton.asMilliseconds()) {
                        if (!debug.active) {
                            sound[3].play();
                            lastPressedBouton = time;
                            MusicManager::Instance()->gamePause = true;
                            GameTime::Instance()->pause();
                            debug.active = true;
                        } else debug.active = false;
                    }
                }
#endif
            }
            else if (GamePadManager::Instance()->newState) {
                setPause();
                GamePadManager::Instance()->newState = false;
            }
            
            setNewScore(); // Mise à jour du score
            // Fin du stage
            if (wave.finished) {
                if (!setBonnus) {
                    stateStage[0].bonnus = getBonnus();
                    stateStage[0].enemyDead = enemyDead;
                    stateStage[0].score = newscore;
                    stateStage[0].lostLives = player.lostLives;
                    newscore += stateStage[0].bonnus;

                    setBonnus = true;
                } else if (stateStage[0].finished) {

                    score = newscore;
                    nextStage();

                } else {
                    stateStage[0].update();
                }
            }
        }
        
    } else {

        pauseMenu.update();

        if (pauseMenu.useraction > 0) {

            if (pauseMenu.useraction == 1) {
                MusicManager::Instance()->player.play();
                GameTime::Instance()->start();
            } else if (pauseMenu.useraction == 2) {
                restart(stage);

            } else if (pauseMenu.useraction == 3)
                finished = true;
            
            if (pauseMenu.useraction < 4) {
                pauseMenu.useraction = 0;
                pause = false;
                pauseMenu.active = pause;
                MusicManager::Instance()->gamePause = pause;
                player.lastShot = time;
                lastPressedBouton = time;
            } else if (pauseMenu.useraction == 4)
                WindowGame::Instance()->window.close();
        }
    }
    creditUpdate();
}

void Stage::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (stage != 5) {
        target.draw(background.background[0], states);
        target.draw(background.background[1], states);
        if (stage == 1) {
            for (unsigned char i = 0; i < 2; i++)
                target.draw(background.ecumes[i], states);
            target.draw(background.background[2], states);
            target.draw(background.background[4], states);
        }
    } else if (stage == 5) {
        for (unsigned char i = 0; i < 2; i++)
            target.draw(background.animation[i], states);
    }

    if (stage != 1)
        target.draw(background.background[3], states);

    // RedShape
    if (wave.boss.size() == 1)
        target.draw(wave.boss.back().redShape, states);

    // Tir du joueurs
    for (unsigned char i = 0; i < bullets.size(); i++)
        target.draw(bullets[i], states);

    // Tir ennemis
    for (unsigned char i = 0; i < bulletsEnemy.size(); i++)
        target.draw(bulletsEnemy[i], states);

    // PowerUp
    for (unsigned char i = 0; i < powerups.size(); i++) {
        target.draw(powerups[i], states);
    }

    target.draw(wave, states);

    // Le joueur
    target.draw(player, states);
    if (stage != 1)
        target.draw(background.background[2], states);
    else target.draw(background.background[3], states);

    // Explosions
    for (unsigned char i = 0; i < explosions.size(); i++) {
        target.draw(explosions[i], states);
    }

    // Indique le stage en cours
    if (startStage > time)
        target.draw(textStage, states);

    if (player.activeSuperAttack)
        target.draw(player.SuperAttack, states);

    target.draw(transition, states);

    if (player.lives <= 0 && player.credits <= 0)
        target.draw(textGameover, states);
    
    if (wave.finished) {
        target.draw(stateStage[0], states);
    }
    
    target.draw(pauseMenu, states);

#ifdef _DEBUG
    if (debug.active)
    target.draw(debug, states);
#endif

}

void Stage::setNewScore() {
    if (score < newscore)
        score += 10;
}

void Stage::saveScore() {
    char s = -1;
    for (unsigned char i = 13; i > 0; i--) {
        if (score > Highscore::Instance()->scoring[i].score) {
            s = i;
        }
    }
    if (s > -1) {
        Highscore::Instance()->scoring[s].playername = Profil::Instance()->playername;
        Highscore::Instance()->scoring[s].stage = "Stage " + to_string(stage);
        Highscore::Instance()->scoring[s].mode = gameDifficulty;
        Highscore::Instance()->scoring[s].score = score;
        Highscore::Instance()->scoring[s].enemydead = totalEnemyDead;
        Highscore::Instance()->save();
    }
}

void Stage::nextStage() {
    
    if (!activeNextStage) {
        MusicManager::Instance()->fadingOut = true;
        saveProfil();
        transition.initialize(1);
        activeNextStage = true;
    }
    
    if (Profil::Instance()->credits == 0 && stage == 1) {
        if (player.credits == 0)
        sound[4].play();
        player.credits = 1;
    }
    
    if (transition.finish) {
#if defined _RELEASE || defined _DEBUG
        if (stage != 5) {
            stage += 1;
            totalEnemyDead += enemyDead;
            enemyDead = 0;
            initialize(stage);
        } else {
            finished = true;
        }
#elif defined _BETA
        totalEnemyDead += enemyDead;
        if (stage == 4) {
        saveScore();
        finished = true;
        
        } else {
            stage += 1;
            enemyDead = 0;
            initialize(stage);
        }
#endif
    }
}

void Stage::restart(unsigned char stage) {
    score = lastScore;
    newscore = 0;
    player.lives = lastLives;
    player.countSuperAttack = lastSuperAttack;
    initialize(stage);
}

int Stage::getBonnus() {
    unsigned int bonnus = 0;

    if (enemyDead >= 51)
        bonnus += 1000;

    if (gameDifficulty == 2) {
        if (player.lostLives < 3 && player.lostLives > 0)
            bonnus += 2000;
        else if (player.lostLives == 0)
            bonnus += 3000;
    } else if (gameDifficulty == 1) {
        if (player.lostLives < 2 && player.lostLives > 0)
            bonnus += 2000;
        else if (player.lostLives == 0)
            bonnus += 3000;
    } else if (gameDifficulty == 0) {
        if (player.lostLives < 1 && player.lostLives > 0)
            bonnus += 3000;
        else if (player.lostLives == 0)
            bonnus += 4000;
    }
    
    if (enemyDead > 230)
        bonnus += 1000;

    return bonnus;
}

// Classe StateStage

Stage::StateStage::StateStage(unsigned char stage) {
    rectangle.setSize(Vector2f(480, 600));
    rectangle.setPosition(800, 0);
    rectangle.setFillColor(sf::Color(0, 0, 0, 155));
    finished = false;
    lastTime = 0;
    lastTime2 = 0;
    stateText.reserve(20);
    if (Language::Instance()->language != "english")
        language = Language::Instance()->french[9];
    else language = Language::Instance()->english[9];
    stateText.emplace_back(language[0] + " " + to_string(stage) + " " + language[1], 3000, Vector2f(180, 20));
    stateText[0].text.setScale(0.9, 0.9);

    if (font.loadFromFile(FileManager::Instance()->font)) {

        text.setFont(font);
        if (stage != 5)
            text.setString(language[12]);
        else text.setString(language[13]);
        text.setScale(0.4, 0.4);
        text.setPosition(340, 580);
        text.setColor(sf::Color(255, 255, 255, 0));
        countText = 0;

    }

    initialize = false;

}

void Stage::StateStage::update() {

    if (!initialize) {
        unsigned const char a = 40;
        unsigned const char b = 30;
        stateText.emplace_back(language[2], 5000, Vector2f(180, stateText[0].text.getPosition().y + a + 20));
        stateText.emplace_back(to_string(enemyDead), 6000, Vector2f(180, stateText[1].text.getPosition().y + b));
        stateText.emplace_back(language[3], 8000, Vector2f(180, stateText[2].text.getPosition().y + a));
        stateText.emplace_back(to_string(lostLives), 9000, Vector2f(180, stateText[3].text.getPosition().y + b));
        stateText.emplace_back(language[4], 13000, Vector2f(180, stateText[4].text.getPosition().y + a));
        stateText.emplace_back(to_string(bonnus), 14000, Vector2f(180, stateText[5].text.getPosition().y + b));
        stateText.emplace_back(language[5], 17000, Vector2f(180, stateText[6].text.getPosition().y + a));
        stateText.emplace_back(to_string(score), 18000, Vector2f(180, stateText[7].text.getPosition().y + b));
        stateText.emplace_back(language[6], 21000, Vector2f(180, stateText[8].text.getPosition().y + a));
        stateText.emplace_back(to_string(score + bonnus), 22000, Vector2f(180, stateText[9].text.getPosition().y + b));
        stateText.emplace_back(language[7], 25000, Vector2f(180, stateText[10].text.getPosition().y + a));
        if (bonnus > 5000)
            stateText.emplace_back(language[11], 26000, Vector2f(stateText[11].text.getPosition().y + b, 550));
        else if (bonnus > 3000)
            stateText.emplace_back(language[10], 26000, Vector2f(180, stateText[11].text.getPosition().y + b));
        else if (bonnus > 2000)
            stateText.emplace_back(language[9], 26000, Vector2f(180, stateText[11].text.getPosition().y + b));
        else stateText.emplace_back(language[8], 26000, Vector2f(180, stateText[11].text.getPosition().y + b));
        initialize = true;
    } else if (rectangle.getPosition().x > 165)
        rectangle.move(-3, 0);
    else {
        
        if (lastTime2 == 0)
            lastTime2 = GameTime::Instance()->getElapsedTime().asMilliseconds();
        else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime2 > 1000) {
            lastTime2 = GameTime::Instance()->getElapsedTime().asMilliseconds();
            countText += 1;
        }

        if (countText == 0)
            text.setColor(sf::Color(255, 255, 255, 0));
        else if (countText == 1)
            text.setColor(sf::Color(255, 255, 255, 255));
        else if (countText > 1)
            countText = 0;
    }

    for (unsigned char i = 0; i < stateText.size(); i++)
        stateText[i].update();

    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds() || 
             Keyboard::isKeyPressed(GamePadManager::Instance()->keys[3])) {
        stateText.clear();
        finished = true;
    }
}

void Stage::StateStage::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rectangle, states);
    for (unsigned char i = 0; i < stateText.size(); i++)
        target.draw(stateText[i], states);
    target.draw(text, states);

}

// Classe Text

Stage::StateText::StateText(string value, float startTime, Vector2f position) {
    trans = 0;
    lastTime = 0;
    if (font.loadFromFile(FileManager::Instance()->font)) {
        text.setString(value);
        text.setFont(font);
        text.setColor(sf::Color(255, 255, 255, trans));
        text.setScale(0.6, 0.6);
        text.setPosition(position);
        active = false;
    }

    this->startTime = startTime;
}

void Stage::StateText::update() {
    if (lastTime == 0)
        lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
    else if (!active) {

        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > startTime) {
            active = true;
            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();
        }
    } else if (active) {
        if (GameTime::Instance()->getElapsedTime().asMilliseconds() - lastTime > 50) {

            if (trans < 255) {
                trans += 15;
                text.setColor(sf::Color(255, 255, 255, trans));
            }

            lastTime = GameTime::Instance()->getElapsedTime().asMilliseconds();

        }
    }
}

void Stage::StateText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active)
        target.draw(text, states);
}

//Stage::Story::Story() {
    //finished = false;
    //sprites.reserve(3);
    //for (unsigned char i = 0; i < 3; i++) {
        //sprites[i].setTexture(FileManager::Instance()->artworks[i]);
        //sprites[i].setPosition(250,250);
        //sprites[i].setScale(1.2f,1.2f);
    //}
//}

Stage::DebugOption::DebugOption() {
    stage = 0;
    wave = 0;
    time = sf::seconds(0.2);
    restart = false;
    str.reserve(15);
    text.reserve(25);
    sprite.reserve(2);
    option.reserve(8);
    
    for (unsigned char i = 0; i < 25; i++) {
        if (i < 2)
            sprite.emplace_back();
        if (i < 8) {
            option.emplace_back();
            option[i] = 0;
        }

        if (i < 15);
        str.emplace_back();

        text.emplace_back();
    }

    // Définition des chaînes
    str[0] = "Stage";
    str[1] = "Wave";
    str[2] = "Test mode";
    str[3] = "Show ennemies rectangle";
    str[4] = "Show player rectangle";
    str[5] = "Show boss rectangle";
    str[6] = "Show bullets rectangle";
    str[7] = "God mode";
    str[8] = "Illimited special attack";
    str[9] = "Kill the boss";
    str[10] = "Restart stage";
    str[11] = "Restart game";
    str[12] = "Resume game";
    str[13] = "Actived";
    str[14] = "Desactived";

    // Attribution des textures
    sprite[0].setTexture(FileManager::Instance()->menu[5]); // Window
    sprite[1].setTexture(FileManager::Instance()->menu[3]); // Select
    sprite[0].setPosition(230, 100);

    Vector2f position = Vector2f(sprite[0].getPosition().x + 30, sprite[0].getPosition().y + 40);
    if (font.loadFromFile(FileManager::Instance()->font)) {
        for (unsigned char i = 0; i < 25; i++) {
            if (i < 13) {
                text[i].setString(str[i]);
            } else if (i > 17) {
                text[i].setString(str[14]);
            }

            if (i < 15) {
                position.y += 20;
                text[i].setPosition(position);
            }

            text[i].setFont(font);
            text[i].setColor(sf::Color::White);
            text[i].setScale(0.4, 0.4);
        }
    }
    sprite[1].setPosition(text[0].getPosition().x - 10, text[0].getPosition().y + 2);
}

void Stage::DebugOption::initialize() {
    active = false;
    lastTime = 0;
    keyAction = 0;
    move = 0;
    text[16].setString(to_string(stage));
    text[17].setString(to_string(wave));
    if (!restart) {
        unsigned char const positionX = 80;
        text[16].setPosition(text[0].getPosition().x + positionX, text[0].getPosition().y);
        text[17].setPosition(text[1].getPosition().x + positionX, text[1].getPosition().y);
        text[18].setPosition(text[2].getPosition().x + positionX + 10, text[2].getPosition().y);
        text[19].setPosition(text[3].getPosition().x + positionX + 120, text[3].getPosition().y);
        text[20].setPosition(text[4].getPosition().x + positionX + 120, text[4].getPosition().y);
        text[21].setPosition(text[5].getPosition().x + positionX + 100, text[5].getPosition().y);
        text[22].setPosition(text[6].getPosition().x + positionX + 120, text[6].getPosition().y);
        text[23].setPosition(text[7].getPosition().x + positionX, text[7].getPosition().y);
        text[24].setPosition(text[8].getPosition().x + positionX + 120, text[8].getPosition().y);
    }
    clock.restart();
}

void Stage::DebugOption::action(unsigned char count) {

    if (count == 1) {
        move += 1;
    } else if (count == 2) {
        move -= 1;
    } else if (count == 3) {
        if (move == 0) {
            stage += 1;
        } else if (move == 1) {
            wave += 1;
        } else if (move == 2) {
            option[0] = 1;
        } else if (move == 3)
            option[1] = 1;
        else if (move == 4)
            option[2] = 1;
        else if (move == 5)
            option[3] = 1;
        else if (move == 6)
            option[4] = 1;
        else if (move == 7)
            option[5] = 1;
        else if (move == 8)
            option[6] = 1;
    } else if (count == 4) {
        if (move == 0) {
            stage -= 1;
        } else if (move == 1) {
            wave -= 1;
        } else if (move == 2)
            option[0] = 0;
        else if (move == 3)
            option[1] = 0;
        else if (move == 4)
            option[2] = 0;
        else if (move == 5)
            option[3] = 0;
        else if (move == 6)
            option[4] = 0;
        else if (move == 7)
            option[5] = 0;
        else if (move == 8)
            option[6] = 0;
    } else if (count == 5) {
        option[7] = 1;
    } 
    
    else if (count == 13) {
        keyAction = 1;
    } else if (count == 14)
        keyAction = 2;
    else if (count == 15)
        keyAction = 3;

    if (count > 12 && count < 16)
        restart = true;

    lastTime = clock.getElapsedTime().asMilliseconds();

}

void Stage::DebugOption::control() {

    if (clock.getElapsedTime().asMilliseconds() - lastTime > time.asMilliseconds()) {
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            action(1);
        } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            action(2);
        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            action(3);
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            action(4);
        } else if (Keyboard::isKeyPressed(GamePadManager::Instance()->keys[0])) {
            if (move == 9)
                action(5);
            else if (move == 10)
                action(13);
            else if (move == 11)
                action(14);
            else if (move == 12) { // resume
                keyAction = 3;
                move = 0;
                lastTime = 0;
                restart = true;
            }
        }
    }
}

void Stage::DebugOption::update() {
    if (active) {
        control();
        // Gestion de la sélection

        if (move > 12)
            move = 12;
        else if (move < 0)
            move = 0;

        if (stage > 5)
            stage = 0;
        else if (stage < 1)
            stage = 5;

        if (wave > 5)
            wave = 0;
        else if (wave < 0)
            wave = 5;

        text[16].setString(to_string(stage));
        text[17].setString(to_string(wave));

        for (unsigned char i = 0; i < 15; i++) {
            sprite[1].setPosition(text[move].getPosition().x - 10, text[move].getPosition().y + 2);
        }

        if (option[0] == 1) // Test mode
            text[18].setString(str[13]);
        else text[18].setString(str[14]);

        if (option[1] == 1) // Rectangles des ennemis
            text[19].setString(str[13]);
        else text[19].setString(str[14]);

        if (option[2] == 1) // Rectangles du joueur
            text[20].setString(str[13]);
        else text[20].setString(str[14]);

        if (option[3] == 1) // Rectangle dy boss
            text[21].setString(str[13]);
        else text[21].setString(str[14]);

        if (option[4] == 1) // Rectangle des bullets
            text[22].setString(str[13]);
        else text[22].setString(str[14]);

        if (option[5] == 1) // Invincible
            text[23].setString(str[13]);
        else text[23].setString(str[14]);

        if (option[6] == 1) // Attaque illimité
            text[24].setString(str[13]);
        else text[24].setString(str[14]);
    }
}

void Stage::DebugOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (active) {
        for (unsigned char i = 0; i < text.size(); i++) {
            if (i < 2)
                target.draw(sprite[i], states);
            target.draw(text[i], states);
        }
    }
}