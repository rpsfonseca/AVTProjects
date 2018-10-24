#pragma once

namespace AVTEngine
{
	struct GameState {
		int lives = 5;
		int points = 0;
		bool paused = false;
	};
}