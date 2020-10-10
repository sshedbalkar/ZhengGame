#pragma once

#include "stateMachine.h"

class Transform;

class SwordStateMachine : public StateMachine
{
public:
	SwordStateMachine();
	~SwordStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new SwordStateMachine;}

private:
	Transform* hero;
	Transform* transform;
	int timer;
	float dx;
	float offset_x;
};
