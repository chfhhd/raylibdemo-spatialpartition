#include "headerfiles/entity.h"
#include "headerfiles/grid.h"

Entity::Entity(Grid* grid, Vector2 position) : grid(grid), position(position), previous(nullptr), next(nullptr) {
	this->speed.x = GetRandomValue(-2, 2);
	this->speed.y = GetRandomValue(-2, 2);
	grid->add(this);
}

void Entity::move() {
	grid->move(this);
}

Vector2 Entity::getPosition() {
	return this->position;
}