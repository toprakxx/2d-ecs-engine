#include "./Game/Game.h"

int main(int argc, char* argv[]) {
	Game game;

	game.Initalize();
	game.Run();
	game.Destroy();

	return 0;
}
