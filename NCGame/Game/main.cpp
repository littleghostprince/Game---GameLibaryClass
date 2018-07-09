#include "Engine.h"

int wmain(int argc, char* argv[])
{
	Engine engine;

	engine.Initialize();
	while (!engine.isQuit())
	{
		engine.Update();
	}
	engine.Shutdown();


	return 0;
}