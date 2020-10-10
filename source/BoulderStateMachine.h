#pragma once

#include "stateMachine.h"

class BoulderStateMachine : public StateMachine
{
public:
	BoulderStateMachine();
	~BoulderStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new BoulderStateMachine; }

private:

};
