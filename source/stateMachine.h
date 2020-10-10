#pragma once

#include "gameLogic.h"
#include "message.h"

class StateMachine : public GameLogic
{
public:
	enum InnerState
	{
		OnEnter,
		OnUpdate,
		OnExit
	};
	StateMachine() { logic_type = LT_StateMachine; };
	virtual ~StateMachine() { };

	virtual void Execute( int dt ) = 0;
	virtual void Initialize( Composition* owner ) = 0;
	
	virtual void ProceedMessage( const Message* msg ) = 0;

	virtual GameLogic* Clone() = 0;

protected:
	int state;
	InnerState inner_state;
	Composition* owner;
	MessageID msg_id;
};
