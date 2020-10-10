#include "body.h"
#include "composition.h"
#include "transform.h"
#include "physics.h"

//===========================================
Body::Body() : Component( CT_Body )
{
}
//===========================================
Body::~Body()
{
	if ( owner ) owner->RemoveReference();
}
//===========================================
void Body::Serialize( Json::Value& root )
{
	const std::string& str = root["shape"].asString();

	if ( str == "circle" ) shape = Shape_Circle;
	else shape = Shape_Rectangle;

	const std::string& str_type = root["type"].asString();
	if ( str_type == "terrain" ) body_type = Terrain;
	else if ( str_type == "attackable" ) body_type = Attackable;
	else body_type = None;

}
//===========================================
void Body::Initialize()
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	PHYSICS->AddBody( this );
	owner->AddReference();
}
//===========================================
Component* Body::Clone()
{
	return new Body(*this);
}
//===========================================
bool Body::CollideWith( int side )
{
	return (terrain_collision_flag & side) == side;
}