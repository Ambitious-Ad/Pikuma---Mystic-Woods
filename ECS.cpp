#include "ECS.h"
#include <vector>

int Entity::GetId() const
{
	return id;
}

void System::AddEntityToSystem(Entity entity)
{
	entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity entity)
{
	entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
		return entity == other;
		}), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}

Entity Registry::CreateEntity()
{
	int entityId;

	entityId = numEntites++;

	Entity entity(entityId);
	entitiesToBeAdded.insert(entity);
	return entity;
}

void Registry::Update()
{

}