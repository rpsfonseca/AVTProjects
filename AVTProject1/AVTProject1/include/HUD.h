#pragma once

#include "TextureMappedFont.h"
#include "ResourcesManager.h"

namespace AVTEngine
{
	class HUD {
		Shader* fontShader = ResourcesManager::loadShader("fontShader");
		TextureMappedFont font = TextureMappedFont("font.bmp", *fontShader);

	public:
		void draw() {
			font.DrawString(0, 0, "Text");
		}
	};
}