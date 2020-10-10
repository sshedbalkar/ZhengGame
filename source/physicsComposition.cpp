#include "physicsComposition.h"
#include "utility.h"
#include "physicalLogic.h"
#include "allPhysics.h"
#include "physics.h"

#include "composition.h"


std::map< std::string, PhysicsSerializer*> PhysicsComposition::serializer_map;
//==========================================
PhysicsComposition::PhysicsComposition() : Component( CT_PhysicsComposition )
{
}
//==========================================
PhysicsComposition::~PhysicsComposition()
{
	for ( unsigned int i = 0; i < physical_logics.size(); ++i )
		utility::Delete( physical_logics[i]);

	if ( owner ) owner->RemoveReference();
}
//==========================================
void PhysicsComposition::Serialize( Json::Value& root )
{
	for ( unsigned int i = 0; i < root.size(); ++i )
	{
	//serializer_map;
		PhysicalLogic* physics = serializer_map[root[i].asString()]->Create();
		physical_logics.push_back( physics );
	}
}
//==========================================
void PhysicsComposition::Initialize()
{
	for ( unsigned int i = 0; i < physical_logics.size(); ++i )
		physical_logics[i]->Initialize( owner );

	PHYSICS->AddPhysicsComposition( this );
	owner->AddReference();
}
//==========================================
void PhysicsComposition::Execute( int dt )
{
	for ( unsigned int i = 0; i < physical_logics.size(); ++i )
		physical_logics[i]->Execute( dt );
}
//==========================================
Component* PhysicsComposition::Clone()
{
	PhysicsComposition* new_physics_composition = new PhysicsComposition;
	for ( unsigned int i = 0; i < physical_logics.size(); ++i )
	{
		PhysicalLogic* new_logic = physical_logics[i]->Clone();
		new_physics_composition->physical_logics.push_back( new_logic );
	}
	return new_physics_composition;
}
//==========================================
void PhysicsComposition::AddPhysicsSerializer( std::string name, PhysicsSerializer* serializer )
{
	serializer_map[name] = serializer;
}
//==========================================
void PhysicsComposition::DeleteSerializers()
{
	std::map<std::string, PhysicsSerializer*>::iterator it;
	for ( it = serializer_map.begin(); it != serializer_map.end(); ++it )
		utility::Delete( it->second );
}

