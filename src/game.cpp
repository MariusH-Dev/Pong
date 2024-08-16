#include <iostream>
#include "game.h"

Game::Game()
    : ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, 8, 10),
    player(GetScreenWidth() - 55, GetScreenHeight() / 2 - 60, 20, 120, 10),
    computer(35, GetScreenHeight() / 2 - 60, 20, 120, 10),
    playerScore(0), compScore(0), gameStarted(false) {}

Game::~Game() {
    // Unload sounds and music
    UnloadSound(collisionSound);
    UnloadSound(scoreSound);
    UnloadMusicStream(bg_music);

    CloseAudioDevice();
}

void Game::InitAudio() {
    InitAudioDevice();

    // Load sounds and music
    collisionSound = LoadSound("assets/sounds/click2.wav");
    edgeCollisionSound = LoadSound("assets/sounds/click4.wav");
    scoreSound = LoadSound("assets/sounds/Coin01.wav");
    bg_music = LoadMusicStream("assets/sounds/bg_music.mp3");
    SetSoundVolume(collisionSound, 1);
    SetSoundVolume(edgeCollisionSound, 1);

    PlayMusicStream(bg_music);
    SetMusicVolume(bg_music, 0.1);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (!gameStarted) {
        DrawText("PONG", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 80, 60, WHITE);
        DrawText("Press ENTER to Start", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 20, 30, WHITE);
    }
    else {
        ball.Draw();
        player.Draw();
        computer.Draw();

        DrawText(TextFormat("%i", compScore), GetScreenWidth() / 4 - 20, 20, 25, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * (GetScreenWidth() / 4) - 20, 20, 25, WHITE);
    }

    EndDrawing();
}

void Game::Update() {

    //  Delta Time for smooth movements
    float deltaTime = GetFrameTime();

    UpdateMusicStream(bg_music);

    if (!gameStarted) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameStarted = true;
        }
    }
    else {
        ball.Update();
        player.Update();
        computer.Update(ball.posY, ball.speedX, deltaTime);

        // Ball collision detection with paddles
        if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { player.posX, player.posY, player.width, player.height })) {
            ball.speedX *= -1;
            PlaySound(collisionSound);
        }

        if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { computer.posX, computer.posY, computer.width, computer.height })) {
            ball.speedX *= -1;
            PlaySound(collisionSound);
        }

        // Check whether a point has been scored
        if (ball.posX + ball.radius >= GetScreenWidth()) {
            compScore++;
            SetSoundPan(scoreSound, 0.2);
            PlaySound(scoreSound);
            ball.ResetBall();
        }

        if (ball.posX - ball.radius <= 0) {
            playerScore++;
            SetSoundPan(scoreSound, 0.8);
            PlaySound(scoreSound);
            ball.ResetBall();
        }

        // Check collision detection with edges 
        if (ball.posY + ball.radius >= GetScreenHeight() || ball.posY - ball.radius <= 0) {
            ball.speedY *= -1;
            PlaySound(edgeCollisionSound);
        }
    }
}

void Game::ResetGame() {
    playerScore = 0;
    compScore = 0;
    ball.ResetBall();
    gameStarted = false;
}
