#pragma once

#include "physicalLogic.h"

class Body;
class Transform;
class Steering;

class CollisionTest : public PhysicalLogic
{
public:
	CollisionTest();
	virtual ~CollisionTest();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual PhysicalLogic* Clone() { return new CollisionTest();}

private:
	Body* body;
};
