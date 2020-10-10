#pragma once

#include "gameLogic.h"

class BounceTwiceAndSelfDestruct : public GameLogic
{
public:
	BounceTwiceAndSelfDestruct();
	~BounceTwiceAndSelfDestruct();

	virtual void Execute( int dt ) {};
	virtual void Initialize( Composition* _owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new BounceTwiceAndSelfDestruct; }

private:
	int bouncing_count;
	Composition* owner;
	Transform* transform;
	Steering* steering;
};
