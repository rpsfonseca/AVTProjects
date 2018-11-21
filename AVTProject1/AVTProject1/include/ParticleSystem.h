#pragma once

#include <glm\glm.hpp>
#include "Material.h"

namespace AVTEngine
{
	class Mesh;
	class Texture;

	class ParticleSystem
	{
		static const int PARTICLE_COUNT = 20;

		struct Particle
		{
			Particle() {}
			Particle(float life, float fadeRate, glm::vec3 color, glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration)
			: life(life), fadeRate(fadeRate), color(color), position(position), velocity(velocity), acceleration(acceleration) { }

			float life;
			float fadeRate;
			glm::vec3 color;
			glm::vec3 position;
			glm::vec3 velocity;
			glm::vec3 acceleration;
		};
		Particle particles[PARTICLE_COUNT];
		float stepSize = 1.f / 60;
		Mesh* mesh;
		Texture* texture;
		Material material = Material("lensflare");
		float scale = 1;
		float maxLife = 3.0f; // 2 seconds

		void renderParticles();
		Particle generateParticle();

	public:
		ParticleSystem();
		void step();
		void draw();
	};
}