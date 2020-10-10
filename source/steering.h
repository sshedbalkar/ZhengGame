#pragma once

#include "component.h"
#include "math.h"

class Transform;

class Steering : public Component
{
public:
	Steering();
	virtual ~Steering();

	virtual void Initialize();
	virtual void Serialize( Json::Value& root );

	virtual Component* Clone();

	Vector2 velocity;
	Vector2 accel;
	float rotation;
	float max_speed;
	float max_accel;

};
