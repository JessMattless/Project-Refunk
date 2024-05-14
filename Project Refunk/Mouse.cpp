#include "Mouse.h"
#include <SDL_image.h>

Mouse::Mouse()
{
	cursorList.push_back(IMG_Load("../misc/cursors/Cursor.bmp"));
	cursorList.push_back(IMG_Load("../misc/cursors/Cursor_Active.bmp"));
}

void Mouse::setPos(int xPos, int yPos)
{
	position.first = xPos;
	position.second = yPos;
}

void Mouse::setMotion(int xMotion, int yMotion)
{
	motion.first = xMotion;
	motion.second = yMotion;
}

/// <returns>The surface of the active cursor</returns>
SDL_Surface* Mouse::getActiveCursor()
{
	return cursorList[activeCursor];
}

/// <summary>
/// Check whether the mouse cursor is within a given area
/// </summary>
/// <returns>True is the mouse is within the area, and false otherwise</returns>
bool Mouse::checkCursorPos(float xPosStart, float xPosEnd, float yPosStart, float yPosEnd)
{
	if (position.first >= xPosStart && position.first <= xPosEnd
		&& position.second >= yPosStart && position.second <= yPosEnd) {
		return true;
	}
	return false;
}
