#pragma once

#include "component.h"

class Transform;

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void Initialize();
	virtual void Serialize( Json::Value& root );

	virtual Component* Clone();

	void GetViewingPosition( float& x, float& y );

private:
	Transform* transform;

};
