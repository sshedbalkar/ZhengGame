#include "gravityAffected.h"
#include "composition.h"

#include "steering.h"

#define GRAVITY				20.0f

//======================================
GravityAffected::GravityAffected()
{
}
//======================================
GravityAffected::~GravityAffected()
{
}
//======================================
void GravityAffected::Execute( int dt )
{
	float time_s = (float)dt/1000.0f;

	steering->velocity.y -= GRAVITY * time_s;

}
//======================================
void GravityAffected::Initialize( Composition* owner )
{
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
}
