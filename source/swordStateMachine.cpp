#include "SwordStateMachine.h"
#include "factory.h"
#include "transform.h"
#include "composition.h"

#define STATE_IDLE		0
#define STATE_SWING		1

//=======================================
SwordStateMachine::SwordStateMachine()
{
}
//=======================================
SwordStateMachine::~SwordStateMachine()
{
}
//=======================================
void SwordStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;

	hero = static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform ));
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));

	state = STATE_IDLE;
	inner_state = OnEnter;
}
//=======================================
void SwordStateMachine::Execute( int dt )
{

	switch( state )
	{
	case STATE_IDLE:
		transform->width = 0.0f;
		transform->height = 0.0f;
		transform->position.y = hero->position.y-50.0f;
		transform->position.x = hero->position.x;
		if ( msg_id == MSG_ACTIVATE )
		{
			state = STATE_SWING;
			transform->position.y = hero->position.y + 0.2f;
			transform->position.x = hero->GetXInFront( 1.0f );
			inner_state = OnEnter;
		}
		break;

	case STATE_SWING:
		switch ( inner_state )
		{
		case OnEnter:
			timer = 0;
			inner_state = OnUpdate;
			transform->width = 1.0f;
			transform->height = 1.0f;
			transform->facing = hero->facing;
			offset_x = transform->position.x - hero->position.x;
			transform->position.x += 0.5f * offset_x / abs(offset_x );
			dx = 0.02f;
			break;

		case OnUpdate:
			transform->position.x = hero->position.x;
			transform->position.x += offset_x;
			transform->position.x += transform->width/2.0f * offset_x / abs(offset_x );
			transform->position.y = hero->position.y + 0.2f;
			transform->width += dx*(float)dt;
			if ( timer > 100 ) dx = 0.0f;
			timer += dt;
			if ( timer > 300 ) inner_state = OnExit;
			break;

		case OnExit:
			state = STATE_IDLE;
			inner_state = OnEnter;
			break;
		}
		break;
	};

	msg_id = MSG_NONE;
}
//=======================================
void SwordStateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
