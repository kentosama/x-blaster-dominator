/* 
 * File:   Wave.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 23 mars 2013, 10:16
 */

#include "Wave.h"

Wave::Wave() {
    enemies.reserve(200);
    boss.reserve(1);
    currentWave = 1;
    gameDifficulty = Profil::Instance()->mode;

#ifdef _DEBUG
    if (currentWave == 0)
        test = true;
    else test = false;
#else
    test = false;
#endif

}

Wave::Wave(const Wave& orig) {
}

Wave::~Wave() {
}

void Wave::initialize(unsigned char const stage, unsigned char startWave) {

#if defined _DEBUG
    if (startWave == 1)
        gameDifficulty = Profil::Instance()->mode;
#else
    if (stage == 1 && startWave == 1)
        gameDifficulty = Profil::Instance()->mode;
#endif

    int position = 0;
    int position2 = 500;
    unsigned char mode = 0;
    if (finished)
        finished = false;

    this->stage = stage;

    if (!test)
        currentWave = startWave;
    if (enemies.size() > 0)
        enemies.clear();


    if (boss.size() > 0)
        boss.clear();

    if (stage == 1) {
        if (currentWave == 0) // Réservé aux tests
        {
            enemies.emplace_back(Vector2f(230, -30), 5, 0, true, 50, 10000000, 0, true, false);


        } else if (currentWave == 1) {
            if (gameDifficulty == 2) {
                enemies.emplace_back(Vector2f(-100, 300), 0, 0, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 300), 0, 0, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(150, -50), 0, 5000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(300, -50), 0, 5000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 6000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 6000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(250, -50), 0, 9000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(250, -300), 0, 9000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(150, -50), 3, 13000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 3, 13000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 16000, true, 100, 2000, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 16000, true, 200, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(150, -50), 0, 16000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 16000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 3, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 3, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(150, -50), 0, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 26000, true, 100, 4000, 1, true, true);

                enemies.emplace_back(Vector2f(100, -50), 3, 32000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 3, 32000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 3, 32000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(250, -50), 3, 37000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(250, -300), 3, 37000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 1, 42000, true, 100, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(111, -50), 1, 42000, true, 150, 4000, 2, true, false);
                enemies.emplace_back(Vector2f(222, -50), 1, 42000, true, 200, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(333, -50), 1, 42000, true, 250, 2000, 2, true, false);
                enemies.emplace_back(Vector2f(444, -50), 1, 42000, true, 300, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(0, -50), 1, 47000, true, 100, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(111, -50), 1, 47000, true, 150, 4000, 2, true, false);
                enemies.emplace_back(Vector2f(222, -50), 1, 47000, true, 200, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(333, -50), 1, 47000, true, 250, 2000, 2, true, false);
                enemies.emplace_back(Vector2f(444, -50), 1, 47000, true, 300, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(250, -50), 3, 50000, true, 200, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(250, -300), 3, 50000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(0, -400), 3, 50000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(445, -400), 3, 50000, true, 100, 3000, 1, true, false);

                enemies.emplace_back(Vector2f(0, -50), 2, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -400), 2, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -800), 2, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -1000), 2, 55000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(220, -100), 3, 60000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -50), 2, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -400), 2, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -800), 2, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -1000), 2, 65000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(150, -50), 7, 69000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 7, 69000, false, 0, 0, 0, true, false);

            } else if (gameDifficulty < 2) { // Normal et difficile
                enemies.emplace_back(Vector2f(0, -50), 0, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -150), 0, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -50), 0, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -150), 0, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 3000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 3000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 3, 6000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -150), 3, 8000, true, 50, 1000, 1, true, true);
                enemies.emplace_back(Vector2f(230, -250), 3, 10000, true, 100, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 0, 14000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 16000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 18000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 20000, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 22000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 24000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 15000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 3, 27000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 27000, true, 100, 1000, 1, true, true);
                enemies.emplace_back(Vector2f(230, -50), 3, 27000, true, 150, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 32000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 32000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 0, 32000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 34000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(130, -50), 0, 36000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(130, -50), 0, 38000, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(330, -50), 0, 40000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(330, -50), 0, 42000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 38000, true, 150, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 38000, true, 150, 5000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 4, 44000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 1, 46000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -50), 1, 46000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(443, -50), 1, 46000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(343, -50), 1, 46000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 8, 50000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -50), 8, 50000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -150), 4, 50000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(230, -200), 8, 50000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 8, 60000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -50), 8, 60000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 60000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -150), 5, 60000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -200), 8, 60000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 8, 68000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 68000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(30, -50), 8, 68000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -50), 8, 68000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(430, -50), 8, 68000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 74000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 74000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 74000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 74000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 74000, true, 250, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 74000, true, 250, 5000, 0, true, false);
            }

        } else if (currentWave == 2) {

            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(150, -50), 2, 0, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 0, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 5000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 5000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 3, 10000, true, 50, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(350, -200), 3, 10000, true, 50, 3000, 1, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 15000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 15000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 18000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 18000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 22000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 22000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -200), 7, 22000, false, 0, 0, 0, true, true);


                enemies.emplace_back(Vector2f(0, -50), 0, 25000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -100), 0, 25000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -50), 0, 28000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -100), 0, 28000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(220, -50), 7, 33000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(120, -50), 7, 33000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(320, -200), 7, 33000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -100), 0, 35000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -50), 0, 38000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -100), 0, 38000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(220, -50), 3, 42000, true, 50, 5000, 2, true, false);
                enemies.emplace_back(Vector2f(120, -50), 3, 42000, true, 100, 5000, 1, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 45000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 0), 0, 45000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, -0), 0, 45000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 0), 0, 47000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 0), 0, 47000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 0), 0, 47000, false, 0, 0, 7, false, false);

                enemies.emplace_back(Vector2f(-100, 200), 0, 49000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 200), 0, 49000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 300), 0, 49000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 200), 0, 52000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 200), 0, 52000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 300), 0, 52000, false, 0, 0, 7, false, false);

                enemies.emplace_back(Vector2f(-100, 200), 0, 54000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(-300, 200), 0, 54000, false, 0, 0, 8, false, false);

                enemies.emplace_back(Vector2f(600, 300), 0, 56000, false, 0, 0, 9, false, false);
                enemies.emplace_back(Vector2f(700, 300), 0, 56000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(-100, 400), 0, 58000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 400), 0, 58000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(-100, 300), 0, 60000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 300), 0, 60000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(220, -50), 7, 62000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(120, -50), 7, 62000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(320, -50), 7, 62000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 600), 0, 63000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 500), 0, 63000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(-100, 300), 0, 64000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 300), 0, 64000, false, 0, 0, 9, false, false);

            } else if (gameDifficulty < 2) {
                enemies.emplace_back(Vector2f(-100, 0), 0, 300, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 300, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 1300, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 1300, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 1000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 2300, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 2300, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 2000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 3300, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 3300, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 3000, false, 0, 0, 0, true, false);

                for (unsigned char i = 0; i < 5; i++) {
                    position -= 100;
                    position2 += 100;
                    enemies.emplace_back(Vector2f(position, 540), 0, 3000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 500), 0, 3000, false, 0, 0, 9, false, false);
                }

                enemies.emplace_back(Vector2f(150, -50), 3, 6000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 3, 6000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(150, -50), 3, 12000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 3, 12000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 15000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 15000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 15000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 15000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 15000, true, 350, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 15000, true, 350, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 20000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 20000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 19000, false, 0, 0, 0, true, true);

                enemies.emplace_back(Vector2f(-100, 0), 0, 22000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 22000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 21000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 24000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 24000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 23000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 24000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 24000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 25000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(430, -50), 8, 30000, true, 50, 300, 2, true, false);
                enemies.emplace_back(Vector2f(0, -50), 8, 31000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 32000, true, 50, 300, 2, true, false);

                enemies.emplace_back(Vector2f(430, -50), 8, 35000, true, 50, 300, 2, true, false);
                enemies.emplace_back(Vector2f(0, -50), 8, 36000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 37000, true, 50, 300, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 150, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 250, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, 300, 100, 1, true, false);

                enemies.emplace_back(Vector2f(130, -50), 4, 46000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(330, -50), 4, 46000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 5, 48000, true, 50, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(150, -50), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 52000, true, 100, 4000, 1, true, false);

                enemies.emplace_back(Vector2f(150, -50), 1, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 1, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 1, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 1, 55000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(150, -350), 1, 55000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 1, 55000, true, 100, 4000, 1, true, false);

                enemies.emplace_back(Vector2f(100, -50), 3, 60000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(200, -50), 3, 60000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 3, 60000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 3, 60000, true, 100, 5000, 0, true, false);


                enemies.emplace_back(Vector2f(230, -50), 0, 65000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 65000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 64000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 67000, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 67000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 66000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 4, 70000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 70000, true, 100, 1000, 1, true, true);
                enemies.emplace_back(Vector2f(230, -50), 4, 70000, true, 150, 1000, 2, true, false);
            }
        } else if (currentWave == 3) {

            if (gameDifficulty == 2) {
                // Attaque en mouvement rapide
                enemies.emplace_back(Vector2f(150, -50), 2, 0, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 0, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 2000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 2000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 2, 4000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 4000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 1, 6000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 1, 6000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 2, 9000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 9000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 0, 11000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 11000, true, 200, 200, 2, true, false);

                // Attaque normale

                enemies.emplace_back(Vector2f(50, -200), 8, 16000, true, 100, 300, 2, true, false);
                enemies.emplace_back(Vector2f(250, -50), 8, 16000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(400, -200), 8, 16000, true, 100, 300, 1, true, false);

                enemies.emplace_back(Vector2f(150, -50), 4, 22000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 4, 22000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 500), 0, 30000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 400), 0, 30000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(-100, 300), 0, 32000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 200), 0, 32000, false, 0, 0, 9, false, false);


                enemies.emplace_back(Vector2f(-100, 100), 0, 36000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 150), 0, 37000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 200), 0, 38000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 100), 0, 36000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 150), 0, 37000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 200), 0, 38000, false, 0, 0, 7, false, false);

                // Petit groupement avec tourelle

                enemies.emplace_back(Vector2f(50, -50), 7, 42000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 7, 42000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 47000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(150, -200), 8, 47000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 8, 47000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -400), 8, 47000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(350, -400), 8, 47000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 7, 52000, true, 50, 5000, 0, true, false);

                // Nouvelle phase

                enemies.emplace_back(Vector2f(50, -50), 0, 57000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(50, -100), 0, 57000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(50, -150), 0, 57000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(50, -200), 0, 57000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(50, -250), 0, 57000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(50, -300), 0, 57000, true, 300, 200, 2, true, false);

                enemies.emplace_back(Vector2f(400, -50), 0, 59000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(400, -100), 0, 59000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(400, -150), 0, 59000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(400, -200), 0, 59000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(400, -250), 0, 59000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(400, -300), 0, 59000, true, 300, 200, 1, true, false);

                enemies.emplace_back(Vector2f(230, -50), 7, 58000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 0, 65000, true, 200, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 65000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -150), 0, 65000, true, 200, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -200), 0, 65000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -250), 0, 65000, true, 200, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -300), 0, 65000, true, 300, 200, 1, true, false);

                enemies.emplace_back(Vector2f(230, -300), 5, 70000, true, 100, 6000, 0, true, false);
            } else if (gameDifficulty < 2) {
                enemies.emplace_back(Vector2f(150, -50), 2, 0, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 0, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(50, -50), 2, 1000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(50, -100), 2, 100, true, 100, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 2000, true, 150, 100, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 2000, true, 150, 100, 2, true, false);

                enemies.emplace_back(Vector2f(350, -50), 2, 3000, true, 250, 100, 1, true, false);
                enemies.emplace_back(Vector2f(350, -100), 2, 3000, true, 250, 100, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 2, 4000, true, 350, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 4000, true, 350, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 5000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 5000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 1, 6000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 6000, true, 100, 100, 2, true, false);

                enemies.emplace_back(Vector2f(50, -50), 1, 7000, true, 150, 100, 1, true, false);
                enemies.emplace_back(Vector2f(50, -100), 2, 7000, true, 150, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 1, 8000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 8000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(350, -50), 1, 9000, true, 250, 100, 1, true, false);
                enemies.emplace_back(Vector2f(350, -100), 2, 9000, true, 250, 100, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 1, 10000, true, 300, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 10000, true, 300, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 1, 11000, true, 350, 100, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 11000, true, 350, 100, 2, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 17000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 17000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 16000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 19000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 19000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 18000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 21000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 21000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 23000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 23000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 22000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(50, -50), 8, 26000, true, 50, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -300), 8, 26000, true, 50, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -500), 8, 26000, true, 100, 5000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -700), 8, 26000, true, 150, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -900), 8, 26000, true, 200, 5000, 2, true, false);

                enemies.emplace_back(Vector2f(50, -50), 8, 36000, true, 50, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -300), 8, 36000, true, 50, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -500), 7, 36000, true, 100, 5000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -700), 7, 36000, true, 150, 5000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -900), 7, 36000, true, 200, 5000, 2, true, false);


                enemies.emplace_back(Vector2f(-100, 0), 0, 44000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 44000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 43000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 45000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 45000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 44000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 46000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 46000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 45000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 0), 0, 48000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(560, 0), 0, 48000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 47000, false, 0, 0, 0, true, false);

                if (Profil::Instance()->credits > 0) {
                    enemies.emplace_back(Vector2f(180, -50), 14, 52000, true, 150, 10000, 0, true, false);
                    enemies.emplace_back(Vector2f(270, -50), 14, 52000, true, 150, 10000, 0, true, false);
                } else enemies.emplace_back(Vector2f(230, -50), 14, 52000, true, 150, 10000, 0, true, true);

                enemies.emplace_back(Vector2f(50, -50), 7, 58000, true, 50, 10000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 58000, true, 50, 10000, 0, true, false);

                enemies.emplace_back(Vector2f(180, -50), 5, 62000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(270, -50), 5, 62000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(180, -50), 7, 67000, true, 250, 10000, 0, true, false);
                enemies.emplace_back(Vector2f(270, -50), 7, 67000, true, 250, 10000, 0, true, false);

                for (unsigned char i = 0; i < 10; i++) {
                    position -= 100;
                    position2 += 100;
                    enemies.emplace_back(Vector2f(position, 50), 0, 67000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 400), 0, 67000, false, 0, 0, 9, false, false);
                }

                enemies.emplace_back(Vector2f(180, -50), 8, 70000, true, 250, 10000, 0, true, false);
                enemies.emplace_back(Vector2f(270, -50), 8, 70000, true, 250, 10000, 0, true, false);

            }
        } else if (currentWave == 4) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(160, -300), 5, 0, true, 100, 6000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -300), 5, 0, true, 100, 6000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 1, 12000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 1, 12000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 1, 14000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 1, 17000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 1, 17000, true, 300, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 1, 19000, true, 300, 200, 1, true, false);

                enemies.emplace_back(Vector2f(50, -50), 8, 25000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 8, 25000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(50, -50), 7, 28000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(400, -50), 7, 28000, false, 0, 0, 0, true, true);

                enemies.emplace_back(Vector2f(150, -50), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 30000, true, 100, 4000, 1, true, false);

                if (Profil::Instance()->credits > 0) {
                    enemies.emplace_back(Vector2f(180, -50), 14, 40000, true, 150, 10000, 0, true, false);
                    enemies.emplace_back(Vector2f(270, -50), 14, 40000, true, 150, 10000, 0, true, false);
                } else enemies.emplace_back(Vector2f(230, -50), 14, 40000, true, 150, 10000, 0, true, true);

                enemies.emplace_back(Vector2f(160, -300), 4, 45000, true, 100, 6000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -300), 4, 45000, true, 100, 6000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 48000, true, 300, 300, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 48000, true, 200, 300, 1, true, false);

                if (Profil::Instance()->credits > 0) {
                    enemies.emplace_back(Vector2f(230, -50), 7, 55000, false, 0, 0, 0, true, true);
                }

                enemies.emplace_back(Vector2f(50, -50), 7, 52000, true, 300, 300, 2, true, false);
                enemies.emplace_back(Vector2f(400, -50), 7, 52000, true, 200, 300, 1, true, false);

                for (unsigned char i = 0; i < 5; i++) {
                    position -= 100;
                    enemies.emplace_back(Vector2f(position, 440), 0, 57000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position, 240), 0, 60000, false, 0, 0, 8, false, false);

                    position2 += 100;
                    enemies.emplace_back(Vector2f(position2, 540), 0, 57000, false, 0, 0, 9, false, false);
                    enemies.emplace_back(Vector2f(position2, 340), 0, 60000, false, 0, 0, 9, false, false);

                }

                enemies.emplace_back(Vector2f(230, -50), 10, 65000, true, 50, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(190, -50), 8, 70000, true, 300, 300, 2, true, false);
                enemies.emplace_back(Vector2f(270, -50), 8, 70000, true, 300, 300, 1, true, false);

                enemies.emplace_back(Vector2f(190, -50), 7, 75000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(270, -50), 7, 75000, false, 0, 0, 0, true, false);

                // Attaque en mouvement rapide
                enemies.emplace_back(Vector2f(150, -50), 2, 82000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 82000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 2, 83000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 2, 83000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 2, 85000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 85000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 1, 87000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(250, -100), 1, 87000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(150, -50), 2, 8900, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -100), 2, 89000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(250, -50), 0, 91000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 91000, true, 200, 200, 2, true, false);

            } else if (gameDifficulty < 2) {

                enemies.emplace_back(Vector2f(160, -50), 10, 0, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 0, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 2, 5000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 2, 5000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 2, 6000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 2, 6000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 7000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 1, 8000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 8000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 1, 8000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 8, 10000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 10000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 8, 12000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 12000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 16000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -300), 8, 16000, true, 50, 100, 2, true, false);

                for (unsigned char i = 0; i < 10; i++) {
                    position -= 100;
                    position2 += 100;
                    enemies.emplace_back(Vector2f(position, 500), 0, 20000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 540), 0, 20000, false, 0, 0, 9, false, false);
                }

                enemies.emplace_back(Vector2f(160, -50), 10, 22000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 7, 25000, true, 50, 1000, 0, true, true);
                enemies.emplace_back(Vector2f(290, -50), 10, 22000, true, 50, 1000, 0, true, false);

                position = 0;
                position2 = 500;

                for (unsigned char i = 0; i < 10; i++) {
                    position -= 100;
                    position2 += 100;
                    enemies.emplace_back(Vector2f(position, 500), 0, 35000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 540), 0, 35000, false, 0, 0, 9, false, false);
                }

                position = 0;
                for (unsigned char i = 0; i < 5; i++) {
                    enemies.emplace_back(Vector2f(160, position), 0, 45000, true, 50, 100, mode, true, false);
                    enemies.emplace_back(Vector2f(290, position), 0, 45000, true, 50, 100, mode, true, false);
                    if (mode < 2)
                        mode += 1;
                    else mode = 0;
                    position -= 100;
                }

                enemies.emplace_back(Vector2f(230, -150), 7, 48000, true, 50, 5000, 0, true, false);

                position = 0;
                for (unsigned char i = 0; i < 5; i++) {
                    enemies.emplace_back(Vector2f(160, position), 0, 52000, true, 50, 100, mode, true, false);
                    enemies.emplace_back(Vector2f(290, position), 0, 52000, true, 50, 100, mode, true, false);
                    if (mode < 2)
                        mode += 1;
                    else mode = 0;
                    position -= 100;
                }

                enemies.emplace_back(Vector2f(230, -150), 5, 54000, true, 50, 5000, 0, true, true);

                if (Profil::Instance()->credits > 0) {
                    enemies.emplace_back(Vector2f(180, -50), 14, 60000, true, 150, 10000, 0, true, false);
                    enemies.emplace_back(Vector2f(270, -50), 14, 60000, true, 150, 10000, 0, true, false);
                } else enemies.emplace_back(Vector2f(230, -50), 14, 60000, true, 150, 10000, 0, true, false);


                enemies.emplace_back(Vector2f(150, -50), 0, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 65000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 65000, true, 100, 4000, 1, true, true);

            }
        } else if (currentWave == 5) {
            boss.emplace_back(stage, Vector2f(250, -500), 4000);
        }
    } else if (stage == 2) {
        if (currentWave == 1) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(160, -50), 0, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 0, 1000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 1000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 0, 2000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 2000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 1, 8000, true, 50, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 1, 8000, true, 50, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 1, 10000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 1, 10000, true, 100, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 1, 12000, true, 150, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 1, 12000, true, 150, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 1, 14000, true, 50, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 1, 14000, true, 50, 500, 2, true, false);


                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 18000, true, 200, 1000, 2, true, true);

                enemies.emplace_back(Vector2f(0, -50), 3, 28000, true, 50, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 3, 28000, true, 50, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 7, 28000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 3, 35000, true, 50, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 3, 35000, true, 50, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 7, 35000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 7, 40000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 200, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 45000, true, 100, 1000, 2, true, true);

                enemies.emplace_back(Vector2f(160, -50), 0, 50000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 50000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 0, 52000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 52000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 0, 54000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(385, -100), 0, 54000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 2, 56000, true, 50, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 2, 56000, true, 50, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 2, 58000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 2, 58000, true, 100, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 2, 60000, true, 150, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 2, 60000, true, 150, 500, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 2, 62000, true, 50, 500, 1, true, false);
                enemies.emplace_back(Vector2f(385, -100), 2, 62000, true, 50, 500, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 14, 65000, true, 100, 2000, 1, true, false);

                enemies.emplace_back(Vector2f(160, -50), 14, 68000, true, 100, 2000, 1, true, true);
                enemies.emplace_back(Vector2f(385, -50), 14, 68000, true, 100, 2000, 2, true, false);

            } else if (gameDifficulty < 2) {

                enemies.emplace_back(Vector2f(0, -50), 10, 0, true, 50, 3000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 10, 0, true, 50, 3000, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 9, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(160, -100), 9, 10000, false, 0, 0, 0, false, false);
                enemies.emplace_back(Vector2f(290, -50), 9, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(290, -100), 9, 10000, false, 0, 0, 0, false, false);

                enemies.emplace_back(Vector2f(230, -50), 10, 15000, true, 50, 3000, 0, true, true);

                enemies.emplace_back(Vector2f(160, -50), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(160, -50), 9, 20000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(290, -50), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 9, 20000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 5, 25000, true, 50, 1000, 0, true, true);

                enemies.emplace_back(Vector2f(160, -50), 8, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(160, -50), 8, 30000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(290, -50), 8, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 8, 30000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 36000, true, 250, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 36000, true, 200, 200, 1, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 36000, true, 100, 400, 1, true, false);

                enemies.emplace_back(Vector2f(445, -50), 7, 36000, true, 250, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 36000, true, 200, 200, 2, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 36000, true, 100, 400, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 46000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(290, -50), 10, 46000, false, 0, 0, 0, true, true);

                enemies.emplace_back(Vector2f(220, -50), 14, 54000, true, 250, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 54000, true, 250, 200, 2, true, true);

                enemies.emplace_back(Vector2f(0, -50), 7, 58000, true, 100, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 58000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 58000, true, 100, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(445, -50), 7, 68000, true, 100, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 68000, true, 100, 500, 2, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 68000, true, 100, 1000, 2, true, false);
            }
        } else if (currentWave == 2) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(230, -50), 10, 0, true, 50, 3000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 1000, true, 200, 2000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 1000, true, 200, 2000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 4000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(150, -50), 0, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 10000, true, 100, 4000, 1, true, false);

                enemies.emplace_back(Vector2f(150, -50), 0, 12000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(300, -50), 0, 12000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -200), 0, 12000, true, 100, 100, 2, true, false);
                enemies.emplace_back(Vector2f(300, -200), 0, 12000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(150, -350), 0, 12000, true, 200, 100, 2, true, false);
                enemies.emplace_back(Vector2f(300, -350), 0, 12000, true, 100, 100, 1, true, false);

                enemies.emplace_back(Vector2f(150, -50), 1, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -50), 2, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -200), 1, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -200), 2, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(150, -350), 1, 14000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(300, -350), 2, 14000, true, 100, 4000, 1, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 20000, true, 100, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 20000, true, 100, 500, 1, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 20000, true, 100, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(445, -50), 7, 26000, true, 100, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 26000, true, 100, 500, 2, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 26000, true, 100, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 4, 30000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 4, 30000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 4, 30000, true, 100, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(0, -50), 5, 40000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 5, 40000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 50000, true, 200, 1000, 2, true, true);

                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 57000, true, 200, 1000, 2, true, true);

                enemies.emplace_back(Vector2f(-100, 0), 0, 63000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 0), 0, 63000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, -0), 0, 63000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 0), 0, 63000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 0), 0, 63000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 0), 0, 63000, false, 0, 0, 7, false, false);

            } else if (gameDifficulty < 2) {
                enemies.emplace_back(Vector2f(-160, 250), 0, 0, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-260, 250), 0, 0, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-360, 250), 0, 0, false, 0, 0, 10, false, false);

                enemies.emplace_back(Vector2f(640, 250), 0, 0, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(740, 250), 0, 0, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(840, 250), 0, 0, false, 0, 0, 11, false, false);


                enemies.emplace_back(Vector2f(-160, 50), 1, 5000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-260, 50), 1, 5000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-360, 50), 1, 5000, false, 0, 0, 10, false, false);

                enemies.emplace_back(Vector2f(640, 50), 1, 5000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(740, 50), 1, 5000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(840, 50), 1, 5000, false, 0, 0, 11, false, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 10000, true, 200, 1000, 2, true, true);

                enemies.emplace_back(Vector2f(-100, 0), 0, 20000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 0), 0, 20000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 0), 0, 20000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 0), 0, 20000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 0), 0, 20000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 0), 0, 20000, false, 0, 0, 7, false, false);

                enemies.emplace_back(Vector2f(-100, 200), 0, 22000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 200), 0, 22000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 300), 0, 22000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 200), 0, 22000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 200), 0, 22000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 300), 0, 22000, false, 0, 0, 7, false, false);

                enemies.emplace_back(Vector2f(-160, 100), 3, 29000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-260, 100), 3, 29000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-360, 100), 3, 29000, false, 0, 0, 10, false, true);

                enemies.emplace_back(Vector2f(640, 100), 3, 29000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(740, 100), 3, 29000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(840, 100), 3, 29000, false, 0, 0, 11, false, true);

                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 36000, true, 200, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 3, 44000, true, 200, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(160, -150), 5, 50000, true, 200, 6000, 0, true, true);
                enemies.emplace_back(Vector2f(290, -150), 5, 50000, true, 200, 6000, 0, true, true);

                enemies.emplace_back(Vector2f(-160, 250), 0, 60000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-260, 250), 0, 60000, false, 0, 0, 10, false, false);
                enemies.emplace_back(Vector2f(-360, 250), 0, 60000, false, 0, 0, 10, false, false);

                enemies.emplace_back(Vector2f(640, 250), 0, 60000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(740, 250), 0, 60000, false, 0, 0, 11, false, false);
                enemies.emplace_back(Vector2f(840, 250), 0, 60000, false, 0, 0, 11, false, false);

                enemies.emplace_back(Vector2f(-160, 530), 0, 63000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(-260, 530), 0, 63000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(-360, 530), 0, 63000, false, 0, 0, 8, false, false);

                enemies.emplace_back(Vector2f(640, 430), 0, 63000, false, 0, 0, 9, false, false);
                enemies.emplace_back(Vector2f(740, 430), 0, 63000, false, 0, 0, 9, false, false);
                enemies.emplace_back(Vector2f(840, 430), 0, 63000, false, 0, 0, 9, false, false);

            }
        } else if (currentWave == 3) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(-100, 100), 0, 0, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 100), 0, 0, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 100), 0, 0, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 100), 0, 0, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 100), 0, 0, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 100), 0, 0, false, 0, 0, 7, false, false);

                enemies.emplace_back(Vector2f(130, -50), 9, 3000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(330, -50), 9, 3000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(230, -50), 9, 5000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 9, 10000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(330, -50), 9, 10000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(230, -50), 9, 15000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(130, -100), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(130, -150), 9, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(130, -200), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(130, -250), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(130, -350), 9, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(330, -50), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -100), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -150), 9, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(330, -200), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -250), 9, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -300), 9, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(-100, 100), 0, 28000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-200, 100), 0, 28000, false, 0, 0, 6, false, false);
                enemies.emplace_back(Vector2f(-300, 100), 0, 28000, false, 0, 0, 6, false, false);

                enemies.emplace_back(Vector2f(600, 100), 0, 28000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(700, 100), 0, 28000, false, 0, 0, 7, false, false);
                enemies.emplace_back(Vector2f(800, 100), 0, 28000, false, 0, 0, 7, false, false);

                for (unsigned char i = 0; i < 10; i++) {
                    position -= 100;
                    position2 += 100;
                    enemies.emplace_back(Vector2f(position, 500), 0, 30000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 540), 0, 30000, false, 0, 0, 9, false, false);
                }

                enemies.emplace_back(Vector2f(0, -50), 7, 35000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 35000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 35000, true, 150, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -50), 7, 35000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 35000, true, 350, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 35000, true, 350, 5000, 0, true, true);


                enemies.emplace_back(Vector2f(-100, 250), 0, 40000, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(600, 250), 0, 40000, false, 0, 0, 9, false, false);

                enemies.emplace_back(Vector2f(260, -50), 8, 40000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(260, -50), 8, 40000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(260, -50), 8, 40000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 44000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 44000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 48000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 48000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 9, 49000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 9, 49000, false, 0, 0, 0, true, false);

            } else if (gameDifficulty < 2) {
                enemies.emplace_back(Vector2f(20, -50), 14, 0, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 5000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(400, -50), 14, 10000, true, 100, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(20, -50), 14, 15000, true, 200, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 14, 25000, true, 200, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(20, -50), 14, 25000, false, 0, 0, 0, true, false);

                position = -100;
                position2 = 640;
                unsigned char count = 0;
                for (unsigned char i = 0; i < 5; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 50), 1, 29000, false, 0, 0, 10, false, true);
                        enemies.emplace_back(Vector2f(position2, 50), 1, 29000, false, 0, 0, 11, false, true);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 50), 1, 29000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 50), 1, 29000, false, 0, 0, 11, false, false);
                        count = 0;
                    }
                    position -= 100;
                    position2 += 100;
                }

                enemies.emplace_back(Vector2f(20, -50), 14, 36000, true, 200, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 36000, true, 200, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(400, -50), 14, 36000, true, 200, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 9, 43000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(160, -50), 9, 44000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 9, 45000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 9, 46000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 5, 50000, true, 50, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(230, -50), 5, 56000, true, 50, 5000, 0, true, true);

            }
        } else if (currentWave == 4) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(230, -50), 0, 0, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 0, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -150), 0, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -200), 0, 0, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -250), 0, 0, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -300), 0, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 150, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 250, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 15000, true, 300, 100, 1, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 23000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 23000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 9, 28000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(330, -50), 9, 28000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 28000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(130, -50), 9, 32000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(330, -50), 9, 32000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 35000, true, 50, 1000, 1, true, false);

                enemies.emplace_back(Vector2f(220, -50), 14, 38000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(120, -50), 14, 40000, true, 100, 3000, 0, true, false);

                enemies.emplace_back(Vector2f(320, -50), 14, 40000, true, 100, 3000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 0, 49000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -100), 0, 49000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -150), 0, 49000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -200), 0, 49000, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -250), 0, 49000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -300), 0, 49000, false, 0, 0, 0, true, false);

            } else if (gameDifficulty < 2) {

                position = -160;
                position2 = 600;
                for (unsigned char i = 0; i < 10; i++) {
                    enemies.emplace_back(Vector2f(position, -50), 0, 0, false, 0, 0, 6, false, false);
                    enemies.emplace_back(Vector2f(position2, -50), 0, 0, false, 0, 0, 7, false, false);
                    position -= 100;
                    position2 += 100;
                }

                enemies.emplace_back(Vector2f(0, -50), 7, 5000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 7, 7000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 9000, true, 50, 5000, 0, true, false);

                position = -160;
                position2 = 600;
                for (unsigned char i = 0; i < 10; i++) {
                    enemies.emplace_back(Vector2f(position, 500), 0, 12000, false, 0, 0, 8, false, false);
                    enemies.emplace_back(Vector2f(position2, 500), 0, 12000, false, 0, 0, 9, false, false);
                    position -= 100;
                    position2 += 100;
                }

                enemies.emplace_back(Vector2f(0, -50), 9, 16000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 9, 16000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 9, 20000, true, 50, 1000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -50), 9, 20000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 5, 24000, true, 300, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 4, 24000, true, 300, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 4, 24000, true, 300, 200, 2, true, false);

                position = -100;
                position2 = 640;
                unsigned char count = 0;
                for (unsigned char i = 0; i < 20; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 300), 0, 30000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 300), 0, 30000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 200), 1, 30000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 200), 1, 30000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 2) {
                        enemies.emplace_back(Vector2f(position, 100), 2, 30000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 100), 2, 30000, false, 0, 0, 11, false, false);
                        count = 0;
                    }
                    position -= 100;
                    position2 += 100;
                }

                count = 2;
                position = 50;
                for (unsigned char i = 0; i < 6; i++) {
                    enemies.emplace_back(Vector2f(230, -50), 8, 42000, true, position, 100, count, true, false);
                    if (count == 2)
                        count = 1;
                    else count += 1;
                    position += 50;
                }
            }
        } else if (currentWave == 5) {
            boss.emplace_back(stage, Vector2f(245, -500), 4000);
        }
    } else if (stage == 3) {
        if (currentWave == 1) {
            if (gameDifficulty == 2) {

                enemies.emplace_back(Vector2f(680, 540), 12, 0, true, 610, 10000, 9, true, false);

                enemies.emplace_back(Vector2f(-160, 540), 12, 0, true, 30, 10000, 8, true, false);

                position = -100;
                position2 = 640;
                unsigned char count = 0;
                for (unsigned char i = 0; i < 20; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 350), 0, 0, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 350), 0, 0, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 200), 1, 10000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 200), 1, 10000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 2) {
                        enemies.emplace_back(Vector2f(position, 50), 2, 15000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 50), 2, 15000, false, 0, 0, 11, false, false);
                        count = 0;
                    }

                    position -= 100;
                    position2 += 100;
                }

                enemies.emplace_back(Vector2f(680, 540), 12, 20000, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 540), 12, 20000, true, 30, 10000, 8, true, false);
                enemies.emplace_back(Vector2f(680, 450), 12, 25000, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 450), 12, 25000, true, 30, 10000, 8, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 28000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 28000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 10, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(290, -50), 10, 35000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 150, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 250, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 44000, true, 300, 100, 1, true, false);

                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 100, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 150, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 250, 100, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 50000, true, 300, 100, 1, true, false);

                enemies.emplace_back(Vector2f(220, -50), 14, 64000, true, 250, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(220, -50), 14, 64000, true, 250, 200, 2, true, true);

            } else if (gameDifficulty < 2) {

                position = 0;
                int time = 0;
                unsigned char mode = 1;

                for (unsigned char i = 0; i < 30; i++) {
                    time += 800;
                    enemies.emplace_back(Vector2f(position, -30), 11, time, true, 50, 250, mode, true, false);
                    if (position < 445)
                        position += 50;
                    else position = 160;

                    if (mode == 1)
                        mode = 2;
                    else mode = 1;
                }

                enemies.emplace_back(Vector2f(230, -30), 9, 29000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -30), 9, 30000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -30), 9, 30000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -30), 9, 32000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -30), 9, 32000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(0, -30), 7, 34000, true, 50, 2000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -30), 7, 34000, true, 50, 2000, 0, true, true);

                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 38000, true, 200, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 100, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 200, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 100, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 2, 46000, true, 200, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -30), 9, 53000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -30), 9, 52000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -30), 9, 53000, true, 50, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -30), 9, 55000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -30), 9, 55000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(100, -30), 5, 58000, true, 50, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(345, -30), 5, 58000, true, 50, 5000, 0, true, true);

            }
        } else if (currentWave == 2) {
            if (gameDifficulty == 2) {
                position = -100;
                position2 = 640;
                unsigned char count = 0;
                for (unsigned char i = 0; i < 20; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 350), 0, 0, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 350), 0, 0, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 200), 1, 10000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 200), 1, 10000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 2) {
                        enemies.emplace_back(Vector2f(position, 50), 2, 15000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 50), 2, 15000, false, 0, 0, 11, false, false);
                        count = 0;
                    }

                    position -= 100;
                    position2 += 100;
                }

                if (Profil::Instance()->credits > 3) {
                    enemies.emplace_back(Vector2f(680, 580), 12, 0, true, 610, 10000, 9, true, false);
                    enemies.emplace_back(Vector2f(-160, 580), 12, 0, true, 30, 10000, 8, true, false);
                }

                enemies.emplace_back(Vector2f(680, 500), 12, 0, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 500), 12, 0, true, 30, 10000, 8, true, false);
                enemies.emplace_back(Vector2f(680, 420), 12, 0, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 420), 12, 0, true, 30, 10000, 8, true, false);

                position = -100;
                position2 = 640;
                count = 0;
                for (unsigned char i = 0; i < 10; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 350), 3, 30000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 350), 3, 30000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 200), 4, 40000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 200), 4, 40000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 2) {
                        enemies.emplace_back(Vector2f(position, 50), 2, 45000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 50), 2, 45000, false, 0, 0, 11, false, false);
                        count = 0;
                    }

                    position -= 100;
                    position2 += 100;
                }

                enemies.emplace_back(Vector2f(160, -50), 4, 58000, true, 50, 200, 1, true, true);
                enemies.emplace_back(Vector2f(290, -50), 4, 58000, true, 50, 200, 2, true, true);
                enemies.emplace_back(Vector2f(230, -50), 4, 62000, true, 50, 5000, 0, true, false);

            } else if (gameDifficulty < 2) {

                position = 0;
                unsigned int time = 0;
                unsigned char mode = 1;

                for (unsigned char i = 0; i < 30; i++) {
                    enemies.emplace_back(Vector2f(position, -30), 11, time, true, 50, 250, mode, true, false);
                    time += 800;
                    if (position < 445)
                        position += 50;
                    else position = 160;
                    if (mode == 1)
                        mode = 2;
                    else mode = 1;
                }

                position = 0;
                time += 3000;

                for (unsigned char i = 0; i < 30; i++) {
                    enemies.emplace_back(Vector2f(position, -30), 1, time, true, 50, 250, mode, true, false);
                    time += 800;
                    if (position < 445)
                        position += 50;
                    else position = 160;
                    if (mode == 1)
                        mode = 2;
                    else mode = 1;
                }

                position = 0;
                time += 3000;
                unsigned char type = 3;

                for (unsigned char i = 0; i < 10; i++) {

                    enemies.emplace_back(Vector2f(position, -30), type, time, true, 50, 250, mode, true, false);
                    time += 2000;
                    if (position < 445)
                        position += 50;
                    else position = 160;
                    if (mode == 1)
                        mode = 2;
                    else mode = 1;
                    if (type == 3)
                        type = 4;
                    else type = 3;
                }
            }
        } else if (currentWave == 3) {
            if (gameDifficulty == 2) {
                enemies.emplace_back(Vector2f(0, -50), 2, 0, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 2, 0, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 2, 2000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 2, 2000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 4000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 1, 4000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 6000, true, 150, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 1, 6000, true, 150, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 8, 8000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 8000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 8, 10000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 10000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 12000, true, 200, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -300), 8, 12000, true, 200, 100, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 6, 18000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 6, 18000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 25000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 27000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 28000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 29000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 8, 34000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 36000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(160, -50), 8, 37000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 38000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(160, -50), 8, 39000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 40000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(160, -50), 8, 41000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 42000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 6, 46000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 6, 46000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(0, -50), 9, 50000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 9, 50000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 9, 54000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(290, -50), 9, 54000, true, 50, 100, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 9, 57000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 57000, true, 100, 200, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 57000, true, 150, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 9, 57000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 68000, true, 50, 200, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 68000, true, 50, 200, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 8, 68000, true, 50, 200, 2, true, false);

                enemies.emplace_back(Vector2f(160, -50), 8, 69000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(160, -50), 8, 69000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(160, -50), 8, 69000, true, 100, 200, 1, true, true);

                enemies.emplace_back(Vector2f(290, -50), 8, 74000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(290, -50), 8, 74000, true, 100, 200, 1, true, false);
                enemies.emplace_back(Vector2f(290, -50), 8, 74000, true, 100, 200, 1, true, true);

            } else if (gameDifficulty < 2) {
                position = 0;
                int time = 0;
                unsigned char mode = 1;

                for (unsigned char i = 0; i < 30; i++) {
                    time += 800;
                    enemies.emplace_back(Vector2f(position, -30), 11, time, true, 50, 250, mode, true, false);
                    if (position < 445)
                        position += 50;
                    else position = 160;

                    if (mode == 1)
                        mode = 2;
                    else mode = 1;
                }

                enemies.emplace_back(Vector2f(0, -50), 0, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(0, -150), 0, 30000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -50), 30000, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -150), 30000, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 34000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 34000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 3, 36000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -150), 3, 38000, true, 50, 1000, 1, true, true);
                enemies.emplace_back(Vector2f(230, -250), 3, 40000, true, 100, 1000, 2, true, false);

                enemies.emplace_back(Vector2f(230, -50), 0, 42000, true, 50, 1000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 43000, true, 50, 1000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 44000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 45000, true, 100, 3000, 2, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 46000, true, 100, 3000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -50), 0, 47000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(160, -50), 4, 50000, true, 50, 200, 1, true, true);
                enemies.emplace_back(Vector2f(290, -50), 4, 58000, true, 50, 200, 2, true, true);
                enemies.emplace_back(Vector2f(230, -50), 4, 62000, true, 50, 5000, 0, true, false);
            }
        } else if (currentWave == 4) {
            if (gameDifficulty == 2) {
                // Super phase ennemi I
                enemies.emplace_back(Vector2f(680, 580), 12, 0, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 580), 12, 0, true, 30, 10000, 8, true, false);
                enemies.emplace_back(Vector2f(680, 500), 12, 5000, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 500), 12, 5000, true, 30, 10000, 8, true, false);
                enemies.emplace_back(Vector2f(680, 420), 12, 10000, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 420), 12, 10000, true, 30, 10000, 8, true, false);

                enemies.emplace_back(Vector2f(680, 480), 0, 2000, false, 0, 0, 9, false, false);
                enemies.emplace_back(Vector2f(-160, 480), 0, 2000, false, 0, 0, 8, false, false);

                enemies.emplace_back(Vector2f(160, -30), 7, 2000, true, 100, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(230, -30), 7, 2000, true, 50, 7000, 0, true, false);
                enemies.emplace_back(Vector2f(290, -30), 7, 2000, true, 100, 5000, 0, true, true);


                enemies.emplace_back(Vector2f(230, -30), 8, 15000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -30), 8, 15000, true, 50, 7000, 1, true, false);
                enemies.emplace_back(Vector2f(230, -30), 8, 15000, true, 150, 5000, 2, true, false);


                enemies.emplace_back(Vector2f(160, -30), 8, 30000, true, 150, 100, 0, true, false);
                enemies.emplace_back(Vector2f(160, -30), 8, 30000, true, 150, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -30), 8, 30000, true, 100, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(230, -30), 8, 30000, true, 50, 100, 1, true, false);
                enemies.emplace_back(Vector2f(230, -30), 8, 30000, true, 50, 100, 2, true, false);
                enemies.emplace_back(Vector2f(290, -30), 8, 30000, true, 100, 100, 0, true, false);
                enemies.emplace_back(Vector2f(290, -30), 8, 30000, true, 100, 100, 1, true, false);

                enemies.emplace_back(Vector2f(220, -50), 14, 40000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(120, -50), 14, 45000, true, 100, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(320, -50), 14, 50000, true, 100, 5000, 0, true, false);

                position = -100;
                position2 = 640;
                unsigned char count = 0;
                for (unsigned char i = 0; i < 20; i++) {
                    if (count == 0) {
                        enemies.emplace_back(Vector2f(position, 350), 1, 60000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 350), 1, 60000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 1) {
                        enemies.emplace_back(Vector2f(position, 200), 1, 70000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 200), 1, 70000, false, 0, 0, 11, false, false);
                        count += 1;
                    } else if (count == 2) {
                        enemies.emplace_back(Vector2f(position, 50), 1, 65000, false, 0, 0, 10, false, false);
                        enemies.emplace_back(Vector2f(position2, 50), 1, 65000, false, 0, 0, 11, false, false);
                        count = 0;
                    }

                    position -= 100;
                    position2 += 100;
                }

            } else if (gameDifficulty < 2) {
                enemies.emplace_back(Vector2f(0, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(200, -50), 7, 2000, true, 50, 4000, 0, true, true);
                enemies.emplace_back(Vector2f(250, -50), 7, 2000, true, 50, 4000, 0, true, true);

                enemies.emplace_back(Vector2f(0, -30), 11, 5000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 5000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 5000, true, 200, 200, 1, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 5000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 5000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 5000, true, 200, 200, 2, true, false);

                enemies.emplace_back(Vector2f(200, -50), 8, 8000, true, 50, 4000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 8, 8000, true, 50, 4000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 10000, true, 200, 500, 2, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 10000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 10000, true, 200, 500, 1, true, false);

                enemies.emplace_back(Vector2f(200, -50), 4, 13000, true, 50, 4000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 4, 13000, true, 50, 4000, 0, true, false);

                enemies.emplace_back(Vector2f(500, 450), 12, 13000, true, 610, 13000, 9, true, false);
                enemies.emplace_back(Vector2f(500, 500), 12, 13000, true, 610, 13000, 9, true, false);

                enemies.emplace_back(Vector2f(230, -50), 5, 18000, true, 50, 4000, 0, true, true);

                enemies.emplace_back(Vector2f(-160, 450), 12, 25000, true, 30, 18000, 8, true, false);
                enemies.emplace_back(Vector2f(-160, 500), 12, 25000, true, 30, 18000, 8, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 25000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 25000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 25000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 25000, true, 150, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(0, -50), 7, 25000, true, 350, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 25000, true, 350, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(280, -30), 11, 25000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(180, -30), 11, 25000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(280, -30), 11, 28000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(180, -30), 11, 28000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(280, -30), 11, 30000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(180, -30), 11, 30000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 30000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 30000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(200, -50), 8, 34000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 8, 34000, true, 100, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(200, -200), 8, 34000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -200), 8, 34000, true, 100, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 8, 38000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(150, -50), 8, 38000, true, 100, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 8, 38000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(335, -50), 8, 38000, true, 100, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(220, -50), 14, 42000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(120, -50), 14, 48000, true, 100, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(320, -50), 14, 56000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 5, 60000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(280, -50), 5, 65000, true, 200, 10000, 0, true, false);
                enemies.emplace_back(Vector2f(180, -50), 5, 65000, true, 200, 10000, 0, true, false);

                enemies.emplace_back(Vector2f(-160, 450), 12, 66000, true, 30, 10000, 8, true, false);
                enemies.emplace_back(Vector2f(-160, 500), 12, 66000, true, 30, 10000, 8, true, false);

            }
        } else if (currentWave == 5) {
            boss.emplace_back(stage, Vector2f(250, -500), 4000);
        }
    } else if (stage == 4) {
        if (currentWave == 1) {
            if (gameDifficulty == 2) {
                enemies.emplace_back(Vector2f(0, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 0, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 0, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(180, -30), 11, 2000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -30), 11, 2000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(280, -30), 11, 2000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 4000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 4000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 4000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 4000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 4000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 4000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -30), 11, 6000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -130), 11, 6000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(230, -230), 11, 6000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(680, 500), 12, 9000, true, 610, 10000, 9, true, false);
                enemies.emplace_back(Vector2f(-160, 500), 12, 9000, true, 30, 10000, 8, true, false);

                enemies.emplace_back(Vector2f(200, -50), 8, 14000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -50), 8, 14000, true, 100, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(200, -200), 8, 16000, true, 50, 1000, 0, true, false);
                enemies.emplace_back(Vector2f(250, -200), 8, 16000, true, 100, 1000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 20000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 20000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 22000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 22000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 22000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 24000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 24000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(100, -30), 11, 24000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 26000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 26000, false, 0, 0, 0, true, true);
                enemies.emplace_back(Vector2f(345, -30), 11, 26000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(180, -30), 5, 30000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 8, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -150), 8, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -250), 8, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -350), 8, 35000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(230, -450), 8, 35000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(280, -30), 5, 40000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 43000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 43000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 43000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 45000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 45000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 45000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -30), 11, 47000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(50, -30), 11, 47000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(100, -30), 11, 47000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(445, -30), 11, 49000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(395, -30), 11, 49000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(345, -30), 11, 49000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(180, -50), 10, 53000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(280, -50), 10, 53000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(230, -30), 3, 58000, true, 100, 5000, 0, true, true);
                enemies.emplace_back(Vector2f(230, -230), 3, 58000, true, 100, 5000, 0, true, true);

                enemies.emplace_back(Vector2f(0, -30), 0, 58000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -30), 0, 58000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(180, -50), 2, 62000, false, 80, 500, 0, true, false);
                enemies.emplace_back(Vector2f(230, -50), 10, 62000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(280, -50), 2, 62000, false, 80, 500, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 64000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 64000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 68000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 68000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 70000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 70000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 0, 72000, false, 0, 0, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 0, 72000, false, 0, 0, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 75000, true, 50, 2000, 0, true, true);
                enemies.emplace_back(Vector2f(445, -50), 7, 75000, true, 50, 2000, 0, true, true);

                enemies.emplace_back(Vector2f(0, -50), 7, 78000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 78000, true, 100, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(230, -50), 14, 82000, true, 100, 8000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 85000, true, 50, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 85000, true, 50, 5000, 0, true, false);

                enemies.emplace_back(Vector2f(0, -50), 7, 88000, true, 100, 5000, 0, true, false);
                enemies.emplace_back(Vector2f(445, -50), 7, 88000, true, 100, 5000, 0, true, false);

            } else if (gameDifficulty < 2) {

                enemies.emplace_back(Vector2f(0, -50), 9, 0, false, 0, 0, 0, true, false);

            }
        } else if (currentWave == 2) {
            enemies.emplace_back(Vector2f(445, -50), 13, 0, true, 100, 6000, 0, true, false);
            enemies.emplace_back(Vector2f(0, -50), 13, 1000, true, 100, 6000, 0, true, false);
            enemies.emplace_back(Vector2f(230, -50), 13, 2000, true, 100, 6000, 0, true, false);
            
            enemies.emplace_back(Vector2f(230, -30), 15, 15000, true, 100, 10000, 0, true, false);
            
            enemies.emplace_back(Vector2f(445, -30), 11, 18000, false, 0, 0, 0, true, false);
            enemies.emplace_back(Vector2f(445, -30), 11, 19000, false, 0, 0, 0, true, true);
            enemies.emplace_back(Vector2f(445, -30), 11, 22000, false, 0, 0, 0, true, false);
            enemies.emplace_back(Vector2f(445, -30), 11, 24000, false, 0, 0, 0, true, false);
            
            enemies.emplace_back(Vector2f(0, -30), 11, 24000, false, 0, 0, 0, true, false);
            enemies.emplace_back(Vector2f(0, -30), 11, 26000, false, 0, 0, 0, true, true);
            enemies.emplace_back(Vector2f(0, -30), 11, 28000, false, 0, 0, 0, true, false);
            enemies.emplace_back(Vector2f(0, -30), 11, 30000, false, 0, 0, 0, true, false);
            
            enemies.emplace_back(Vector2f(230, -50), 13, 34000, true, 50, 6000, 0, true, false);
            
            unsigned int timer = 36000;
            bool powerup = false;
            for (unsigned char i = 0; i < 8; i++) {
                timer += 1000;
                if (i == 7)
                    powerup = true;
                else powerup = false;
                enemies.emplace_back(Vector2f(180, -30), 11, timer, false, 0, 0, 0, true, powerup);
                enemies.emplace_back(Vector2f(280, -30), 11, timer, false, 0, 0, 0, true, powerup);
            }
            
            enemies.emplace_back(Vector2f(230, -50), 13, 38000, true, 150, 6000, 0, true, false);
            
            enemies.emplace_back(Vector2f(680, 500), 12, 40000, true, 610, 10000, 9, true, false);
            enemies.emplace_back(Vector2f(680, 400), 12, 40000, true, 610, 10000, 9, true, false);
            enemies.emplace_back(Vector2f(-160, 500), 12, 42000, true, 30, 10000, 8, true, false);
            enemies.emplace_back(Vector2f(-160, 400), 12, 42000, true, 30, 10000, 8, true, false);
            
            timer = 45000;
            
            for (unsigned char i = 0; i < 12; i++) {
                timer += 1000;
                enemies.emplace_back(Vector2f(-160, 350), 0, timer, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(560, 300), 0, timer, false, 0, 0, 9, false, false);
                
                enemies.emplace_back(Vector2f(-160, 550), 0, timer, false, 0, 0, 8, false, false);
                enemies.emplace_back(Vector2f(560, 500), 0, timer, false, 0, 0, 9, false, false);
            }
            
            enemies.emplace_back(Vector2f(180, -30), 8, 54000, true, 200, 5000, 0, true, false);
            enemies.emplace_back(Vector2f(180, -30), 8, 54000, true, 50, 300, 1, true, false);
            enemies.emplace_back(Vector2f(180, -30), 8, 54000, true, 100, 600, 1, true, false);
            enemies.emplace_back(Vector2f(180, -30), 8, 54000, true, 150, 900, 1, true, false);
            
            enemies.emplace_back(Vector2f(280, -30), 8, 54000, true, 200, 5000, 0, true, false);
            enemies.emplace_back(Vector2f(280, -30), 8, 54000, true, 50, 300, 2, true, false);
            enemies.emplace_back(Vector2f(280, -30), 8, 54000, true, 100, 600, 2, true, false);
            enemies.emplace_back(Vector2f(280, -30), 8, 54000, true, 150, 900, 2, true, false);
            
            enemies.emplace_back(Vector2f(230, -30), 15, 56000, true, 50, 10000, 0, true, false);

        } else if (currentWave == 3) {

        } else if (currentWave == 4) {

        } else if (currentWave == 5) {
            boss.emplace_back(stage, Vector2f(250, -500), 4000);
        }
    } else if (stage == 5) {
        if (currentWave == 1) {

        } else if (currentWave == 2) {

        } else if (currentWave == 3) {

        } else if (currentWave == 4) {

        }
    }

    if (currentWave == 1) {
        for (unsigned char i = 0; i < enemies.size(); i++) {
            enemies[i].startTime += 10000;
        }
    }
}

