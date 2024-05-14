#pragma once

#include <SDL.h>

static struct Util
{
public:
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;

	void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
} util;

