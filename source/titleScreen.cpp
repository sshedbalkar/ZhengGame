#include "TitleScreen.h"
#include "input.h"
#include "core.h"

#include "input_messages.h"
#include "composition.h"


//======================================
TitleScreen::TitleScreen()
{
	logic_type = LT_Controller;
}
//======================================
TitleScreen::~TitleScreen()
{
}
//======================================
void TitleScreen::Execute( int dt )
{

}
//======================================
void TitleScreen::Initialize( Composition* _owner )
{	
	owner = _owner;
	enable = false;

	Substance* substance = new Substance;
	substance->SetParameters( 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,"resources\\title_alpha.bmp","resources\\title.bmp" );
	owner->AddComponent( substance );

}
//======================================
void TitleScreen::ProceedMessage( const Message* msg )
{

	if ( msg->id != MSG_KEY_TRIGGERED ) return;
	const MessageKeyTriggered* key_msg = static_cast< const MessageKeyTriggered*>(msg);

	CORE->SetNextLevel( "level0" );
}
