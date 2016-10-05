#include <string>
#include "VGCVirtualGameConsole.h"
#include "Game.h"

using namespace std;

//Window
static string name = "INVADERS";
static const int width = 600;
static const int height = 640;

int VGCMain(const VGCStringVector &arguments){

	//Create window
	VGCVirtualGameConsole::initialize(name, width, height);

	//Create and start game
	Game game;
	game.start();

	return 0;
}