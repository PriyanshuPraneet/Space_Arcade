#include <raylib.h>
#include "game.hpp"
#include <string>

std::string formatWithLeadingZeroes(int number, int width){
    std::string numberText = std::to_string(number);
    int leadingZero = width - numberText.length();
     return numberText = std::string(leadingZero,'0')+ numberText;
}

int main()
{
    Color purple={60,30,60,255};
    Color gold = {255, 203, 0, 255};
   int offset = 50; 
   int windowsht = 600;
   int windowswt = 650;
   InitWindow(windowswt+offset, windowsht+2*offset, "Invasion");
   InitAudioDevice();
   Font font = LoadFontEx("Font/monogram.ttf",64,0,0);
   Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");
   SetTargetFPS(60);
   Game game;
   while(WindowShouldClose() == false){
    UpdateMusicStream(game.music);
    BeginDrawing();
    game.update();
    ClearBackground(purple);
    DrawRectangleRoundedLines({10,10,680,680},0.18f,20,2,gold);
    DrawLineEx({25,630}, {675,630},3,gold);
    if(game.run){
    DrawTextEx(font, "LEVEL 01", {470,640},34,2,gold);
    }
    else{
        DrawTextEx(font, "GAME OVER", {470,640},34,2,gold);
    }
    float x = 50;
    for(int i=0; i<game.lives; i++){
        DrawTextureV(spaceshipImage, {x,645}, WHITE);
        x+=50;
    }

    DrawTextEx(font, "SCORE", {50,15}, 34, 2, gold);
    std::string scoreText = formatWithLeadingZeroes(game.score, 5);
    DrawTextEx(font, scoreText.c_str(), {50,40},34,2,gold); 

    DrawTextEx(font, "HIGH SCORE", {470,15}, 34,2,gold);
    std::string highscoretext = formatWithLeadingZeroes(game.highscore, 5);
    DrawTextEx(font, highscoretext.c_str(), {555,40}, 34, 2, gold);

    game.draw();
    game.HandleInput();

    EndDrawing();
   }
   CloseWindow();
   CloseAudioDevice();
}