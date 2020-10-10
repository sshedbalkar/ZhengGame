#include "stateMachine.h"

class Substance;
class Dialogs;

class ShowDialogs : public StateMachine
{
public:
	ShowDialogs();
	~ShowDialogs();

	virtual void Execute( int dt );
	virtual void Initialize( Composition* owner );
	
	virtual void ProceedMessage( const Message* msg );

	virtual GameLogic* Clone() { return new ShowDialogs; }

private:
	Substance* substance;
	Dialogs* dialogs_info;	
	Vector3* hero_position;
	Transform* transform;

	int inner_inner_state;

};
