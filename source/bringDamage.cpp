#include "bringDamage.h"
#include "other_messages.h"
#include "core.h"

//======================================
BringDamage::BringDamage()
{
	logic_type = LT_CollisionHandling;
}
//======================================
BringDamage::~BringDamage()
{
}
//======================================
void BringDamage::Initialize( Composition* _owner )
{
	owner = _owner;
}
//======================================
void BringDamage::ProceedMessage( const Message* msg )
{
	if ( msg->id != MSG_COLLISION ) return;
		
	const MessageCollision* m = static_cast<const MessageCollision*>(msg);
	if ( m->colliding_body->body_type != Body::Attackable ) return;

	MessageTakeHit mth;
	CORE->SendMessageToObj( &mth, m->colliding_body->GetOwner(), LT_StateMachine );

	MessagePostAttacking mpa;
	CORE->SendMessageToObj( &mpa, owner, LT_StateMachine );
}