#include "chaseThePlayer.h"
#include "composition.h"

#include "transform.h"
#include "steering.h"
#include "factory.h"

#define SLOW_RADIUS		3.0f

//======================================
ChaseThePlayer::ChaseThePlayer()
{
}
//======================================
ChaseThePlayer::~ChaseThePlayer()
{
}
//======================================
void ChaseThePlayer::Execute( int dt )
{
	float accel_x = player_pos->x - transform->position.x;
	accel_x /= abs(accel_x);
	accel_x *= steering->max_accel;

	float target_speed = steering->max_speed;
	float rate = abs( player_pos->y - transform->position.y ) / SLOW_RADIUS;
	if ( rate < 1.0f ) target_speed *= rate;

	float accel_y = player_pos->y - transform->position.y;
	accel_y /= abs(accel_y);
	accel_y *= target_speed;
	accel_y -= steering->velocity.y;

	steering->accel.x = accel_x;
	steering->accel.y = accel_y;
}
//======================================
void ChaseThePlayer::Initialize( Composition* owner )
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
	player_pos = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform ))->position);
}
