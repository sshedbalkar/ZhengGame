#pragma once

#include "stateMachine.h"

class Transform;
class Steering;

class Level0StateMachine : public StateMachine
{
public:
	Level0StateMachine();
	~Level0StateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new Level0StateMachine;}

private:
	Transform* hero;
	Steering* hero_steering;
	float last_checkpoint_x, last_checkpoint_y;

	void CheckPointSet();
};
