#pragma once

#include <SDL.h>

static struct Util
{
public:
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;

	void drawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius);
} util;

