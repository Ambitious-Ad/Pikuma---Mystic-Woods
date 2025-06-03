#include "ECS.h"
	
Entity::Entity(int id) : id(id) {}
	
Entity::~Entity() {}
	
int Entity::GetId() const
{
	return id;
}