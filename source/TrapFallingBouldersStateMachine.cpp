#include "TrapFallingBouldersStateMachine.h"
#include "composition.h"

#include "factory.h"

#define STATE_IDLE		0
#define STATE_ON_TRAP1	1
#define STATE_ON_TRAP2	2
#define STATE_ON_TRAP3	3

#define INTERVAL		180
#define INTERVAL2		120
#define DISTANCE		1.1f

//=============================================
TrapFallingBouldersStateMachine::TrapFallingBouldersStateMachine()
{
}
//=============================================
TrapFallingBouldersStateMachine::~TrapFallingBouldersStateMachine()
{
}
//=============================================
void TrapFallingBouldersStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;

	hero_position = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform )))->position;
	position = &(static_cast<Transform*>(owner->GetComponent( CT_Transform )))->position;

	state = STATE_IDLE;
	inner_state = OnEnter;
}
//=============================================
void TrapFallingBouldersStateMachine::Execute( int dt )
{
	if ( msg_id == MSG_RESET )
	{
		state = STATE_IDLE;
		inner_state = OnEnter;
		msg_id = MSG_NONE;
	}

	switch( state )
	{
	case STATE_IDLE:
		if ( hero_position->x > position->x ) 
		{
			state = STATE_ON_TRAP1;
		}
		break;

	case STATE_ON_TRAP1:
		switch( inner_state )
		{
		case OnEnter:
			timer = INTERVAL;
			counter = 0;
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			timer += dt;
			if ( timer >= INTERVAL )
			{
				Composition* boulder = FACTORY->NewObject( "boulder", position->x + counter * DISTANCE, 12.0f, 0.0f );
				timer = 0;
				++counter;
				if ( counter >= 10 ) inner_state = OnExit;
			}
			break;
		case OnExit:
			if ( hero_position->x > position->x + 18.0f )
			{
				state = STATE_ON_TRAP2;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_ON_TRAP2:
		switch( inner_state )
		{
		case OnEnter:
			timer = INTERVAL2;
			counter = 0;
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			timer += dt;
			if ( timer >= INTERVAL2 )
			{
				Composition* boulder = FACTORY->NewObject( "boulder", position->x + 18.0f + (6 - counter) * DISTANCE, 12.0f, 0.0f );
				timer = 0;
				++counter;
				if ( counter >= 8 ) inner_state = OnExit;
			}
			break;
		case OnExit:
			break;
		}
		break;

	case STATE_ON_TRAP3:
		switch( inner_state )
		{
		case OnEnter:
			timer = INTERVAL2;
			counter = 0;
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			timer += dt;
			if ( timer >= 150 )
			{
				Composition* boulder = FACTORY->NewObject( "boulder", position->x + 17.5f - (2 - counter) * DISTANCE, 12.0f, 0.0f );
				timer = 0;
				++counter;
				if ( counter >= 4 ) inner_state = OnExit;
			}
			break;
		case OnExit:
			state = STATE_ON_TRAP3;
			inner_state = OnEnter;
			break;
		}
		break;
	};
}
//=============================================
void TrapFallingBouldersStateMachine::ProceedMessage( const Message* m )
{
	msg_id = m->id;
}