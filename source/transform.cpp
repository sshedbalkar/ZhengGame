#include "transform.h"

//=========================================
Transform::Transform() : Component( CT_Transform )
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	width = 1.0f;
	height = 1.0f;
	facing = FacingRight;
}
//=========================================
Transform::~Transform()
{
}
//=========================================
void Transform::Serialize( Json::Value& root )
{
	position.x = static_cast<float>(root.get("x", 0.0f ).asDouble());
	position.y = static_cast<float>(root.get("y", 0.0f ).asDouble());
	
	width = static_cast<float>(root.get("width",1.0f ).asDouble());
	height = static_cast<float>(root.get("height",1.0f ).asDouble());
	orientation = static_cast<float>(root.get("orientation",0.0f ).asDouble());
}
//=========================================
void Transform::Initialize()
{
}
//=========================================
Component* Transform::Clone()
{
	return new Transform( *this );
}
//=============================================
void Transform::BuildWorldMatrix( Matrix4x4& mat_world )
{
	if ( facing == FacingRight )
		MatrixScaling( &mat_world, width, height, 1.0f );
	else MatrixScaling( &mat_world, -width, height, 1.0f );
	Matrix4x4 mat;
	MatrixRotation( &mat, orientation );
	mat_world *= mat;
	MatrixTranslation( &mat, position.x, position.y, position.z );
	mat_world *= mat;
}
//=============================================
float Transform::GetXInFront( float offset )
{
	float factor = facing == FacingRight ? 1.0f : -1.0f;
	return position.x + factor * offset;
}
