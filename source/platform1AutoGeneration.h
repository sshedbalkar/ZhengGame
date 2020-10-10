#pragma once

#include "gameLogic.h"

class Platform1AutoGeneration : public GameLogic
{
public:
	Platform1AutoGeneration();
	~Platform1AutoGeneration();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new Platform1AutoGeneration(*this); }

private:

};
