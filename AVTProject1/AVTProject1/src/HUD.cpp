#include "HUD.h"
#include "Application.h"

void AVTEngine::HUD::draw() {
	auto& gameState = Application::getInstance()->getGameState();
	font.DrawString(0, 0, "Lives: " + std::to_string(gameState.lives) + " Points: " + std::to_string(gameState.points));
}