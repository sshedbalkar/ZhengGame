#include "SwordAttackInputHandling.h"
#include "input.h"
#include "core.h"

#include "input_messages.h"
#include "other_messages.h"


//======================================
SwordAttackInputHandling::SwordAttackInputHandling()
{
	logic_type = LT_Controller;
}
//======================================
SwordAttackInputHandling::~SwordAttackInputHandling()
{
}
//======================================
void SwordAttackInputHandling::Execute( int dt )
{

}
//======================================
void SwordAttackInputHandling::Initialize( Composition* _owner )
{	
	owner = _owner;
	enable = false;
}
//======================================
void SwordAttackInputHandling::ProceedMessage( const Message* msg )
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
		
	case 'A':
		MessageActivate m;
		CORE->SendMessageToObj( &m, owner, LT_StateMachine );
		break;

	}
}
