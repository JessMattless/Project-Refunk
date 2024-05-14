#pragma once

#include <SDL.h>
#include <map>
#include <vector>

static class Mouse
{
private:
	int activeCursor = 0;
	std::vector<SDL_Surface*> cursorList;

public:

	std::map<int, bool> button;
	std::pair<int, int> position;
	std::pair<int, int> motion;
	float wheel = 0;

	Mouse();

	void setPos(int xPos, int yPos);
	void setMotion(int xMotion, int yMotion);

	SDL_Surface* getActiveCursor();

	bool checkCursorPos(float xPosStart, float xPosEnd, float yPosStart, float yPosEnd);

} mouse;