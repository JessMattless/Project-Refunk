#include "Player.h"
#include "Util.h"

#include <SDL_image.h>

Player::Player(SDL_Renderer* renderer)
{
	pos = { 0, 0 };
	target = { 0, 0 };
	direction = 0;
	state = Standing;
	funkeyId = UB;

	movementStep = 1.5;

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = 0;
	rect.h = 0;

	this->renderer = renderer;

	surface = IMG_Load("../funkeys/UB.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Player::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	
	rect.x = x;
	rect.y = y;
}

/// <summary>
/// Set the player's direction
/// </summary>
/// <param name="direction"> the direction of the player, 0 = south, 1 = southwest</param>
void Player::setDirection(int direction)
{
	if (0 <= direction < 8) {
		this->direction = direction;
	}
	else throw std::invalid_argument("Direction must be between 0 and 8");
}

void Player::setState(State state)
{
	this->state = state;
}

void Player::setFunkeyId(FunkeyID funkeyId)
{
	this->funkeyId = funkeyId;
}

/// <summary>
/// Sets the target of the player, used for walking to the target
/// </summary>
void Player::setTarget(float x, float y)
{
	target.x = x - rect.w / 2;
	target.y = y - rect.h + 5;
}

position Player::getPos()
{
	return pos;
}

/// <returns>A direction between 0 and 8, south = 0, southwest = 1</returns>
int Player::getDirection()
{
	return direction;
}

State Player::getState()
{
	return state;
}

FunkeyID Player::getFunkeyId()
{
	return funkeyId;
}

float Player::getMovementStep()
{
	return movementStep;
}

position Player::getTarget()
{
	return target;
}

/// <summary>
/// Returns true if the player has reached their target x coordinate
/// </summary>
bool Player::hasReachedTargetX()
{
	if (pos.x == target.x) return true;
	return false;
}

/// <summary>
/// Returns true if the player has reached their target y coordinate
/// </summary>
bool Player::hasReachedTargetY()
{
	if (pos.y == target.y) return true;
	return false;
}


/// <summary>
/// Render the player to the screen
/// </summary>
/// <param name="renderer">the renderer to render the player to</param>
void Player::render(SDL_Renderer* renderer)
{

	rect.w = surface->w;
	rect.h = surface->h;

	SDL_RenderCopy(renderer, texture, NULL, &rect);

}

/// <summary>
/// Render the circular target that the player will walk to 
/// </summary>
void Player::renderTarget(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	util.drawCircle(renderer, target.x + rect.w / 2, target.y + rect.h - 5, 12);
}

void Player::moveByStep()
{
	position diff = { target.x - pos.x, target.y - pos.y };
	if (!hasReachedTargetX()) {
		float posDiff = (diff.x > 0) ? diff.x : -diff.x;
		if (posDiff < movementStep) setPos(pos.x + diff.x, pos.y);
		else {
			if (diff.x > 0) setPos(pos.x + movementStep, pos.y);
			else setPos(pos.x - movementStep, pos.y);
		}
	}
	if (!hasReachedTargetY()) {
		float posDiff = (diff.y > 0) ? diff.y : -diff.y;
		if (posDiff < movementStep) setPos(pos.x, pos.y + diff.y);
		else {
			if (diff.y > 0) setPos(pos.x, pos.y + movementStep);
			else setPos(pos.x, pos.y - movementStep);
		}
	}
}
