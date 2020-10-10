#include "snapFromTerrain.h"

#include "transform.h"
#include "steering.h"
#include "composition.h"

#include "other_messages.h"

//===============================================
SnapFromTerrain::SnapFromTerrain()
{
	logic_type = LT_CollisionHandling;
}
//===============================================
SnapFromTerrain::~SnapFromTerrain()
{
}
//===============================================
void SnapFromTerrain::Initialize( Composition* owner )
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));

}
//===============================================
void SnapFromTerrain::ProceedMessage( const Message* msg )
{
	if ( msg->id != MSG_COLLISION ) return;
	const MessageCollision* m = static_cast<const MessageCollision*>(msg);
	if ( m->colliding_body->body_type != Body::Terrain ) return;

	transform->position.x += m->colliding_x;
	transform->position.y += m->colliding_y;

	if ( abs(m->colliding_x) > 0.01f ) steering->velocity.x = 0.0f;
	if ( abs(m->colliding_y) > 0.01f ) steering->velocity.y = 0.0f;

}
