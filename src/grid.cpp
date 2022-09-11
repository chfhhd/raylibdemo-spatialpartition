#include "headerfiles/grid.h"

Grid::Grid() {
	// Clear the grid
	for (int x = 0; x < this->NUM_CELLS; x++) {
		for (int y = 0; y < this->NUM_CELLS; y++) {
			this->cells[x][y] = nullptr;
		}
	}

}

void Grid::add(Entity* entity) {
	// Determine which grid cell it's in.
	int cell_x = (int)(entity->position.x / this->CELL_SIZE);
	int cell_y = (int)(entity->position.y / this->CELL_SIZE);

	// Add to the front of list for the cell it's in.
	entity->previous = nullptr;
	entity->next = this->cells[cell_x][cell_y];
	this->cells[cell_x][cell_y] = entity;

	if (entity->next != nullptr) {
		entity->next->previous = entity;
	}
}

void Grid::handleCollision() {
	for (int x = 0; x < this->NUM_CELLS; x++) {
		for (int y = 0; y < this->NUM_CELLS; y++) {
			handleCell(x, y);
		}
	}
}

void Grid::handleCell(int x, int y) {
	Entity* entity = this->cells[x][y];
	while (entity != nullptr) {
		// Handle other units in this cell.
		handleEntity(entity, entity->next);

		// Also try the neighboring cells.
		if (x > 0 && y > 0) handleEntity(entity, this->cells[x - 1][y - 1]);
		if (x > 0) handleEntity(entity, this->cells[x - 1][y]);
		if (y > 0) handleEntity(entity, this->cells[x][y - 1]);
		if (x > 0 && y < this->NUM_CELLS - 1) {
			handleEntity(entity, this->cells[x - 1][y + 1]);
		}
		entity = entity->next;
	}
}

void Grid::handleEntity(Entity* entity, Entity* other) {
	while (other != nullptr) {
		if (CheckCollisionCircles(entity->position, 6.0f, other->position, 6.0f)) {
			float speed_x = GetRandomValue(-2, 2);
			float speed_y = GetRandomValue(-2, 2);
			entity->speed.x = speed_x;
			entity->speed.y = speed_y;
			other->speed.x = -(speed_x);
			other->speed.y = -(speed_y);
		}
		this->number_of_collision_instructions++;
		other = other->next;
	}
}

void Grid::move(Entity* entity) {
	// See which cell it was in.
	int old_cell_x = (int)(entity->position.x / this->CELL_SIZE);
	int old_cell_y = (int)(entity->position.y / this->CELL_SIZE);

	// See which cell it's moving to.
	int cell_x = (int)((entity->position.x + entity->speed.x) / this->CELL_SIZE);
	int cell_y = (int)((entity->position.y + entity->speed.y) / this->CELL_SIZE);

	// Change direction if it is at the Screen width/height.
	if (entity->position.x >= GetScreenWidth() - 3) {
		entity->position.x -= 3;
		entity->speed.x = -(entity->speed.x);
	} 
	else if (entity->position.x <= 3) {
		entity->position.x += 3;
		entity->speed.x = -(entity->speed.x);
	}

	if (entity->position.y >= GetScreenHeight() - 3) {
		entity->position.y -= 3;
		entity->speed.y = -(entity->speed.y);
	}
	else if (entity->position.y <= 3) {
		entity->position.y += 3;
		entity->speed.y = -(entity->speed.y);
	}

	entity->position.x = entity->position.x + entity->speed.x;
	entity->position.y = entity->position.y + entity->speed.y;

	// If it didn't change cells, we're done.
	if (old_cell_x == cell_x && old_cell_y == cell_y) {
		return;
	}

	// Unlink it from the list of its old cell.
	if (entity->previous != nullptr) {
		entity->previous->next = entity->next;
	}

	if (entity->next != nullptr) {
		entity->next->previous = entity->previous;
	}

	// If it's the head of a list, remove it.
	if (this->cells[old_cell_x][old_cell_y] == entity) {
		this->cells[old_cell_x][old_cell_y] = entity->next;
	}

	// Add it back to the grid at its new cell.
	add(entity);
}

void Grid::setCollisionInstructions(int instructions) {
	this->number_of_collision_instructions = instructions;
}

int Grid::getCollisionInstructions() {
	return this->number_of_collision_instructions;
}