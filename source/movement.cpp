#include "movement.h"
#include "composition.h"

#include "transform.h"
#include "steering.h"
#include "body.h"

#define STATIC_FRICTION		5.0f
///max speed ~= acceleration / static_friction

//======================================
Movement::Movement()
{
}
//======================================
Movement::~Movement()
{
}
//======================================
void Movement::Execute( int dt )
{
	float time_s = (float)dt/1000.0f;
	
	steering->velocity += steering->accel * time_s;

	if ( steering->velocity.x > 0.01f ) transform->facing = Transform::FacingRight;
	else if ( steering->velocity.x < -0.01f ) transform->facing = Transform::FacingLeft;

	if ( body->CollideWith(COLLIDE_BOTTOM) )
	{
		float friction_accel = steering->velocity.x * STATIC_FRICTION;
		float sub_velocity = friction_accel * time_s;
		if ( abs(sub_velocity) >= abs(steering->velocity.x) ) 
			sub_velocity = steering->velocity.x;
		steering->velocity.x -= sub_velocity;
	}
	else if ( abs(steering->velocity.x) > steering->max_speed )
	{
		steering->velocity.x /= abs(steering->velocity.x);
		steering->velocity.x *= steering->max_speed;
	}
	Vector3& pos = transform->position;
	pos.x += steering->velocity.x * time_s;
	pos.y += steering->velocity.y * time_s;

}
//======================================
void Movement::Initialize( Composition* owner )
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
	body = static_cast<Body*>(owner->GetComponent( CT_Body ));
}
