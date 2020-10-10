#pragma once

#include "stateMachine.h"

class Steering;
class Transform;

class GhostStateMachine : public StateMachine
{
public:
	GhostStateMachine();
	~GhostStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new GhostStateMachine; }

private:
	Steering* steering;
	Transform* transform;
	Vector3* hero_position;

	float initial_x;
	float initial_y;

	void ChaseTarget( float x, float y );
};
