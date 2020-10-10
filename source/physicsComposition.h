#pragma once

#include "component.h"
#include "physicalLogic.h"

class PhysicsComposition : public Component
{
public:
	PhysicsComposition();
	virtual ~PhysicsComposition();

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();
	virtual Component* Clone();

	void Execute( int dt );
	static void DeleteSerializers();
	static void AddPhysicsSerializer( std::string name, PhysicsSerializer* serializer );

private:
	std::vector< PhysicalLogic* > physical_logics;
	static std::map< std::string, PhysicsSerializer*> serializer_map;
	
};
