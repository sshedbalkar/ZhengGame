#pragma once

#include "system.h"
#include "physicalLogic.h"
#include <list>

class PhysicsComposition;
class Body;
class Transform;

class Physics : public System
{
public:
	Physics();
	virtual ~Physics();

	virtual void Update( int dt );
	virtual void Initialize();
	virtual void Free();
	
	void AddPhysicsComposition( PhysicsComposition* comp );
	void AddBody( Body* body );
	static bool CollidingTest( Body* body0, Transform* transform0,
							   Body* body1, Transform* transform1,
							   float* colliding_x=NULL, float* colliding_y=NULL );

	typedef std::list<Body*> BodyList;
	typedef std::list<PhysicsComposition*> PhysicsCompositionList;

	const BodyList& GetBodyList() { return bodies; }

private:
	PhysicsCompositionList physics_compositions;
	BodyList bodies;
};

extern Physics* PHYSICS;