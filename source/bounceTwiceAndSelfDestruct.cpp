#include "bounceTwiceAndSelfDestruct.h"

#include "transform.h"
#include "steering.h"
#include "composition.h"
#include "body.h"

#include "other_messages.h"
#include "core.h"

#define BOUNCING_RATE		0.5f

//=============================================
BounceTwiceAndSelfDestruct::BounceTwiceAndSelfDestruct()
{
	logic_type = LT_CollisionHandling;
}
//=============================================
BounceTwiceAndSelfDestruct::~BounceTwiceAndSelfDestruct()
{
}
//=============================================
void BounceTwiceAndSelfDestruct::Initialize( Composition* _owner )
{
	bouncing_count = 0;

	owner = _owner;
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));

}
//=============================================
void BounceTwiceAndSelfDestruct::ProceedMessage( const Message* msg )
{
	if ( msg->id != MSG_COLLISION ) return;
	++bouncing_count;
	if ( bouncing_count == 2 ) 
	{
		MessageDestruct md;
		CORE->SendMessageToObj( &md, owner, LT_StateMachine );
	}

	const MessageCollision* m = static_cast<const MessageCollision*>(msg);

	float x = m->colliding_x;
	float y = m->colliding_y;

	transform->position.x += x;
	transform->position.y += y;

	float speed = steering->velocity.x * steering->velocity.x;
	speed += steering->velocity.y * steering->velocity.y;
	speed = sqrt(speed);
	speed *= BOUNCING_RATE;
	float base = abs(x) + abs(y);
	steering->velocity.x = speed * x /base;
	steering->velocity.y = speed * y /base;

	Body* body = static_cast<Body*>(owner->GetComponent( CT_Body ));
	body->terrain_collision_flag = 0;

//	if ( abs(x) > 0.01f ) steering->velocity.x = -steering->velocity.x * 0.5f;
//	if ( abs(y) > 0.01f ) steering->velocity.y = -steering->velocity.y * 0.5f;

}
