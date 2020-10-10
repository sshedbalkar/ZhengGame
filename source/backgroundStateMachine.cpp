#include "backgroundStateMachine.h"

#include "composition.h"
#include "substance.h"
#include "factory.h"

#include "other_messages.h"

#define STATE_IDLE			0
#define STATE_SWITCHDARK	1

//==============================================
BackgroundStateMachine::BackgroundStateMachine()
{
}
//==============================================
BackgroundStateMachine::~BackgroundStateMachine()
{
}
//==============================================
void BackgroundStateMachine::Initialize( Composition* _owner )
{
	owner = _owner;

	substance = static_cast<Substance*>( owner->GetComponent(CT_Substance) );

	state = STATE_IDLE;
	inner_state = OnEnter;
	hero_position = &(static_cast<Transform*>(FACTORY->GetHeroHandle()->GetComponent( CT_Transform )))->position;

}
//==============================================
void BackgroundStateMachine::Execute( int dt )
{
	static int timer = 0;

	switch( state )
	{
	case STATE_IDLE:
		if ( hero_position->x > 39.0f )
		{
			state = STATE_SWITCHDARK;
			inner_state = OnEnter;
		}
		break;

	case STATE_SWITCHDARK:
		switch( inner_state )
		{
		case OnEnter:
			{
				handle = new Substance;
				handle->SetParameters( 0.4f,0.1f,0.0f,0.0f,0.0f,0.0f,"static_circle_filled",0.0f,0.1f,0.9f );
				substance->AddSubSubstance( handle );

				Substance* moon = new Substance;
				moon->SetParameters( 0.6f,-0.07f,0.0f,0.3f,0.3f,0.0f,"moon",1.0f,1.0f,1.0f );
				substance->AddSubSubstance( moon );

				inner_state = OnUpdate;
				timer = 0;
				counter = 0;
				break;
			}

		case OnUpdate:
			timer += dt;
			if ( timer > 100 )
			{
				handle->IncreaseSize( 0.3f, 0.15f );
				timer = 0; ++counter;
				if ( counter >= 12 ) inner_state = OnExit;
			}
			break;

		case OnExit:

			break;
		}
		break;

	};
	msg_id = MSG_NONE;
}
//==============================================
void BackgroundStateMachine::ProceedMessage( const Message* msg )
{
	msg_id = msg->id;
}
