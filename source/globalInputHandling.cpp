#include "globalInputHandling.h"
#include "input_messages.h"
#include "graphics.h"
#include "core.h"

//===========================================
GlobalInputHandling::GlobalInputHandling()
{
	logic_type = LT_Controller;
}
//===========================================
GlobalInputHandling::~GlobalInputHandling()
{
}
//===========================================
void GlobalInputHandling::Initialize( Composition* owner )
{
}
//===========================================
void GlobalInputHandling::Execute( int dt )
{
}
//===========================================
void GlobalInputHandling::ProceedMessage( const Message* msg )
{

	if ( msg->id != MSG_KEY_TRIGGERED ) return;

	const MessageKeyTriggered* m = static_cast<const MessageKeyTriggered*>(msg);

	switch( m->key )
	{
	case VK_F1:
		GRAPHICS->ToggleDebugDrawing();
		break;

	case VK_F2:
		CORE->TogglePrintFrametime();
		break;
	}
}
