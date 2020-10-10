#pragma once

#include <vector>
#include "component.h"
#include "utility.h"

class Composition
{
public:
	Composition( int _id = 0 ): id(_id),exists(true),reference_count(0) { };
	~Composition() 
	{ 
		for ( unsigned int i = 0; i < components.size(); ++i ) components[i]->Delete();
	};

	void AddComponent( Component* comp ) { comp->SetOwner( this );components.push_back(comp); }
	void Initialize() 
	{
		unsigned int i = 0;
		while (1)
		{
			components[i]->Initialize();
			++i;
			if ( i >= components.size() ) break;
		}
	}
	int GetID() { return id; };

	Component* GetComponent( ComponentType type ) 
	{
		for ( unsigned i = 0; i < components.size(); ++i ) if (components[i]->GetType() == type ) return components[i];
		return NULL;
	}

	bool Exists() { return exists; }
	void MarkToDelete() { exists = false; }
	void AddReference() { ++reference_count; }
	void RemoveReference() { --reference_count; }
	int Referenced() { return reference_count; }
private:
	int id;
	unsigned int reference_count;
	bool exists;
	std::vector<Component*> components;
};
