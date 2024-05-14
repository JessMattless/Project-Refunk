#include "App.h"
#include "Util.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <SDL_image.h>
#include <cmath>

App::App() {
	_running = true;
	_fullscreen = false;

	SDL_Init(SDL_INIT_VIDEO);
	util.window = SDL_CreateWindow("Project Refunk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	util.renderer = SDL_CreateRenderer(util.window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	util.texture = SDL_CreateTexture(util.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetWindowMinimumSize(util.window, WINDOW_WIDTH, WINDOW_HEIGHT);

	player = new Player(util.renderer);

	onExecute();
}

int App::onExecute()
{
	uint32_t timeA, timeB = 0;

	SDL_Event event;
	while (_running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		timeA = SDL_GetTicks();
		uint32_t deltaTime = timeA - timeB;
		if (deltaTime > 1000 / 60.0) {
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

	//Press F11 to toggle fullscreen
	if (keyboard.key[SDLK_F11] && !_fullscreen) {
		SDL_SetWindowFullscreen(util.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		_fullscreen = true; keyboard.key[SDLK_F11] = false;
	}
	else if (keyboard.key[SDLK_F11] && _fullscreen) {
		SDL_SetWindowFullscreen(util.window, 0);
		_fullscreen = false; keyboard.key[SDLK_F11] = false;
	}

	// Click to set a target that triggers the player moving
	if (mouse.button[SDL_BUTTON_LEFT]) {
		player->setTarget(mouse.position.first, mouse.position.second);
		mouse.button[SDL_BUTTON_LEFT] = false;
	}

	player->moveByStep();

	SDL_SetCursor(cursor);
}

void App::onRender()
{
	SDL_SetRenderDrawColor(util.renderer, 0, 0, 0, 255);
	SDL_RenderClear(util.renderer);

	if (!player->hasReachedTargetX() || !player->hasReachedTargetY()) {
		player->renderTarget(util.renderer);
	}

	player->render(util.renderer);

	SDL_RenderPresent(util.renderer);
}

void App::onCleanup()
{
	SDL_DestroyTexture(util.texture);
	SDL_DestroyRenderer(util.renderer);

	SDL_DestroyWindow(util.window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	App app;

	return app.onExecute();
}