#pragma once

#include "gameLogic.h"

class GlobalInputHandling : public GameLogic
{
public:
	GlobalInputHandling();
	~GlobalInputHandling();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new GlobalInputHandling(*this); }

private:
};
