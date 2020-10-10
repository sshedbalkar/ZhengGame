#include "heroAnimations.h"
#include "other_messages.h"

#include "substance.h"
#include "body.h"
#include "steering.h"
#include "composition.h"
#include "factory.h"

#define STATE_NORMAL		0
#define STATE_CURSED		1

//========================================
HeroAnimations::HeroAnimations()
{
}
//========================================
HeroAnimations::~HeroAnimations()
{
}
//========================================
void HeroAnimations::Initialize( Composition* owner )
{
	counter = 0;
	Substance* handle = static_cast<Substance*>( owner->GetComponent(CT_Substance) );

	body = handle->GetSubstanceByID( "body" );
	legs = handle->GetSubstanceByID( "legs" );
	face = handle->GetSubstanceByID( "face" );
	front_eye = handle->GetSubstanceByID( "front_eye" );
	back_eye = handle->GetSubstanceByID( "back_eye" );
	hair = handle->GetSubstanceByID( "hair" );

	collision_body = static_cast<Body*>( owner->GetComponent(CT_Body) );
	steering = static_cast<Steering*>( owner->GetComponent(CT_Steering) );
	hero_position = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform )))->position;

	state = STATE_NORMAL;
}
//========================================
void HeroAnimations::Execute( int dt )
{
	if ( collision_body->CollideWith( COLLIDE_BOTTOM ) && 
		abs(steering->velocity.x) > 1.0f )
		legs->ChangeSpriteTo( "hero_legs_run" );
	else legs->ChangeSpriteTo( "hero_legs_stand" );

	switch( state )
	{
	case STATE_NORMAL:
		if ( msg_id == MSG_TAKE_HIT && hero_position->x > 40.0f )
		{
			++counter;
			if ( counter > 2 ) 
			{
				state = STATE_CURSED;
				inner_state = OnEnter;
			}
		}
		break;
		
	case STATE_CURSED:
		switch( inner_state )
		{
		case OnEnter:
			front_eye->ChangeSpriteTo("hero_eye_cursed");
			inner_state = OnUpdate;
			break;
		}
		break;
	}
}
//========================================
void HeroAnimations::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
