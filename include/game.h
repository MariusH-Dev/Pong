#ifndef GAME_H
#define GAME_H

#include "comp_paddle.h"
#include "ball.h"
#include "paddle.h"
#include "powerup.h"
#include "raylib.h"

#include <vector>

using namespace std;

class Game {
private:
    Ball ball;
    Paddle player;
    CompPaddle computer;

    vector<PowerUp> powerUps;

    int compScore;
    int playerScore;

    float spawnX, spawnY;

    bool gameStarted;

    // Audio components
    Sound collisionSound, edgeCollisionSound, powerUpSound, scoreSound;
    Music bg_music;

public:
    Game();
    ~Game();
    void PowerUpLogic();
    void CheckCollision();
    void CheckGameStarted(float deltaTime);
    void CheckScore();
    void Draw();
    void InitAudio();
    void LoadMusicAndSounds();
    void SpawnPowerUp();
    void Update();
    void UpdateDifficulty();
    void ResetGame();

    template <typename T>
    T Clamp(T value, T min, T max);
};

#endif
