#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <vector>

class Particle {
public:
	Vector2 position;
	Vector2 velocity;
	Color color;
	float lifetime;
	
	static void CreateParticle(Vector2 positon, int count);
	static void UpdateParticles();
	static void DrawParticle();
};

#endif

