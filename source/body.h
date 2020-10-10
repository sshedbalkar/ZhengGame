#pragma once

#include "component.h"

#define COLLIDE_LEFT		1
#define COLLIDE_RIGHT		2
#define COLLIDE_BOTTOM		4
#define COLLIDE_TOP			8

class Transform;

class Body : public Component 
{
public:

	enum Shape
	{
		Shape_Rectangle,
		Shape_Circle
	};
	enum Type
	{
		None,
		Terrain,
		Attackable
	};

	Body();
	virtual ~Body();

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();

	////cloning a sprite make little sense
	virtual Component* Clone();

	bool CollideWith( int side );
	int terrain_collision_flag;

	Shape shape;
	Type body_type;

	Transform* transform;

};
