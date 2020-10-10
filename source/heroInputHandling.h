#pragma once

#include "gameLogic.h"

class Transform;
class Steering;
class Body;

class HeroInputHandling : public GameLogic
{
public:
	HeroInputHandling();
	~HeroInputHandling();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new HeroInputHandling; }

private:
	bool enable;
	Transform* transform;
	Steering* steering;
	Body* body;
};
