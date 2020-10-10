#pragma once

#include "physicalLogic.h"

class Steering;

class GravityAffected : public PhysicalLogic
{
public:
	GravityAffected();
	virtual ~GravityAffected();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual PhysicalLogic* Clone() { return new GravityAffected();}

private:
	Steering* steering;
};
