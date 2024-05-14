#pragma once

#include <stdexcept>

enum State {Standing, Walking, Teleporting, Falling};
enum FunkeyID {UB};

struct position {
	float x, y;
};

class Player
{
private:
	position pos;
	int direction;
	State state;
	FunkeyID funkeyId;

public:
	Player();

	void setPos(float x, float y);
	void setDirection(int direction);
	void setState(State state);
	void setFunkeyId(FunkeyID funkeyId);

	position getPos();
	int getDirection();
	State getState();
	FunkeyID getFunkeyId();
};

