#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "ball.h"
#include "paddle.h"
#include "comp_paddle.h"

class Game {
private:
    Ball ball;
    Paddle player;
    CompPaddle computer;

    int playerScore;
    int compScore;

    bool gameStarted;

    // Audio components
    Sound collisionSound;
    Sound edgeCollisionSound;
    Sound scoreSound;
    Music bg_music;

public:
    Game();
    ~Game();
    void Draw();
    void InitAudio();
    void Update();
    void ResetGame();
};

#endif