void Wave::waveBoss(const unsigned char currentWave) {

    if (stage == 1) {
        if (currentWave == 1) {
            int position = 0;
            int position2 = 500;
            for (unsigned char i = 0; i < 5; i++) {
                position -= 100;
                enemies.emplace_back(Vector2f(position, 540), 0, 0, false, 0, 0, 8, false, false);

                position2 += 100;
                enemies.emplace_back(Vector2f(position2, 440), 0, 2000, false, 0, 0, 9, false, false);
            }
        } else if (currentWave == 2) {
            enemies.emplace_back(Vector2f(50, -50), 7, 0, true, 300, 5000, 0, true, true);
            enemies.emplace_back(Vector2f(400, -50), 7, 0, true, 300, 5000, 0, true, true);

        }
    } else if (stage == 2) {
        if (currentWave == 1) {
            enemies.emplace_back(Vector2f(10, -50), 8, 0, true, 50, 10000, 0, true, true);
            enemies.emplace_back(Vector2f(435, -50), 8, 0, true, 50, 10000, 0, true, true);
        } else if (currentWave == 2) {
            int position = -50;
            for (unsigned char i = 0; i < 5; i++) {
                enemies.emplace_back(Vector2f(10, position), 8, 0, false, 0, 10000, 0, true, false);
                enemies.emplace_back(Vector2f(435, position), 8, 0, false, 00, 10000, 0, true, false);
                position -= 50;
            }
        }
    }

    boss.back().currentWave = 0;
}

void Wave::update() {
    if (!finished) {

        if (enemies.size() == 0 && boss.size() == 0 && currentWave < 6) {
            if (!test && currentWave != 0)
                currentWave += 1;

            initialize(stage, currentWave);
        } else if (boss.size() == 1) {
            if (boss.back().currentWave > 0 && boss.back().health[0] > 4000) {
                if (enemies.size() == 0) {
                    waveBoss(boss.back().currentWave);
                }
            }
            if (!boss.back().active) {
                boss.clear();
                finished = true;
            }
        } else if (currentWave > 5)
            finished = true;

        for (unsigned i = 0; i < enemies.size(); i++)
            enemies[i].update();
        if (boss.size() == 1)
            boss.back().update();
    }
}

void Wave::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!finished) {
        for (unsigned char i = 0; i < enemies.size(); i++)
            target.draw(enemies[i], states);
        if (boss.size() == 1)
            target.draw(boss[0], states);
    }
}