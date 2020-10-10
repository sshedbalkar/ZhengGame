#pragma once

#include "gameLogic.h"

class WaterAutoGeneration : public GameLogic
{
public:
	WaterAutoGeneration();
	~WaterAutoGeneration();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new WaterAutoGeneration(*this); }

private:

};
