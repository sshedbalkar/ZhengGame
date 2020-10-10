#include "ShowDialogs.h"
#include "composition.h"
#include "substance.h"
#include "dialogs.h"
#include "factory.h"


#define STATE_IDLE		0
#define STATE_POPUP		1
#define STATE_SHRINK	2
#define STATE_SHOW		3

#define IISTATE_ENTER	0
#define IISTATE_UPDATE	1
#define IISTATE_EXIT	2

//==============================================
ShowDialogs::ShowDialogs()
{
}
//==============================================
ShowDialogs::~ShowDialogs()
{

}
//==============================================
void ShowDialogs::Initialize( Composition* _owner )
{		
	owner = _owner;
	state = STATE_IDLE;
	inner_state = OnEnter;
	
	dialogs_info = static_cast<Dialogs*>( owner->GetComponent( CT_Dialogs ));
	hero_position = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform )))->position;
	transform = static_cast<Transform*>( owner->GetComponent( CT_Transform ));
	
	substance = new Substance;
	transform->height = 1.0f;
	transform->width = 1.0f;
	substance->SetParameters( 0.0f,4.0f,0.0f,6.5f,6.5f,0.0f,
								"blank",0.93f,0.91f,0.67f );
	owner->AddComponent( substance );
}
//==============================================
void ShowDialogs::Execute( int dt )
{
	Dialogs::DialogList& dialogs = dialogs_info->dialogs;

	static int show_id = -1;

	if ( state > STATE_SHRINK && 
		 (abs(dialogs[show_id].x - hero_position->x) > dialogs_info->range_x ||
		 abs(dialogs[show_id].y - hero_position->y) > dialogs_info->range_y ) )
	{
		state = STATE_SHRINK;
		inner_state = OnEnter;
	}

	switch( state )
	{
	case STATE_IDLE:
		{
			for ( unsigned int i = 0; i < dialogs.size(); ++i )
			{
				if ( abs(dialogs[i].x - hero_position->x) < dialogs_info->range_x &&
					 abs(dialogs[i].y - hero_position->y) < dialogs_info->range_y )
				{
					show_id = i;
					state = STATE_POPUP;
					inner_state = OnEnter;
				}
			}
		}
		break;

	case STATE_SHRINK:
		switch( inner_state )
		{
		case OnEnter:
			substance->ChangeSpriteTo( "dialog_shrink" );
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			if ( msg_id == MSG_ANIMATION_END )
			{
				substance->ChangeSpriteTo( "blank" );
				state = STATE_IDLE;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_POPUP:
		switch( inner_state )
		{
		case OnEnter:
			transform->position.x = dialogs[show_id].x;
			transform->position.y = dialogs[show_id].y;
			substance->ChangeSpriteTo( "dialog_popup" );
			inner_state = OnUpdate;
			break;
		case OnUpdate:
			if ( msg_id == MSG_ANIMATION_END )
			{
				substance->ChangeSpriteTo( dialogs[show_id].sprite );
				state = STATE_SHOW;
				inner_state = OnEnter;
			}
			break;
		}
		break;

	case STATE_SHOW:
		switch( inner_state )
		{
		case OnEnter:
			inner_state = OnUpdate;
			break;
		}
		break;

	};
	msg_id = MSG_NONE;
}
//==============================================
void ShowDialogs::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
