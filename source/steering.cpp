#include "steering.h"
#include "transform.h"
#include "composition.h"
#include "movement.h"


//===========================================
Steering::Steering() : Component( CT_Steering )
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	accel.x = 0.0f;
	accel.y = 0.0f;
	rotation = 0.0f;
	max_speed = 4.0f;
}
//===========================================
Steering::~Steering()
{
}
//===========================================
void Steering::Serialize( Json::Value& root )
{
	max_speed = static_cast<float>(root["MaxSpeed"].asDouble());
	max_accel = static_cast<float>(root["MaxAccel"].asDouble());

}
//===========================================
void Steering::Initialize()
{
}
//===========================================
Component* Steering::Clone()
{
	return new Steering( *this );
}
