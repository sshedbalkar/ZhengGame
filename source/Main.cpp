#include "core.h"

//INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, INT )
int main()
{
	Core core;
	core.Initialize(std::string("gameData\\game.txt"));
	core.MainLoop();
	core.CleanUp();
	
	return 0;
}
