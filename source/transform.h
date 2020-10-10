#pragma once

#include "component.h"
#include "math.h"

class Transform : public Component
{
public:
	Transform( );
	virtual ~Transform();

	enum FacingDirection
	{
		FacingLeft,
		FacingRight
	};

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();
	float GetXInFront( float offset );
	void BuildWorldMatrix( Matrix4x4& mat );
	virtual Component* Clone();

	Vector3 position;
	float width, height;
	float orientation;
	FacingDirection facing;
};
