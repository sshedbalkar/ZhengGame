#include "archetype.h"
#include "utility.h"
#include "component.h"
#include "composition.h"

//===========================================
Archetype::~Archetype()
{
	for ( unsigned int i = 0; i < components.size();++i )
	{
//		printf("	%i\n", components[i]->GetType());
		components[i]->Delete();
	}
}
//===========================================
Composition* Archetype::Instantiate()
{
	Composition* obj = new Composition();
	Component* comp;
	for ( unsigned int i = 0; i < components.size(); ++i )
	{
		comp = components[i]->Clone();
		comp->SetOwner( obj );
		obj->AddComponent( comp );
	}
	return obj;
}
//===========================================
void Archetype::AddComponent( Component* comp )
{
	components.push_back( comp );
}