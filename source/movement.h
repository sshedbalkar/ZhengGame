#pragma once

#include "physicalLogic.h"

class Transform;
class Steering;
class Body;

class Movement : public PhysicalLogic
{
public:
	Movement();
	virtual ~Movement();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual PhysicalLogic* Clone() { return new Movement();}

private:
	Transform* transform;
	Steering* steering;
	Body* body;
};
