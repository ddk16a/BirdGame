#include <iostream>
#include <sstream>
#include <algorithm>
#include "room.h"
using namespace std;

vector<Room*> Room::rooms;

Room::Room(string environment, bool unlocked) {
	description = environment;
	open = unlocked;
	rooms.push_back(this); //inserts this room into the static vector of rooms
}

//gets the first room
Room* Room::getStart() {
	return rooms.at(0);
}

//returns the room in the specified direction
Room* Room::findRoom(std::string direction) const {
	try {
		return rooms[connections.at(direction)];
	}
	catch (exception) {
		//if there is not a room in the specified direction, throws an error message
		throw string("There isn't a way to go " + direction + ".");
	}
}

Item* Room::search(string target) const {
	auto item = find(contents.begin(), contents.end(), target);
	if (item == contents.end())
		throw string("Could not find target " + target);
	return *item;
}

//finds the specified object and removes if from the room
Bird* Room::gather(string target) {

	/* going to use remove _if */
	auto bird = find(contents.begin(), contents.end(), target);

	if (bird == contents.end())
		throw string("Could not find " + target + ".");
	else if (!(*bird)->getGather())
		throw string ((*bird)->getDescription());

	Bird* ret = new Bird(*static_cast<Bird*>(*bird));
	contents.erase(bird);

	return ret;

}


bool Room::unlocked() const {
	return open;
}

//unlocks the next room
void Room::unlock(string dir) {
	try {
		rooms[connections.at(dir)]->open = true;
	}
	catch (exception) {
		//throws an error message if there isn't a room forward
		throw string("There isn't anything to unlock.");
	}
}

void Room::addItem(Item* item) {
	contents.push_back(item);
}

void Room::removeItem(std::string target) {
	contents.erase(find(contents.begin(), contents.end(), target));
}

void Room::addConnection(string direction, int destination) {
	connections[direction] = destination;
}

void Room::handle(string command) {
	if (command == "Inspect")
		return look_at();
	Control::handle(command);
}

void Room::look_at() const {
	search(Game::line())->inspect();
}

void Room::describe() const {
	Game::print(description);
	for (list<Item*>::const_iterator i = contents.begin(); i != contents.end(); i++)
		(*i)->getNarration();
}
