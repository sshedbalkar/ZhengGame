#pragma once

#include "gameLogic.h"

class Transform;
class Steering;
class Body;

class TitleScreen : public GameLogic
{
public:
	TitleScreen();
	~TitleScreen();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new TitleScreen; }

private:
	bool enable;
	Composition* owner;
};
