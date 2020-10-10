#pragma once

class Composition;
class Component;
#include <vector>

class Archetype
{
public:
	Archetype() {};
	~Archetype();

	Composition* Instantiate();
	void AddComponent( Component* comp );

private:
	std::vector<Component*> components;
};
