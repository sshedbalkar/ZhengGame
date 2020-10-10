#pragma once

#include "stateMachine.h"


class TrapFallingBouldersStateMachine : public StateMachine
{
public:

	TrapFallingBouldersStateMachine();
	~TrapFallingBouldersStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* _owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new TrapFallingBouldersStateMachine(); }

private:
	Composition* owner;
	Vector3* position;
	Vector3* hero_position;
	
	int timer;
	int counter;
};
