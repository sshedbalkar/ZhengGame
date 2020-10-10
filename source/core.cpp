#include "core.h"
#include "utility.h"
#include "../json/json.h"
#include <fstream>
//systems
#include "graphics.h"
#include "factory.h"
#include "input.h"
#include "logicSystem.h"
#include "physics.h"

Core* CORE = NULL;

//===========================================================
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		INPUTSYS->InputMsgProc( msg, wParam, lParam );
		break;

//	case WM_WINDOWPOSCHANGED:
	case WM_PAINT:
		break;

	case WM_DESTROY:
		CORE->game_stage = GS_EXIT;
		PostQuitMessage( 0 );
		return 0;

    }
	return DefWindowProc( hWnd, msg, wParam, lParam );
}
//===========================================================
Core::Core()
{
}
//===========================================================
Core::~Core()
{
}
//===========================================================
void Core::Initialize( const std::string& filename )
{
	///initialize window file
	std::string title;
	Factory::WindowSerialize( filename, screen_width, screen_height,title );

	///window creation
	{
		RECT fullWinRect = {0, 0, screen_width, screen_height};
		AdjustWindowRect(&fullWinRect,	//The rectangle for the full size of the window
				WS_OVERLAPPEDWINDOW,	//The style of the window, which must match what is passed in to CreateWindow below
				FALSE);					//Does this window have a menu?
		////initialize the window
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		title.c_str(), NULL };
		RegisterClassEx( &wc );
		// Create the application's window.
		hwnd = CreateWindow( title.c_str(), title.c_str(), 
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			fullWinRect.right - fullWinRect.left, 
			fullWinRect.bottom - fullWinRect.top ,
			GetDesktopWindow(), NULL, wc.hInstance, NULL );
		
		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);
	}
	//assign a global pointer to the core engine
	CORE = this;
	
	//adding systems
	systems.push_back( new Factory );
	Graphics* graphics = new Graphics;
	graphics->SetWindowProperties( hwnd, screen_width, screen_height );
	systems.push_back( graphics );
	systems.push_back( new Physics );
	systems.push_back( new Input );
	systems.push_back( new LogicSystem );

	//initialize systems
	for ( unsigned int i = 0; i < systems.size(); ++i )
		systems[i]->Initialize();

	//serializing game assets/storing level files
	FACTORY->GameSerialize( filename );

	print_frametime = false;
}
//===========================================================
void Core::CleanUp()
{
	for ( unsigned int i = 0; i < systems.size(); ++i )
	{
		systems[i]->Free();
	}
	for ( unsigned int i = 0; i < systems.size(); ++i )
	{
		utility::Delete(systems[i]);
	}
}
//===========================================================
void Core::MainLoop()
{
	last_time = timeGetTime();

	while( game_stage != GS_EXIT )
	{
		if ( game_stage == GS_NEXT )			///// change level
		{
			for ( unsigned int i = 0; i < systems.size(); ++i )
			{
				systems[i]->Free();
			}
			FACTORY->LevelSerializeAndInitialize( next_level );
			game_stage = GS_NORMAL;
			last_time = timeGetTime();
		}

		unsigned int cur_time = timeGetTime();
		
		while ( cur_time - last_time < 16 ) cur_time = timeGetTime();
		int dt = cur_time - last_time;
		if ( print_frametime ) printf("%i\n", cur_time - last_time );
		if ( dt > 31 ) dt = 31;
//		int t = cur_time, lt = cur_time;
		for ( unsigned int i = 0; i < systems.size(); ++i )
		{
			if ( game_stage != GS_NORMAL ) break;
			systems[i]->Update( dt );
//			t = timeGetTime();
//			printf("%i : %i\n", systems[i]->GetType(), t - lt );
//			lt = t;
		}
//		printf("\n");
		last_time = cur_time;
	}
}
//===========================================================
void Core::SetNextLevel( const std::string& next )
{
	game_stage = GS_NEXT;
	next_level = next;
}
//===========================================================
void Core::SetRestartLevel()
{
	game_stage = GS_NEXT;
}
//===========================================================
System* Core::GetSystem( SystemType sys )
{
	for ( unsigned i = 0; i < systems.size(); ++i )
		if ( systems[i]->GetType() == sys ) return systems[i];

	return NULL;
}
//===========================================================
void Core::BroadcastMessage( const Message* msg )
{
	SendMessageToLogicType( msg, LT_All );
}
//===========================================================
void Core::SendMessageToLogicType( const Message* msg, LogicType type )
{
	LOGICSYS->ProcessMessage( msg, type );
}
//===========================================================
void Core::SendMessageToObj( const Message* msg, Composition* obj, LogicType type )
{
	LOGICSYS->ProcessMessage( msg, type, obj );
}
