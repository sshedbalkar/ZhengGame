#pragma once

#include "gameLogic.h"

class Transform;
class Steering;
class Body;

class SwordAttackInputHandling : public GameLogic
{
public:
	SwordAttackInputHandling();
	~SwordAttackInputHandling();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new SwordAttackInputHandling; }

private:
	bool enable;
	Composition* owner;
};
