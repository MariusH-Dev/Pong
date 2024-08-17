#include "EffectManager.h"

EffectManager::EffectManager() {
    scoreAnimationState = 0.0f;
    glowEffectTimer = 0.0f;
    isGlowing = false;
}


void EffectManager::TriggerScoreEffect() {
    scoreAnimationState = 1.0f;  
    glowEffectTimer = 1.0f;        
    isGlowing = true;
}

void EffectManager::UpdateEffects() {
    if (glowEffectTimer > 0.0f) {
        glowEffectTimer -= GetFrameTime(); 
    }
    else {
        isGlowing = false;
    }

    if (scoreAnimationState > 0.0f) {
        scoreAnimationState -= GetFrameTime(); 
    }
}


void EffectManager::DrawGlowEffect(float ballX, float ballY, float ballRadius) {
    if (isGlowing) {
        for (int i = 0; i < 5; i++) {
            float glowRadius = ballRadius + i * 5;
            float alpha = glowEffectTimer * (1.0f - (i * 0.2f));  
            DrawCircle(ballX, ballY, glowRadius, Fade(YELLOW, alpha * 0.5f));
        }
    }
}


void EffectManager::DrawAnimatedScore(int playerScore, int compScore, int prevPlayerScore, int prevCompScore) {
    // Berechne die Bildschirmmitte
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Skaliere und zeige nur die Punktzahl an, die sich geändert hat
    if (playerScore > prevPlayerScore) {
        // Skaliere die Spieler-Punktzahl in der Mitte des Bildschirms
        float scale = 1.0f + scoreAnimationState * 2.0f;
        DrawText(TextFormat("%i", playerScore), screenWidth / 2 - 20, screenHeight / 2 - 20, 50 * scale, WHITE);
    }
    else if (compScore > prevCompScore) {
        // Skaliere die Computer-Punktzahl in der Mitte des Bildschirms
        float scale = 1.0f + scoreAnimationState * 2.0f;
        DrawText(TextFormat("%i", compScore), screenWidth / 2 - 20, screenHeight / 2 - 20, 50 * scale, WHITE);
    }
    else {
        // Zeichne die normalen Punktzahlen, wenn keine Animation aktiv ist
        DrawText(TextFormat("%i", compScore), screenWidth / 4 - 20, 20, 25, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * (screenWidth / 4) - 20, 20, 25, WHITE);
    }
}


void EffectManager::ResetEffects() {
    scoreAnimationState = 0.0f;
    glowEffectTimer = 0.0f;
    isGlowing = false;
}
