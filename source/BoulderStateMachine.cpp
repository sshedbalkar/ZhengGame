#include "BoulderStateMachine.h"
#include "composition.h"
#include "substance.h"

#include "other_messages.h"

#define STATE_IDLE		0
#define STATE_DESTRUCT	1

//==============================================
BoulderStateMachine::BoulderStateMachine()
{
}
//==============================================
BoulderStateMachine::~BoulderStateMachine()
{
}
//==============================================
void BoulderStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;
	state = STATE_IDLE;
	inner_state = OnEnter;
}
//==============================================
void BoulderStateMachine::Execute( int dt )
{
	static int timer = 0;

	switch( state )
	{
	case STATE_IDLE:
		if ( msg_id == MSG_DESTRUCT || msg_id == MSG_POST_ATTACKING ) 
		{
			state = STATE_DESTRUCT;
			inner_state = OnEnter;
			msg_id = MSG_NONE;
		}
		break;

	case STATE_DESTRUCT:
		switch( inner_state )
		{
		case OnEnter:
			{
				Substance* substance = static_cast<Substance*>(owner->GetComponent(CT_Substance));
				substance->ChangeSpriteTo("boulder_explode");
				inner_state = OnUpdate;
				break;
			}

		case OnUpdate:
			if ( msg_id == MSG_ANIMATION_END ) 
			{
				owner->MarkToDelete();
				inner_state = OnExit;
			}
			break;

		case OnExit:

			break;
		}
		break;

	};
	msg_id = MSG_NONE;
}
//==============================================
void BoulderStateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
