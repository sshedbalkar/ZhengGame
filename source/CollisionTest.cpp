#include "CollisionTest.h"
#include "composition.h"

#include "body.h"
#include "transform.h"

#include "physics.h"
#include "core.h"
#include "other_messages.h"

//======================================
CollisionTest::CollisionTest()
{
}
//======================================
CollisionTest::~CollisionTest()
{
}
//======================================
void CollisionTest::Execute( int dt )
{
	body->terrain_collision_flag = 0;
	const Physics::BodyList& bodies = PHYSICS->GetBodyList();
	
	Physics::BodyList::const_iterator it;
	for ( it = bodies.begin(); it != bodies.end(); ++it )
	{
		if ( (*it) == body ) continue;

		float x, y;
		if ( Physics::CollidingTest( body,body->transform,
								(*it),(*it)->transform,
								&x,&y ) )
		{
			MessageCollision msg;
			msg.colliding_body = *it;
			msg.colliding_x = x;
			msg.colliding_y = y;

			CORE->SendMessageToObj( &msg, body->GetOwner(), LT_CollisionHandling );

			if ( x < -0.001f ) body->terrain_collision_flag |= COLLIDE_RIGHT;
			if ( x >  0.001f ) body->terrain_collision_flag |= COLLIDE_LEFT;
			if ( y < -0.001f ) body->terrain_collision_flag |= COLLIDE_TOP;
			if ( y >  0.0f ) body->terrain_collision_flag |= COLLIDE_BOTTOM;


		}

	}
	
}
//======================================
void CollisionTest::Initialize( Composition* owner )
{
	body = static_cast<Body*>(owner->GetComponent( CT_Body ));
}
