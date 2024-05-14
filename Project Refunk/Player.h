#pragma once

#include <stdexcept>
#include <SDL.h>

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

	position target;
	float movementStep;

	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_Surface* surface;

	SDL_Renderer* renderer;

public:
	int targetCounter = 0;

	Player(SDL_Renderer* renderer);

	void setPos(float x, float y);
	void setDirection(int direction);
	void setState(State state);
	void setFunkeyId(FunkeyID funkeyId);
	void setTarget(int x, int y);

	position getPos();
	int getDirection();
	State getState();
	FunkeyID getFunkeyId();
	float getMovementStep();
	position getTarget();

	bool hasReachedTargetX();
	bool hasReachedTargetY();

	void render(SDL_Renderer* renderer);
	void renderTarget(SDL_Renderer* renderer);
	void moveByStep();
};

