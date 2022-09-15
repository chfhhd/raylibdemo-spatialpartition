#pragma once

#include "header.h"

class Grid;

class Entity {

	friend class Grid;

public:

	Entity(Grid* grid, Vector2 position);

	void move();
	Vector2 getPosition();

private:

	Vector2 speed;
	Vector2 position;
	Grid* grid;

	Entity* previous;
	Entity* next;

protected:

	

};