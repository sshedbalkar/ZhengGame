#pragma once

#include "gameLogic.h"

class SnapFromTerrain : public GameLogic
{
public:
	SnapFromTerrain();
	~SnapFromTerrain();

	virtual void Execute( int dt ) {};
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new SnapFromTerrain; }

private:
	Transform* transform;
	Steering* steering;

};
