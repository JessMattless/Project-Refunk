#pragma once

#include <SDL.h>
#include <map>
#include <vector>

static class Mouse
{
private:
	std::vector<SDL_Surface*> cursorList;

public:
	int activeCursor = 0;

	std::map<int, bool> button;
	std::pair<float, float> position;
	std::pair<float, float> motion;
	float wheel = 0;

	Mouse();

	void setPos(float xPos, float yPos);
	void setMotion(float xMotion, float yMotion);

	SDL_Surface* getActiveCursor();

	bool checkCursorPos(float xPosStart, float xPosEnd, float yPosStart, float yPosEnd);

} mouse;