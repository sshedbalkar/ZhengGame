#pragma once

#include "gameLogic.h"

class BringDamage : public GameLogic
{
public:
	BringDamage();
	~BringDamage();
		
	virtual void Execute( int dt ) {};
	virtual void Initialize( Composition* _owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new BringDamage; }

private:
	Composition* owner;
};
