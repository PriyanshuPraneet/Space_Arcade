#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
class Game{
    public:
        Game();
        ~Game();
        void draw();
        void update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
        Music music;
    private:
        SpaceShip spaceship;
        void DeleteInactiveLaser();
        std::vector<Obstacle> CreateObstacle();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AlienShootLaser();
        void CheckForCollision();
        void GameOver();
        void Reset();
        void InitGame();
        void checkHighscore();
        void saveHighscore(int highscore);
        int loadHighscore();
        std::vector<Obstacle> obstacles;
        std::vector<Alien>aliens;
        int AliensDirection;
        std:: vector<Laser> alienLaser;
        constexpr static float alienLaserShootInterval = 0.30;
        float timeLastAlienFire;
        MysteryShip mysteryship;
        float mysteryshipTimeInterval;
        float mysteryshipLastSpawn;
        Sound explosion;
};