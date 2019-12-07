#ifndef ROOM_H
#define ROOM_H
	
	#include <list>
	#include <map>
	#include <vector>
	#include "control.h"
	#include "item.h"

	class Room : public Control {
		private:
			std::string description;
			std::list<Item*> contents; //holds all the intms found in the room
			std::map<std::string,int> connections; //The key is the direction, and the value is the index for the room it connects to
			bool open;

			static std::vector<Room*> rooms; //this holds each room that is made. Esentially the map

		public:

			Room(std::string, bool);

			static Room* getStart(); //return the first room

			Room* findRoom(std::string) const; //returns the room that is found in the direction specified
			Item* search(std::string) const; //returns the item
			Bird* gather(std::string); //finds and removes an item from the room
			bool unlocked() const; //returns true if this room is open

			void unlock(std::string); //unlocks the room in the direction "forward"
			void addItem(Item*); //adds an item to the room
			void removeItem(std::string); //gets rid of stuff
			void addConnection(std::string, int); //adds a connection to the room. ONLY FOR WHEN LOADING THE GAME
			void handle(std::string); //handler
			void look_at() const; //inspects an item in the room
			void describe() const; //outputs the description
	};

#endif