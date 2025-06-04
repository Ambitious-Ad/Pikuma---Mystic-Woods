#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent
{
protected:
	static int nextId;
};

template <typename T>
class Component: public BaseComponent
{	
	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

class Entity
{
public:
	Entity(int id) : id(id) {};
	~Entity() = default;

	int GetId() const;

private:
	int id;
};

class System
{
public:

	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void removeEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	template <typename TComponent> void RequireComponent();

private:
	Signature componentSignature;
	std::vector<Entity> entities;
};

class Registry
{
public:


private:

};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}