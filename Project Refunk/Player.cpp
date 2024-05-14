#include "Player.h"

Player::Player()
{
	pos = { 0, 0 };
	direction = 0;
	state = Standing;
	funkeyId = UB;
}

void Player::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

/// <summary>
/// Set the player's direction
/// </summary>
/// <param name="direction"> The direction of the player, 0 = south, 1 = southwest</param>
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
