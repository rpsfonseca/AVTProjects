#include "LensFlare.h"
#include "GL\glut.h"
#include "Application.h"
#include "Renderer.h"
#include "CommandBuffer.h"
#include "ResourcesManager.h"
#include <cmath>
#include <cstdlib>
#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

namespace AVTEngine
{
	LensFlare::LensFlare()
	{
		mesh = new Mesh(
			{ glm::vec3(-.5f, -.5f, 0.f), glm::vec3(-.5f, .5f, 0.f), glm::vec3(.5f, .5f, 0.f), glm::vec3(.5f, -.5f, 0.f) },
			{ 0, 1, 2,
			  2, 3, 0 },
			{ glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0) }
		);
		
		for (int i = 0; i < nPieces; i++) {
			element[i] = FlareElement(
				ResourcesManager::loadTextureWithAlpha("flare" + std::to_string(i), "textures\\flare" + std::to_string(i) + ".png"),
				((float)(rand() % 60)) / 100.f + 0.6f,
				((float)(rand() % 50)) / 100.f + 0.5f,
				0xFFFFFFFF);
		}

		material.getShader()->use();
		material.getShader()->setInteger("texture0", 0);
		glUseProgram(0);

		float vertices[] = {
			0.0f, 0.0f,
			5.0f, 0.0f,
			5.0f, 5.0f,
			0.0f, 5.0f
		};

		GL_CHECK_ERRORS

			glGenVertexArrays(1, &_vaoID);
		glBindVertexArray(_vaoID);
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray((*_shader)["in_Position"]);
		glVertexAttribPointer((*_shader)["in_Position"], 2, GL_FLOAT, GL_FALSE, 0, 0);


		GL_CHECK_ERRORS

			//Just initialize with something for now, the tex coords are updated
			//for each character printed
			float texCoords[] = {
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f
		};

		glGenBuffers(1, &_texCoordBuffer);
		GL_CHECK_ERRORS
			glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
		GL_CHECK_ERRORS
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &texCoords[0], GL_DYNAMIC_DRAW);
		GL_CHECK_ERRORS
			//glEnableVertexAttribArray((*_shader)["texCoord"]);
		GL_CHECK_ERRORS
			//glVertexAttribPointer((*_shader)["texCoord"], 2, GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK_ERRORS
	}

	void LensFlare::draw()
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		auto projectedLightPos = Application::getInstance()->getCurrentCamera().getViewProjection() * glm::vec4(lightPosition, 0.f);
		
		int viewport[] = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		GLdouble winX, winY, winZ;
		glm::dmat4 viewProj = glm::dmat4();
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				viewProj[x][y] = Application::getInstance()->getCurrentCamera().getProjection()[x][y];
		glm::dmat4 view = glm::dmat4();
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				view[x][y] = Application::getInstance()->getCurrentCamera().getView()[x][y];
		gluProject(
			lightPosition.x, lightPosition.y, lightPosition.z,
			&view[0][0],
			&viewProj[0][0],
			viewport,
			&winX, &winY, &winZ);

		//renderFlare(projectedLightPos.x, projectedLightPos.y, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		renderFlare(winX, winY, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	}

	void LensFlare::renderFlare(int lx, int ly, int cx, int cy)
	{
		int     dx, dy;          // Screen coordinates of "destination"
		int     px, py;          // Screen coordinates of flare element
		int     maxflaredist, flaredist, flaremaxsize, flarescale;
		int     width, height;    // Piece parameters;
		int     i;

		// Compute how far off-center the flare source is.
		maxflaredist = sqrt(cx*cx + cy * cy);
		flaredist = sqrt((lx - cx)*(lx - cx) +
			(ly - cy)*(ly - cy));
		flaredist = (maxflaredist - flaredist);
		flaremaxsize = (int)(WINDOW_WIDTH * fMaxSize);
		flarescale = (int)(WINDOW_WIDTH * fScale);

		// Destination is opposite side of centre from source
		dx = cx + (cx - lx);
		dy = cy + (cy - ly);

		// Render each element.
		for (i = 0; i < nPieces; ++i)
		{
			FlareElement* el = &element[i];

			// Position is interpolated along line between start and destination.
			px = (int)((1.0f - el->fDistance)*lx + el->fDistance*dx);
			py = (int)((1.0f - el->fDistance)*ly + el->fDistance*dy);

			// Piece size are 0 to 1; flare size is proportion of
			// screen width; scale by flaredist/maxflaredist.
			width = (int)((flaredist*flarescale*el->fSize) / maxflaredist);

			// Width gets clamped, to allows the off-axis flares
			// to keep a good size without letting the elements get
			// too big when centered.
			if (width > flaremaxsize)
			{
				width = flaremaxsize;
			}

			// Flare elements are square (round) so height is just
			// width scaled by aspect ratio.
			height = width;// *((double)WINDOW_HEIGHT / WINDOW_WIDTH);
			//float alpha = (flaredist*(el->argb >> 24)) / maxflaredist;
			float alpha = (float)flaredist / maxflaredist;

			if (width > 1)
			{
				//unsigned int    argb = (alpha << 24) | (el->argb & 0x00ffffff);
				unsigned int    argb = el->argb & 0x00ffffff;

				//drawQuad(px - width / 2, py - height / 2, width, height, element->texture, argb);
				material.getShader()->use();
				material.setTexture("texture0", el->texture);
				auto tint = glm::vec4(
					argb & 0x00FF0000 >> 16,
					argb & 0x0000FF00 >> 8,
					argb & 0x000000FF,
					alpha * 255.f) / 255.f;
				material.getShader()->setVec4("tint", tint);

				// bind/active uniform sampler/texture objects
				auto* samplers = material.getSamplerUniforms();
				for (auto it = samplers->begin(); it != samplers->end(); ++it)
				{
					it->second.texture->bind(it->second.unit);
				}

				material.getShader()->setMat4("viewProjectionMatrix", glm::ortho(0.f, float(WINDOW_WIDTH), 0.f, float(WINDOW_HEIGHT), -1.f, 1.f));
				material.getShader()->setMat4("modelMatrix",
					glm::scale(glm::translate(glm::identity<glm::mat4>(), glm::vec3(px, py, 0.f)), glm::vec3(width, height, 1.f)));

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, element[i].texture->id);

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
}