#include "game.hpp"
#include<iostream>
#include<fstream>

Game::Game()
{   
    music = LoadMusicStream("sound/title.mp3");
    explosion = LoadSound("sound/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}
Game::~Game()
{
    Alien::unloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosion);
}
void Game::update(){
    if(run){
        double currentTime = GetTime();
        if(currentTime - mysteryshipLastSpawn > mysteryshipTimeInterval){
            mysteryship.Spawn();
            mysteryshipLastSpawn = GetTime();
            mysteryshipTimeInterval = GetRandomValue(0,10);
        }
        for(auto& laser : spaceship.lasers){
            laser.update();
        }
        MoveAliens();
        AlienShootLaser();
        for(auto& laser : alienLaser){
            laser.update();
        }
        DeleteInactiveLaser();
        mysteryship.Update();
        CheckForCollision();
    }
    else{
        if(IsKeyDown(KEY_ENTER)){
            Reset();
            InitGame();
        }
    }
}
void Game::draw(){
    spaceship.draw();
    for(auto& laser : spaceship.lasers){
        laser.draw();
    }
    for(auto& obstacle : obstacles){
        obstacle.draw();
    }
    for(auto& alien : aliens){
        alien.Draw();
    }
    for(auto& laser : alienLaser){
        laser.draw();
    }
    mysteryship.Draw();
}
void Game::HandleInput(){
    if(run){
        if(IsKeyDown(KEY_LEFT)){
            spaceship.MoveLeft();
        }
        else if(IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight();
        }
        else if(IsKeyDown(KEY_SPACE)){
            spaceship.Fire();
        }
    }
}

void Game::DeleteInactiveLaser()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active){
            it = spaceship.lasers.erase(it);
        }
        else{
            ++it;
        }
    }
    for(auto it = alienLaser.begin(); it != alienLaser.end();){
        if(!it -> active){
            it = alienLaser.erase(it);
        }
        else{
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacle()
{
    float ObstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * ObstacleWidth))/5;
    for(int i=0; i<4; i++){
        float offsetx = (i+1)*gap + i*ObstacleWidth;
        obstacles.push_back(Obstacle({offsetx,float(GetScreenHeight()-200)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row =0; row<4; row++){
        for(int col = 0; col<11; col++){
            int alientype;
            if(row == 0){
                alientype = 3;
            }
            else if(row==1 || row==2){
                alientype = 2;
            }
            else{
                alientype = 1;
            }
            float x  = 75 + col * 55;
            float y = 60 + row * 55;
            aliens.push_back(Alien(alientype, {x,y}));
        }
    }
    return aliens;
}
void Game::MoveAliens(){
    for(auto& alien: aliens){
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()-25){
            AliensDirection = -1;
            MoveDownAliens(4);
        }
        if(alien.position.x < 25){
            AliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(AliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAlienFire >= alienLaserShootInterval && !aliens.empty())
    {
    int RandomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& alien = aliens[RandomIndex];
    alienLaser.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2, alien.position.y + alien.alienImages[alien.type - 1].height}, 8));
    timeLastAlienFire = GetTime();
    }
}

void Game::CheckForCollision()
{
    for(auto& laser: spaceship.lasers){
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it->getRect(), laser.getRect())){
                PlaySound(explosion);
                if(it -> type==1){
                    score+=100;
                }
                else if(it -> type==2){
                    score+=200;
                }
                else if(it -> type ==3){
                    score+=300;
                }
                checkHighscore();
                it = aliens.erase(it);
                laser.active = false;
            }else{
                ++it;
            }
        }
        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it->getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else{
                    ++it;
                }
            }
        }
            if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
                mysteryship.alive = false;
                laser.active = false;
                score+=500;
                checkHighscore();
                PlaySound(explosion);
            }
        }
    for(auto& laser: alienLaser){
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            lives--;
            if(lives==0){
                GameOver();
            }
        }
        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it->getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else{
                    ++it;
                }
            }
        }
    }
        for(auto& alien: aliens){
            for(auto& obstacle: obstacles){
                auto it = obstacle.blocks.begin();
                while(it != obstacle.blocks.end()){
                    if(CheckCollisionRecs(it->getRect(), alien.getRect())){
                        it = obstacle.blocks.erase(it);
                    }
                    else{
                        it++;
                    }
                }
            }
        if(CheckCollisionRecs(spaceship.getRect(), alien.getRect())){
            GameOver();
        }
     }
}

void Game::GameOver()
{
    run = false;
}

void Game::InitGame()
{
    obstacles = CreateObstacle();
    aliens = CreateAliens();
    AliensDirection = 1;
    timeLastAlienFire = 0.0;
    mysteryshipLastSpawn = 0.0;
    mysteryshipTimeInterval = GetRandomValue(10,20);
    lives = 3;
    run = true;
    score = 0;
    highscore = loadHighscore() ;
}
void Game::checkHighscore()
{
    if(score > highscore){
        highscore = score;
        saveHighscore(highscore);
    }
}
void Game::saveHighscore(int highscore)
{
    std:: ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile<<highscore;
        highscoreFile.close();
    }
    else{
        std::cerr<<"Failed to save highscore"<<std::endl;
    }
}
int Game::loadHighscore(){
    int loadedhighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile>>loadedhighscore;
        highscoreFile.close();
    }
    else{
        std::cerr<<"Failed to load highscore"<<std::endl;
    }
    return loadedhighscore;
}
void Game ::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLaser.clear();
    obstacles.clear();
}
