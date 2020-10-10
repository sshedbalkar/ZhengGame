#pragma once

#include "physicalLogic.h"
#include "math.h"

class Transform;
class Steering;

class ChaseThePlayer : public PhysicalLogic
{
public:
	ChaseThePlayer();
	virtual ~ChaseThePlayer();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual PhysicalLogic* Clone() { return new ChaseThePlayer();}

private:
	Transform* transform;
	Steering* steering;
	Vector3* player_pos;
};
