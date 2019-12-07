#include <iostream>
#include "game.h"
#include "windows.h"
using namespace std;


int main() {
	
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	
	system("cls");
	
	//start up the game
	Game* game = Game::getGame();

	string command;
	game->print("~What do you want to do?");
	command = game->input();
	while(command != "Quit") {
		try {
			game->handle(command);
		}
		catch (string error) {
			game->print(error);
		}

		game->print("~What do you want to do?");
		command = game->input();
	}
}
