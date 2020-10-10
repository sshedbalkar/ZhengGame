#include "level0StateMachine.h"
#include "factory.h"
#include "transform.h"
#include "steering.h"
#include "composition.h"

#include "input_messages.h"
#include "core.h"

#define STATE_IDLE		0
#define STATE_ENDGAME	99


#define ENDGAME_POINTA	115.0f
#define ENDGAME_POINTB	123.0f

//=======================================
Level0StateMachine::Level0StateMachine()
{
}
//=======================================
Level0StateMachine::~Level0StateMachine()
{
}
//=======================================
void Level0StateMachine::Initialize( Composition* )
{
	hero = static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform ));
	hero_steering = static_cast<Steering*>(FACTORY->GetHeroHandle()->GetComponent( CT_Steering ));

	last_checkpoint_x = hero->position.x;
	last_checkpoint_y = hero->position.y;
	
	state = STATE_IDLE;
	inner_state = OnEnter;
}
//=======================================
void Level0StateMachine::Execute( int dt )
{
	CheckPointSet();
//	printf("%0.3f\n",hero->position.x );

	if ( msg_id == MSG_RESET ) 
	{
		hero->position.x = last_checkpoint_x;
		hero->position.y = last_checkpoint_y;
		msg_id = MSG_NONE;
	}

	switch( state )
	{
	case STATE_IDLE:
		if ( hero->position.x > ENDGAME_POINTA )
		{
			state = STATE_ENDGAME;
			inner_state = OnEnter;
		}

		break;

	case STATE_ENDGAME:

		switch( inner_state )
		{
		case OnEnter:
			{
				MessageControlEnable m( false );
				CORE->SendMessageToLogicType( &m, LT_Controller );
				inner_state = OnUpdate;
				break;
			}

		case OnUpdate:
			hero_steering->velocity.x = 2.0f;
			if ( hero->position.x > ENDGAME_POINTB ) inner_state = OnExit;
			break;

		case OnExit:
			hero_steering->velocity.x = 0.0f;
			hero->position.x = ENDGAME_POINTB;
			break;
		}
		break;
	}
}
//=======================================
void Level0StateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
//=======================================
void Level0StateMachine::CheckPointSet()
{
	if ( hero->position.x > 86.0f )
	{
		last_checkpoint_x = 86.0f;
		last_checkpoint_y = 6.0f;
	}
	else if ( hero->position.x > 40.0f ) 
	{
		last_checkpoint_x = 40.0f;
		last_checkpoint_y = 6.0f;
	}
}
