#pragma once

#include <Windows.h>
#include "system.h"
#include "gameLogic.h"
#include <vector>
#include <map>

class Composition;
class Message;

enum GameStage
{
	GS_NORMAL,
	GS_NEXT,
	GS_EXIT
};

class Core
{
public:
	Core();
	~Core();

	void Initialize( const std::string& filename );
	void MainLoop();
	void CleanUp();

	void BroadcastMessage( const Message* msg );
	void SendMessageToLogicType( const Message* msg, LogicType type );
	void SendMessageToObj( const Message* msg, Composition* obj, LogicType type = LT_All );
	void SetNextLevel( const std::string& next );
	void SetRestartLevel();

	System* GetSystem( SystemType sys );

	void TogglePrintFrametime( ) { print_frametime = !print_frametime; }
//	void BroadcastMessage();
//	void SendMessage( SystemType sys );

private:
	unsigned int last_time;

	std::vector<System*> systems;
	HWND hwnd;

	int screen_width, screen_height;
	GameStage game_stage;
	std::string next_level;

	bool print_frametime;
	
	friend LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
};


extern Core* CORE;
