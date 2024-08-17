#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "raylib.h"

class EffectManager {
private:
    float scoreAnimationState;
    float glowEffectTimer;
    bool isGlowing;

public:
    EffectManager(); 

    void TriggerScoreEffect();     
    void UpdateEffects();         
    void DrawGlowEffect(float ballX, float ballY, float ballRadius); 
    void DrawAnimatedScore(int playerScore, int compScore, int prevPlayerScore, int prevCompScore);
    void ResetEffects();          
};

#endif
