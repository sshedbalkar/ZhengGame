#pragma once

#include "stateMachine.h"

class Substance;
class Body;
class Steering;

class HeroAnimations : public StateMachine
{
public:
	HeroAnimations();
	~HeroAnimations();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	virtual void ProceedMessage( const Message* msg );
	virtual GameLogic* Clone() { return new HeroAnimations; }

private:
	Substance* body;
	Substance* legs;
	Substance* face;
	Substance* front_eye;
	Substance* back_eye;
	Substance* hair;

	Body* collision_body;
	Steering* steering;
	Vector3* hero_position;

	int counter;
};