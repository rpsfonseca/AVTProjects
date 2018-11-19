#include "ParticleSystem.h"
#include "Mesh.h"
#include "ResourcesManager.h"
#include <cstdlib>
#include "Shader.h"
#include "Application.h"
#include <algorithm>
#include "scene.h"
#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

namespace AVTEngine
{
	ParticleSystem::ParticleSystem() {
		mesh = new Mesh(
			{ glm::vec3(-.5f, -.5f, 0.f), glm::vec3(-.5f, .5f, 0.f), glm::vec3(.5f, .5f, 0.f), glm::vec3(.5f, -.5f, 0.f) },
			{ 0, 1, 2,
			  2, 3, 0 },
			{ glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0) }
		);

		texture = ResourcesManager::loadTextureWithAlpha("particle", "textures\\particle.png");

		for (int i = 0; i < PARTICLE_COUNT; i++) {
			particles[i] = generateParticle();
		}

		material.getShader()->use();
		material.getShader()->setInteger("texture0", 0);
		glUseProgram(0);
	}

	void ParticleSystem::step() {
		for (auto& p : particles) {
			p.velocity += stepSize * p.acceleration;
			p.position += stepSize * p.velocity;
			p.life -= stepSize * p.fadeRate;

			if (p.life <= 0) {
				p = generateParticle();
			}
		}
	}

	ParticleSystem::Particle ParticleSystem::generateParticle() {
		return Particle(
			1.0f + rand() % 10 / 10.f * maxLife,
			1.f, // real time
			glm::vec3(1.f, 0.7f, 0.4f),
			Application::getInstance()->scene->car->getPosition(),
			glm::vec3(rand() % 10 / 10.f * 1.f, 0.2f + rand() % 10 / 10.f, rand() % 10 / 10.f * 1.f),
			glm::vec3(0.04f, 0.01f, -0.02f)
		);
	}

	void ParticleSystem::draw() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);

		renderParticles();

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void ParticleSystem::renderParticles() {
		for (auto& p : particles) {
			material.getShader()->use();
			material.setTexture("texture0", texture);
			material.getShader()->setVec4("tint", glm::vec4(.2f, .2f, .2f, std::max(p.life / maxLife, 0.f)));

			// bind/active uniform sampler/texture objects
			auto* samplers = material.getSamplerUniforms();
			for (auto it = samplers->begin(); it != samplers->end(); ++it)
			{
				it->second.texture->bind(it->second.unit);
			}

			material.getShader()->setMat4("viewProjectionMatrix", Application::getInstance()->getCurrentCamera().getViewProjection());
			material.getShader()->setMat4("modelMatrix",
				glm::scale(glm::translate(glm::identity<glm::mat4>(), p.position), glm::vec3(scale)));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->id);

			glBindVertexArray(mesh->getVao());
			if (mesh->usingIndices)
			{
				glDrawElements(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, mesh->getVerticesSize());
			}

			for (auto it = samplers->begin(); it != samplers->end(); ++it)
			{
				it->second.texture->unbind();
			}
		}
	}
}