#pragma once

#include "gameLogic.h"

class PlatformAutoGeneration : public GameLogic
{
public:
	PlatformAutoGeneration();
	~PlatformAutoGeneration();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new PlatformAutoGeneration(*this); }

private:

};
