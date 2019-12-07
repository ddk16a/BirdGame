#include <sstream>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include "player.h"
using namespace std;

Player* Player::instance = NULL;
const int Player::capacity = 20;

Player::Player() : Control() {
	insert(location = Room::getStart());
	location->describe();
}

Player::~Player() {
	delete instance;
}

Player* Player::getPlayer() {
	if (!instance)
		instance = new Player;
	return instance;
}

void Player::handle(string command) {
	if (command == "Go" || command == "go")
		return move();
	if (command == "Use" || command == "use") 
		return use();
	if (command == "Gather" || command == "gather")
		return gather();
	if (command == "Bag" || command == "bag")
		return inventory();
	if (command == "View" || command == "view")
		return view();
	Control::handle(command);
}

//moves the player in the specified direction
void Player::move() {
	string direction = Game::line();
	Room* goal = location->findRoom(direction);
	if(!goal->unlocked()) //if the room is locked, throws an error message
		throw string("You can't go " + direction + " yet. It must be locked.");
	insert(location = goal);
	location->describe();
}

//uses a bird on an object
void Player::use() {
	//if the command wasn't typed properly, throws an error
	string bird, on, target;
	if (!(cin >> bird >> on >> target))
		throw string("Your command wasn't recognized. Use 'commands' to see what you can type.");

	bird = Game::correct(bird);
	target = Game::correct(target);

	//finds the bird to be used, the object to be used on, and erases the used bird after it is used on the object
	auto tool = find(bag.begin(), bag.end(), bird);
	if (tool == bag.end()) 
		throw string("You don't have a " + bird + ".");


	location->search(target)->use(*tool);
}

//takes a bird from the room and puts it in the inventory
void Player::gather() {
	//throws an error if the player's inventory has reched it's capacity
	if (!canHold())
		throw string("Your bag is too full of birds!");

	//finds the target bird and inserts it into the inventory
	string target = Game::line();
	
	bag.push_back(location->gather(target));
	Game::print(bag.back()->getGather());
	Game::print("~Would you like to name the <" + target + ">? ");
	if (Game::input() == "Yes") {
		Game::print("What would to like to name it?");
		bag.back()->setNick(Game::input());
		Game::print("You now have a <" + target + "> named <" + bag.back()->getNick() + ">.");
	}

	bag.sort([] (Bird* a, Bird* b) {
		if (a->getName() != b->getName())
			return a->getName() < b->getName();
		return (b->getNick() != "");
	});
}

void Player::inventory() {
	auto i = bag.begin();
	while (i != bag.end()) {
		string name = (*i)->getListing();
		auto g = find_if_not(i, bag.end(), [name] (Bird* b) { return b->getListing() == name; });

		int d = distance(i, g);
		Game::print(string("^") + (d > 1 ? string("") + char(d + '0') + ' ' : string("")) + name);

		i = g;
	}
}

void Player::view() {
	string bird = Game::input();
	auto tool = find(bag.begin(), bag.end(), bird);
	if (tool == bag.end()) 
		throw string("You don't have a " + bird + ".");
	(*tool)->inspect();
}

//checks if the inventory has reched it's capacity
bool Player::canHold() const {
	return bag.size() < capacity;
}

Room* Player::getLocation() const {
	return location;
}