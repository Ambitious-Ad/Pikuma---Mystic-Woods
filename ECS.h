#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

///////////////////////////////////////////////////////////////////////////////////////
//Signature 
//
// We use a bitset (1s and 0s) to keep track of which components an entity has,
// and also helps to keep track of entities a given system is interested in.
///////////////////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

class Component
{
public:
	Component();
	~Component();

private:

};

Component::Component()
{
}

Component::~Component()
{
}

class Entity
{
public:
	Entity(int id) : id(id) {};
	~Entity();

	int GetId() const;

private:
	int id;
};

///////////////////////////////////////////////////////////////////////////////////////
// System 
///////////////////////////////////////////////////////////////////////////////////////
// The System processes entites that contain specific signature
///////////////////////////////////////////////////////////////////////////////////////

class System
{
public:
	System();
	~System();

	void AddEntityToSystem(Entity entity);
	void removeEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntities() const;
	Signature& GetComponentSignature() const;

	template <typename T> void RequireComponent();

private:
	Signature componentSignature;
	std::vector<Entity> entities;
};

System::System()
{
}

System::~System()
{
}

class Registry
{
public:
	Registry();
	~Registry();

private:

};

Registry::Registry()
{
}

Registry::~Registry()
{
}