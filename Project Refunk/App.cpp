#include "App.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <SDL_image.h>

App::App() {
	_running = true;
	_fullscreen = false;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Project Refunk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	player = new Player();

	onExecute();
}

int App::onExecute()
{
	float timeA, timeB = 0;

	SDL_Event event;
	while (_running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		timeA = SDL_GetTicks();
		float deltaTime = timeA - timeB;
		if (deltaTime > 1000 / 20.0) {
			timeB = timeA;
			onLoop();
			onRender();
		}
	}

	onCleanup();
	return 0;
}

void App::onEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_QUIT:
		_running = false; break;
	case SDL_MOUSEBUTTONDOWN:
		mouse.button[event->button.button] = true; break;
	case SDL_MOUSEBUTTONUP:
		mouse.button[event->button.button] = false; break;
	case SDL_MOUSEMOTION:
		mouse.setPos(event->motion.x, event->motion.y);
		mouse.setMotion(event->motion.xrel, event->motion.yrel);
		break;
	case SDL_MOUSEWHEEL:
		mouse.wheel = event->wheel.preciseY; break;
	case SDL_KEYDOWN:
		if (event->key.repeat == 0) keyboard.key[event->key.keysym.sym] = true; break;
	case SDL_KEYUP:
		keyboard.key[event->key.keysym.sym] = false; break;
	}
}

void App::onLoop()
{
	SDL_Cursor* cursor = SDL_CreateColorCursor(mouse.getActiveCursor(), 0, 0);

	if (keyboard.key[SDLK_F11] && !_fullscreen) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		_fullscreen = true; keyboard.key[SDLK_F11] = false;
	}
	else if (keyboard.key[SDLK_F11] && _fullscreen) {
		SDL_SetWindowFullscreen(window, 0);
		_fullscreen = false; keyboard.key[SDLK_F11] = false;
	}
	
	SDL_SetCursor(cursor);
}

void App::onRender()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void App::onCleanup()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	App app;

	return app.onExecute();
}