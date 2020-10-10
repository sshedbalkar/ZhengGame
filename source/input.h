#pragma once

#include "system.h"
#include <Windows.h>
#include <map>

class Input : public System
{
public:
	Input();
	virtual ~Input();

	virtual void Initialize();
	virtual void Update( int dt );
	virtual void Free();

	bool KeyDown( int key );
	int KeyTime( int key );

	void InputMsgProc( UINT msg, WPARAM wParam, LPARAM lParam );
private:
	struct KeyState
	{
		bool down;
		int time;
	};
	std::map<int, KeyState> key_state;
};
extern Input* INPUTSYS;
