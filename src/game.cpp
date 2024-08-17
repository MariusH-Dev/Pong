#include <iostream>
#include "game.h"
#include "particle.h"
#include "effectManager.h"

EffectManager effectManager;

int playerScore = 0;
int compScore = 0;
int prevPlayerScore = 0;
int prevCompScore = 0;

Game::Game()
    : ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, 8, 10),
    player(GetScreenWidth() - 55, GetScreenHeight() / 2 - 60, 20, 120, 10),
    computer(35, GetScreenHeight() / 2 - 60, 20, 120, 10),
    playerScore(0), compScore(0), gameStarted(false), hueShift(0.0f) {}

Game::~Game() 
{
    // Unload sounds and music
    UnloadSound(collisionSound);
    UnloadSound(scoreSound);
    UnloadMusicStream(bg_music);

    CloseAudioDevice();
}

void Game::BeginDrawingGameContent()
{
    
    // Draw PowerUps
    for (const auto& powerUp : powerUps) {
        powerUp.Draw();
    }

    // Draw Startscreen
    if (!gameStarted)
    {
        DrawText("PONG", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 80, 60, WHITE);
        DrawText("Press ENTER to Start", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 20, 30, WHITE);
    }
    // Draw the Game
    else
    {
        ball.Draw();
        player.Draw();
        computer.Draw();

        DrawText(TextFormat("%i", compScore), GetScreenWidth() / 4 - 20, 20, 35, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * (GetScreenWidth() / 4) - 20, 20, 35, WHITE);
    }

}

void Game::CheckCollision()
{
    if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { player.posX, player.posY, player.width, player.height }))
    {
        if (ball.speedX > 0)
        {
            ball.posX = player.posX - ball.radius;
            ball.speedX *= -1;
            PlaySound(collisionSound);
            Particle::CreateParticle({ ball.posX, ball.posY }, 20);

            float hitPosition = (ball.posY - player.posY) / player.height;
            float angelFactor = (hitPosition - 0.5f) * 2;

            Game::DynamicBallDirection(angelFactor);
        }
        ball.IncreaseSpeed();
    }

    if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { computer.posX, computer.posY, computer.width, computer.height }))
    { 
        if (ball.speedX < 0)
        {
            ball.posX = computer.posX + computer.width + ball.radius;
            ball.speedX *= -1;
            PlaySound(collisionSound);
            Particle::CreateParticle({ ball.posX, ball.posY }, 20);

            float hitPosition = (ball.posY - computer.posY) / computer.height;
            float angleFactor = (hitPosition - 0.5f) * 2;

            Game::DynamicBallDirection(angleFactor);
        }
        ball.IncreaseSpeed();
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
    float saturation = 0.25f;
    float brightness = 0.15f;

    hueShift += 0.001f;
    if (hueShift > 1)
        hueShift = 0.0f;

    Color dynamicBackgroundColor = ColorFromHSV(hueShift * 360.0f, saturation, brightness);

    BeginDrawing();
    ClearBackground(dynamicBackgroundColor);   

    BeginDrawingGameContent();

    ManageEffects();

    Particle::DrawParticle();
    
    EndDrawing();
}

void Game::DynamicBallDirection(float angleFactor)
{
    ball.speedY = angleFactor * abs(ball.speedX);
    if (fabs(ball.speedY) < 5)
        ball.speedY = copysign(5, ball.speedY);
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

void Game::ManageEffects()
{
    if (playerScore > prevPlayerScore || compScore > prevCompScore) {
        effectManager.TriggerScoreEffect();
        prevPlayerScore = playerScore;
        prevCompScore = compScore;
    }

    effectManager.UpdateEffects();

    effectManager.DrawGlowEffect(ball.posX, ball.posY, ball.radius);
}

void Game::PowerUpLogic() {
    for (auto& powerUp : powerUps)
    {
        powerUp.Update();

        if (powerUp.CheckCollisionWithPaddle({ player.posX, player.posY, player.width, player.height }) || powerUp.CheckCollisionWithPaddle({ computer.posX, computer.posY, computer.width, computer.height }))
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
    if (GetRandomValue(0, 100) > 90) {
        float spawnX = GetRandomValue(0, GetScreenWidth() - 20);
        float spawnY = GetScreenHeight() / 2;
        powerUps.push_back(PowerUp(GetRandomValue(0, GetScreenWidth() - 20), 0));
        cout << "PowerUp Spawend" << endl;
    }
}

void Game::Update() 
{
    //  Delta Time for smooth movements
    float deltaTime = GetFrameTime();

    UpdateMusicStream(bg_music);
    Game::CheckGameStarted(deltaTime);
    Game::PowerUpLogic();
    Particle::UpdateParticles();

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