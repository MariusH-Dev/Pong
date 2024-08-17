#include <iostream>
#include "game.h"

Game::Game()
    : ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, 8, 10),
    player(GetScreenWidth() - 55, GetScreenHeight() / 2 - 60, 20, 120, 10),
    computer(35, GetScreenHeight() / 2 - 60, 20, 120, 10),
    playerScore(0), compScore(0), gameStarted(false) {}

Game::~Game() 
{
    // Unload sounds and music
    UnloadSound(collisionSound);
    UnloadSound(scoreSound);
    UnloadMusicStream(bg_music);

    CloseAudioDevice();
}

void Game::CheckCollision()
{
    if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { player.posX, player.posY, player.width, player.height }))
    {
        ball.speedX *= -1;
        PlaySound(collisionSound);
    }

    if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { computer.posX, computer.posY, computer.width, computer.height }))
    {
        ball.speedX *= -1;
        PlaySound(collisionSound);
    }

    // Check collision detection with edges 
    if (ball.posY + ball.radius >= GetScreenHeight() || ball.posY - ball.radius <= 0)
    {
        ball.speedY *= -1;
        PlaySound(edgeCollisionSound);
    }
}

void Game::CheckGameStarted(float deltaTime)
{
    if (!gameStarted) {
        if (IsKeyPressed(KEY_ENTER))
            gameStarted = true;
    }
    else
    {
        ball.Update();
        player.Update();
        computer.Update(ball.posY, ball.speedX, deltaTime);

        Game::CheckCollision();
        Game::CheckScore();
    }
}

void Game::CheckScore()
{
    if (ball.posX + ball.radius >= GetScreenWidth())
    {
        compScore++;
        SetSoundPan(scoreSound, 0.2);
        PlaySound(scoreSound);
        ball.ResetBall();

        Game::SpawnPowerUp();
    }

    if (ball.posX - ball.radius <= 0)
    {
        playerScore++;
        SetSoundPan(scoreSound, 0.8);
        PlaySound(scoreSound);
        ball.ResetBall();

        Game::SpawnPowerUp();
    }
}

void Game::Draw() 
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (const auto &powerUp : powerUps) {
        powerUp.Draw();
    }

    if (!gameStarted) 
    {
        DrawText("PONG", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 80, 60, WHITE);
        DrawText("Press ENTER to Start", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 20, 30, WHITE);
    }
    else 
    {
        ball.Draw();
        player.Draw();
        computer.Draw();

        DrawText(TextFormat("%i", compScore), GetScreenWidth() / 4 - 20, 20, 25, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * (GetScreenWidth() / 4) - 20, 20, 25, WHITE);
    }

    EndDrawing();
}

void Game::InitAudio()
{
    InitAudioDevice();

    LoadMusicAndSounds();

    SetSoundVolume(collisionSound, 1);
    SetSoundVolume(edgeCollisionSound, 1);
    SetSoundVolume(powerUpSound, 0.6);

    PlayMusicStream(bg_music);
    SetMusicVolume(bg_music, 0.1);
}

void Game::LoadMusicAndSounds()
{
    collisionSound = LoadSound("assets/sounds/click2.wav");
    edgeCollisionSound = LoadSound("assets/sounds/click4.wav");
    powerUpSound = LoadSound("assets/sounds/Rise03.wav");
    scoreSound = LoadSound("assets/sounds/Coin01.wav");
    bg_music = LoadMusicStream("assets/sounds/bg_music.mp3");
}

void Game::PowerUpLogic() {
    for (auto& powerUp : powerUps)
    {
        powerUp.Update();

        if (powerUp.CheckCollisionWithPaddle({ player.posX, player.posY, player.width, player.height }))
        {
            powerUp.ActivateEffect(player);
            PlaySound(powerUpSound);
        }
    }

    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(),
        [](const PowerUp& powerUp) { return !powerUp.isActive; }),
        powerUps.end());
}

void Game::SpawnPowerUp()
{
    if (GetRandomValue(0, 100) > 1) 
        float spawnX = GetRandomValue(0, GetScreenWidth() - 20);
        float spawnY = GetScreenHeight() / 2;
        powerUps.push_back(PowerUp(GetRandomValue(0, GetScreenWidth() - 20), 0));
}

void Game::Update() 
{
    //  Delta Time for smooth movements
    float deltaTime = GetFrameTime();

    UpdateMusicStream(bg_music);
    Game::CheckGameStarted(deltaTime);
    Game::PowerUpLogic();
}

void Game::UpdateDifficulty()
{
    if (playerScore >= 5)
        computer.speed = 12;

    if (playerScore >= 10)
        player.height = 100;
}

void Game::ResetGame() 
{
    playerScore = 0;
    compScore = 0;
    ball.ResetBall();
    gameStarted = false;
}
