#pragma once

#include <SDL.h>
#include "Player.h"

class App {
private:
	bool _running;
	bool _fullscreen;

	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

public:

	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;

	Player* player;

	App(); // Used as our init function

	int onExecute();

	void onEvent(SDL_Event* event);

	void onLoop();

	void onRender();

	void onCleanup();
};