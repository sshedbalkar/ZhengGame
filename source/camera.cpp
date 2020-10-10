#include "camera.h"
#include "transform.h"
#include "composition.h"
#include "graphics.h"

//=============================================
Camera::Camera() : Component( CT_Camera )
{
}
//=============================================
Camera::~Camera()
{
}
//=============================================
void Camera::Serialize( Json::Value& root )
{
}
//=============================================
void Camera::Initialize()
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	GRAPHICS->SetCamera( this );
}
//=============================================
Component* Camera::Clone()
{
	return this;
	++reference_count;
}
//=============================================
void Camera::GetViewingPosition( float& x, float& y )
{
	x = transform->position.x;
	y = transform->position.y + 3.0f;
}
