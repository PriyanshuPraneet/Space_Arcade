#include "spaceship.hpp"



SpaceShip::SpaceShip()
{
    image = LoadTexture("Graphics/newship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = (GetScreenHeight() - image.height-75);
    LastFireTime=0.0;
}
SpaceShip::~SpaceShip()
{
    UnloadTexture(image);
}
void SpaceShip::draw()
{
    DrawTextureV(image, position, WHITE);
}
void SpaceShip::MoveLeft()
{
    position.x = position.x - 7;
    if(position.x < 25){
        position.x = 25;
    }
}
void SpaceShip::MoveRight()
{
    position.x = position.x + 7;
    if(position.x > GetScreenWidth() - image.width-25){
        position.x = GetScreenWidth() - image.width-25;
    }
}

void SpaceShip::Fire()
{
    if(GetTime() - LastFireTime >= 0.35){
        lasers.push_back(Laser( {position.x + image.width/2 - 2, position.y}, -6));
        LastFireTime = GetTime();
    }
}

Rectangle SpaceShip::getRect()
{
    return{position.x, position.y, float (image.width), float (image.height)};
}

void SpaceShip::Reset()
{
    position.x = (GetScreenWidth()-image.width)/ 2.0f;
    position.y = GetScreenHeight() - image.height-75;
    lasers.clear();

}
