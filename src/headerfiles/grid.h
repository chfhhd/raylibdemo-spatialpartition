#pragma once

#include "header.h"
#include "entity.h"

class Grid {
public:
	
	Grid();

	static const int NUM_CELLS = 1;			// 1| 10 | 20 | 40
	static const int CELL_SIZE = 1080;		// 1080 | 108 | 54 | 27

	void add(Entity* entity);
	void handleCollision();
	void handleCell(int x, int y);
	void handleEntity(Entity* entity, Entity* other);
	void move(Entity* entity);

	void setCollisionInstructions(int instructions);
	int getCollisionInstructions();

private:

	Entity* cells[NUM_CELLS][NUM_CELLS];
	long long unsigned int number_of_collision_instructions = 0;

protected:

	

};