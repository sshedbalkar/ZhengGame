#include "HeroStateMachine.h"
#include "factory.h"
#include "transform.h"
#include "composition.h"
#include "steering.h"

#include "core.h"
#include "input_messages.h"

#define STATE_IDLE				0
#define STATE_TAKE_HIT			1

//=======================================
HeroStateMachine::HeroStateMachine()
{
}
//=======================================
HeroStateMachine::~HeroStateMachine()
{
}
//=======================================
void HeroStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;
	state = STATE_IDLE;
	inner_state = OnEnter;
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	body = static_cast<Body*>(owner->GetComponent( CT_Body ));
}
//=======================================
void HeroStateMachine::Execute( int dt )
{
	if ( msg_id == MSG_RESET )
	{
		steering->velocity.x = 0.0f;
		steering->velocity.y = 0.0f;
		state = STATE_IDLE;
		inner_state = OnEnter;
		msg_id = MSG_NONE;

	}


	switch( state )
	{
	case STATE_IDLE:

		switch( inner_state )
		{
		case OnEnter:
			if ( body->CollideWith( COLLIDE_BOTTOM ) )
			{
				MessageControlEnable m( true );
				CORE->SendMessageToLogicType( &m, LT_Controller );
				inner_state = OnUpdate;
			}
			break;
		case OnUpdate:
			break;
		}		
		
		if ( msg_id == MSG_TAKE_HIT	|| ( transform->position.y < 0.5f ) )
		{
			state = STATE_TAKE_HIT;
			inner_state = OnEnter;
			msg_id = MSG_NONE;
		}
		break;

	case STATE_TAKE_HIT:
		switch( inner_state )
		{
		case OnEnter:
			{
				steering->velocity.x = 0.0f;
				steering->accel.x = 0.0f;
			
				MessageControlEnable m( false );
				CORE->SendMessageToLogicType( &m, LT_Controller );

				inner_state = OnUpdate;
				break;
			}
		case OnUpdate:
			{
				MessageReset m;
				inner_state = OnExit;
				CORE->SendMessageToLogicType( &m, LT_StateMachine );
				break;
			}
		case OnExit:
			break;
		}
		break;

	};
}
//=======================================
void HeroStateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
