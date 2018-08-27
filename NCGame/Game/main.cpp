#if defined(_MSC_VER)
# pragma warning( disable : 4506 )
#endif

#include "Engine.h"
#include "game.h"


int wmain(int argc, char* argv[])
{

	Engine engine;
	Game game(&engine);

	game.Initalize();
	while (game.Run())
	{
		game.Update();
	}
	game.Shutdown();

	return 0;
}