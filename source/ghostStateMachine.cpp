#include "GhostStateMachine.h"
#include "factory.h"
#include "composition.h"
#include "transform.h"
#include "steering.h"

#include "core.h"
#include "message.h"

#define STATE_IDLE				0
#define STATE_RETURN			1
#define STATE_CHASE				2
#define STATE_TAKE_HIT			3

#define DETECTION_RANGE			8.0f

//=======================================
GhostStateMachine::GhostStateMachine()
{
}
//=======================================
GhostStateMachine::~GhostStateMachine()
{
}
//=======================================
void GhostStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;
	state = STATE_IDLE;
	inner_state = OnEnter;
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	hero_position = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform )))->position;
	initial_x = transform->position.x;
	initial_y = transform->position.y;

}
//=======================================
void GhostStateMachine::Execute( int dt )
{
	if ( msg_id == MSG_RESET )
	{
		state = STATE_IDLE;
		inner_state = OnEnter;
		msg_id = MSG_NONE;

		transform->position.x = initial_x;
		transform->position.y = initial_y;

	}
	if ( hero_position->x > 115.0f )
	{
		ChaseTarget( initial_x, initial_y );
		return;
	}
	if ( msg_id == MSG_TAKE_HIT )
	{
		state = STATE_TAKE_HIT;
		inner_state = OnEnter;
	}


	switch( state )
	{
	case STATE_IDLE:
		switch( inner_state )
		{
		case OnEnter:
			steering->accel.x = 0.0f;
			steering->accel.y = 0.0f;
			steering->velocity.x = 0.0f;
			steering->velocity.y = 0.0f;
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			if ( abs( hero_position->x - transform->position.x ) < DETECTION_RANGE )
			{
				state = STATE_CHASE;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_CHASE:
		switch( inner_state )
		{
		case OnEnter:
			inner_state = OnUpdate;
			break;

		case OnUpdate:
			ChaseTarget( hero_position->x, hero_position->y );
			if ( abs(transform->position.x - hero_position->x) > DETECTION_RANGE )
			{
				state = STATE_RETURN;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_RETURN:
		switch( inner_state )
		{
		case OnEnter:
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			ChaseTarget( initial_x, initial_y );
			if ( abs(transform->position.x - initial_x) < 0.5f )
			{
				state = STATE_IDLE;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_TAKE_HIT:
		switch( inner_state )
		{
		case OnEnter:
			{
				float dir = transform->position.x - hero_position->x;
				dir = dir < 0 ? -1.0f : 1.0f;
				transform->position.x += dir * 5.0f;
				transform->position.y += 2.0f;
				state = STATE_IDLE;
				break;
			}
		case OnUpdate:

		case OnExit:
			break;
		}
		break;

	};
	msg_id = MSG_NONE;
}
//=======================================
void GhostStateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
//=======================================
void GhostStateMachine::ChaseTarget( float x, float y )
{
	float accel_x = x - transform->position.x;
	accel_x /= abs(accel_x);
	accel_x *= steering->max_accel;

	float target_speed = steering->max_speed;
	float rate = abs( y - transform->position.y ) / 3.0f;
	if ( rate < 1.0f ) target_speed *= rate;

	float accel_y = y - transform->position.y;
	accel_y /= abs(accel_y);
	accel_y *= target_speed;
	accel_y -= steering->velocity.y;

	steering->accel.x = accel_x;
	steering->accel.y = accel_y;
}
