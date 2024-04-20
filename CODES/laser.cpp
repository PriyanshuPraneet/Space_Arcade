#include "laser.hpp"

Laser::Laser(Vector2 position, int speed)
{
    this->position  = position;
    this->speed = speed;
    active = true;
}
void Laser::draw(){
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

void Laser::update()
{
    position.y+=speed;
    if(position.y > GetScreenHeight() - 100 || position.y<25){
        active = false;
    }
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}
