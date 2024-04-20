#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>
class SpaceShip{
    public:
        SpaceShip();
        ~SpaceShip();
        void draw();
        void MoveLeft();
        void MoveRight();
        void Fire();
        Rectangle getRect();
        void Reset();
        std::vector<Laser>lasers;
    private:
        Texture2D image;
        Vector2 position;    
        double LastFireTime;

};
