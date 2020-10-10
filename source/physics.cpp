#include "physics.h"
#include "physicsComposition.h"
#include "utility.h"
#include "allPhysics.h"
#include "body.h"
#include "transform.h"

#include "composition.h"

Physics* PHYSICS = NULL;

#define REGISTER_PHYSICS(type)	PhysicsComposition::AddPhysicsSerializer(#type,new PhysicsSerializerType<type>());

//=============================================
Physics::Physics() : System( ST_Physics )
{
}
//=============================================
Physics::~Physics()
{
	PhysicsComposition::DeleteSerializers();
}
//=============================================
void Physics::Free()
{
	bodies.clear();
	physics_compositions.clear();
}
//=============================================
void Physics::Initialize()
{
	REGISTER_PHYSICS(Movement);
	REGISTER_PHYSICS(GravityAffected);
	REGISTER_PHYSICS(CollisionTest);
	REGISTER_PHYSICS(ChaseThePlayer);
	PHYSICS = this;
}
//=============================================
void Physics::Update( int dt )
{
	BodyList::iterator bit = bodies.begin();
	while ( bit != bodies.end() )
	{
		if ( !(*bit)->GetOwner()->Exists() )
		{
//			utility::Delete(*bit);
			bit = bodies.erase(bit);
		}
		else ++bit;
	}

	PhysicsCompositionList::iterator it = physics_compositions.begin();
	while ( it != physics_compositions.end() )
	{
		if ( !(*it)->GetOwner()->Exists() )
		{
//			utility::Delete(*it);
			it = physics_compositions.erase(it);
		}
		else
		{
			(*it)->Execute( dt );
			++it;
		}
	}
}
//=============================================
void Physics::AddPhysicsComposition( PhysicsComposition* comp )
{
	physics_compositions.push_back( comp );
}
//=============================================
void Physics::AddBody( Body* body )
{
	bodies.push_back( body );
}
//=============================================
bool Physics::CollidingTest( Body* body0, Transform* transform0,
							Body* body1, Transform* transform1,
							float* colliding_x, float* colliding_y )
{
	bool colliding;

	switch( body0->shape )
	{
	case Body::Shape_Circle:
		switch ( body1->shape )
		{
		case Body::Shape_Circle:
			colliding = math::CircleOnCircle(
				transform0->position.x, transform0->position.y, transform0->width /2.0f,
				transform1->position.x, transform1->position.y, transform1->width /2.0f,
				colliding_x, colliding_y );
			break;

		case Body::Shape_Rectangle:
			colliding = math::CircleOnRectangle(
				transform0->position.x, transform0->position.y, transform0->width /2.0f,
				transform1->position.x, transform1->position.y, transform1->width, transform1->height,
				colliding_x, colliding_y );
			break;

		}
		break;

	case Body::Shape_Rectangle:
		switch( body1->shape )
		{
		case Body::Shape_Circle:
			colliding = math::CircleOnRectangle(
				transform1->position.x, transform1->position.y, transform1->width /2.0f,
				transform0->position.x, transform0->position.y, transform0->width, transform0->height,
				colliding_x, colliding_y );
			*colliding_x = -*colliding_x;
			*colliding_y = -*colliding_y;
			break;

		case Body::Shape_Rectangle:
			colliding = math::RectangleOnRectangle(
				transform0->position.x, transform0->position.y, transform0->width, transform0->height,
				transform1->position.x, transform1->position.y, transform1->width, transform1->height,
				colliding_x, colliding_y );

			if ( abs(*colliding_y) > abs(*colliding_x) ) *colliding_y = 0.0f;
			else *colliding_x = 0.0f;

			break;
		}
		break;
	}

	return colliding;
}