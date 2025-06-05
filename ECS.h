#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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

	bool operator ==(const Entity& other) const { return id == other.id; };

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

class IPool
{
public:

	virtual ~IPool() {}

};

template <typename T>
class Pool: public IPool
{
public:
	
	Pool(int size = 100)
	{
		data.reserve(size);
	}

	virtual ~Pool() = default;

	bool isEmpty() const
	{
		return data.empty();
	}

	int GetSize() const
	{
		return data.size();
	}

	void Resize(int n)
	{
		data.resize(n);
	}

	void Clear()
	{
		data.clear();
	}

	void Add(T object)
	{
		data.push_back(object);
	}

	void Set(int index, T object)
	{
		data[index] = object;
	}

	T& Get(int index)
	{
		return static_cast<T&>(data[index]);
	}

	T& operator [](unsigned int index)
	{
		return data[index];
	}

private:
	std::vector<T> data;
};

class Registry
{
public:
	
	Registry() = default;

	void Update();

	Entity CreateEntity();



	void AddEntityToSystem(Entity entity);
	


private:
	int numEntites = 0;
	std::vector<IPool*> componentPools;
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, System*> system;

	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;
};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}