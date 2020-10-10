#include "status.h"

//===================================
Status::Status() : Component( CT_Status )
{
}
//===================================
Status::~Status()
{
}
//===================================
void Status::Serialize( Json::Value& root )
{
	max_hp = root.get("max_hp",5).asInt();
	max_stamina = root.get("max_stamina",5).asInt();
}
//===================================
void Status::Initialize()
{
}
//===================================
Component* Status::Clone()
{
	return new Status;
}