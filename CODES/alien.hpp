#pragma once

#include<raylib.h>

class Alien{
    public:
        Alien(int type, Vector2 position);
        void Draw();
        void Update(int direction);
        int GetType();
        int type;
        static void unloadImages(); 
        Rectangle getRect();   
        static Texture2D alienImages[3];
        Vector2 position;
    private:
};