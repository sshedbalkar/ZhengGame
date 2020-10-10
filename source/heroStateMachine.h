#pragma once

#include "stateMachine.h"

class Steering;
class Body;

class HeroStateMachine : public StateMachine
{
public:
	HeroStateMachine();
	~HeroStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new HeroStateMachine; }

private:
	Steering* steering;
	Transform* transform;
	Body* body;
};
