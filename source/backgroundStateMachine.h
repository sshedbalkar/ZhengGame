#include "stateMachine.h"

class Substance;

class BackgroundStateMachine : public StateMachine
{
public:
	BackgroundStateMachine();
	~BackgroundStateMachine();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new BackgroundStateMachine; }

private:
	Vector3* hero_position;
	Substance* substance;
	Substance* handle;

	int timer;
	int counter;
};
