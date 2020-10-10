#include "input.h"
#include "input_messages.h"
#include "core.h"
#include <iostream>//////

Input* INPUTSYS = NULL;
//=======================================
Input::Input() : System( ST_Input )
{
}
//=======================================
Input::~Input()
{
	
}
//=======================================
void Input::Free()
{
	key_state.clear();
}
//=======================================
void Input::Initialize()
{
	INPUTSYS = this;
}
//=======================================
void Input::Update( int dt )
{		
	MSG msg;
	while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}
//=======================================
bool Input::KeyDown( int key )
{
	return key_state[key].down;
}
//=======================================
int Input::KeyTime( int key )
{
	return key_state[key].time;
}
//=======================================
void Input::InputMsgProc( UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_KEYDOWN:
		{
			if ( key_state[wParam].down == false ) ///key triggered
			{
				MessageKeyTriggered msg;
				msg.key = wParam;
				CORE->SendMessageToLogicType( &msg, LT_Controller );
			}
			key_state[wParam].down = true;
			break;
		}
	case WM_KEYUP:
		{
			key_state[wParam].down = false;
			break;
		}
	}
}
