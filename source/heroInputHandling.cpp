#include "heroInputHandling.h"
#include "composition.h"
#include "core.h"

#include "transform.h"
#include "input.h"

#include "input_messages.h"
#include "other_messages.h"

#include "body.h"

//======================================
HeroInputHandling::HeroInputHandling()
{
	logic_type = LT_Controller;
}
//======================================
HeroInputHandling::~HeroInputHandling()
{
}
//======================================
void HeroInputHandling::Execute( int dt )
{
//	Vector3& position = transform->Position();
	if ( !enable ) return;

	float max_accel = 20.0f;
	if ( INPUTSYS->KeyDown( 'S' ) ) max_accel = 30.0f;
	if ( INPUTSYS->KeyDown( VK_LEFT ) ) 
	{
		steering->accel.x = -max_accel;
	}
	else if ( INPUTSYS->KeyDown( VK_RIGHT ) ) 
	{
		steering->accel.x = max_accel;
	}
	else
	{
		steering->accel.x = 0.0f;
		//MessageSwitchAnimation msg;
		//msg.animation = MessageSwitchAnimation::Stand;
		//CORE->SendMessageToObj( &msg, body->GetOwner(), LT_Animations );
	}
}
//======================================
void HeroInputHandling::Initialize( Composition* owner )
{
	transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	steering = static_cast<Steering*>(owner->GetComponent( CT_Steering ));
	body = static_cast<Body*>(owner->GetComponent( CT_Body ));
	
	enable = false;
}
//======================================
void HeroInputHandling::ProceedMessage( const Message* msg )
{
	if ( msg->id == MSG_CONTROL_ENABLE ) 
	{
		const MessageControlEnable* mce = 
			static_cast< const MessageControlEnable*>(msg);
		enable = mce->enable;
	}

	if ( !enable ) return;

	if ( msg->id != MSG_KEY_TRIGGERED ) return;
	const MessageKeyTriggered* key_msg = static_cast< const MessageKeyTriggered*>(msg);

	switch( key_msg->key )
	{
		
	case VK_LEFT:
	case VK_RIGHT:
		break;
	case 'D':
		if ( body && body->CollideWith( COLLIDE_BOTTOM ) )
		{
			steering->velocity.y = 10.0f;
			//MessageSwitchAnimation msg;
			//msg.animation = MessageSwitchAnimation::Stand;
			//CORE->SendMessageToObj( &msg, body->GetOwner(), LT_Animations );
		}
		break;

	}
}
