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

public:
    Game();
    void Update();
    void Draw();
    void ResetGame();
};

#endif
