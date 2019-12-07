#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <windows.h>
#include "game.h"
#include "player.h"
#include "room.h"
using namespace std;

Game* Game::instance = NULL;
const int Game::TIME = 2;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

Game::Game() : Control() {
	load();
}

Game::~Game() {
	delete instance;
}

Game* Game::getGame() {
	if (!instance)
		instance = new Game;
	return instance;
}

//loads the game from a .txt file that specifies how the rooms should be made
void Game::load() {
	ifstream fin;

	fin.open("rooms.txt");

	//get file input
	int n;
	fin >> n;

	string junk;
	getline(fin, junk);
	for (int i = 0; i < n; i++) {
		getline(fin, junk);

		//reads in the rooms specifications and makes a new room
		string description;
		getline(fin, description);
		bool open;
		fin >> open;

		Room* room = new Room(description, open);

		//this fills the room with all the items
		string type;
		fin >> type;
		while (type != "end") {
			string nar;
			getline(fin, nar);
			nar = &(nar[1]);
			room->addItem(Factory::gimme(type, nar));

			fin >> type;
		}
		getline(fin, junk);

		//this reads in how the rooms should be connected with each other
		string connections, direction;
		int destination;
		getline(fin, connections);
		stringstream ss(connections);
		while (ss >> direction >> destination) {
			room->addConnection(direction, destination);
		}

	}

	//forms the chain of command
	insert(Player::getPlayer());
	fin.close();
}

void Game::handle(string s) {
	if (s == "Hi")
		return print("Hello, good friend!");
	if (s == "ping" || s== "Ping")
		return print("pong");		
	if (s == "Commands" || s == "Command")
		return print("Commands include:^go _ (forward, backward, left, right)^gather _ (bird)^use _ on _ (bird/item)^bag (to check your inventory)^inspect _ (item or bird)^view _ (to examine a bird in your bag)^quit (to quit the game)");
	Control::handle(s);
}

//for printing out things so that they happen 1 char at a time
void Game::print(string text) { 
	for(int i = 0; text[i] != 0; i++) {
		if(text[i] == '#')
			system("cls");
		else if(text[i] == '~')
			cout << endl << endl;
		else if(text[i] == '^')
			cout << endl;
		else if(text[i] == '<')
			SetConsoleTextAttribute(hConsole, 11);
		else if(text[i] == '>')	
			SetConsoleTextAttribute(hConsole, 7);				
		else{
			Sleep(TIME);
			cout << text[i];
		}
	}
	
	cout << " ";
}

string Game::correct(string s) {
	s[0] = toupper(s[0]);
	for (int i = 1; s[i] != 0; i++)
		s[i] = tolower(s[i]);
	return s;
}

//gets input and makes the first word capital and the rest lower case
string Game::input() {
	string s;
	cin >> s;
	return correct(s);
	
}

//getlines and corrects the case
string Game::line() {
	string s;
	getline(cin, s);
	stringstream ss(s);
	string corrected;
	ss >> corrected;
	corrected = correct(corrected);
	while (ss >> s) {
		for (int i = 0; s[i] != 0; i++)
			s[i] = tolower(s[i]);

		corrected += " " + s;
	}
	return corrected;
}
