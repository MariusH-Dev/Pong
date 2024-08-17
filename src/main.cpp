#include "raylib.h"
#include "game.h"

int main() 
{
    InitWindow(1024, 768, "Pong 2D");
    SetTargetFPS(60);

    Game pongGame;

    pongGame.InitAudio();

    while (!WindowShouldClose()) 
    {
        pongGame.Update();
        pongGame.Draw();
    }

    return 0;
}