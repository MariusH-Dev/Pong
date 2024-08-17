#include "particle.h"

std::vector<Particle> particles;

void Particle::CreateParticle(Vector2 positon, int count)
{
	for (int i = 0; i < count; i++)
	{
		Particle p;
		p.position = positon;
		p.velocity = { GetRandomValue(-50,50) / 20.0f, GetRandomValue(-50,50) / 20.0f };
		p.color = WHITE;
		p.lifetime = 1.0f;
		particles.push_back(p);
	}
}

void Particle::UpdateParticles()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].position.x += particles[i].velocity.x;
		particles[i].position.y += particles[i].velocity.y;
		particles[i].lifetime = GetFrameTime();

		if (particles[i].lifetime <= 0)
		{
			particles.erase(particles.begin()) + i;
			i--;
		}
	}
}

void Particle::DrawParticle()
{
	for (const Particle& p : particles)
		DrawCircleV(p.position, 3, Fade(p.color, p.lifetime));
}
