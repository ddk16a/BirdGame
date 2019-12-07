#ifndef PLAYER_H
#define PLAYER_H

	#include <iostream>
	#include <vector>
	#include "control.h"
	#include "game.h"
	#include "item.h"
	#include "room.h"

	class Player : public Control {
		private:
			std::list<Bird*> bag; //Keeps track of all the items
			Room* location; //keeps track of the map
			static const int capacity;

			void move(); //moves the player in the specified direction
			void use(); //uses and item in the inventory, on something if so specified
			void gather(); //inserts a bird into the bag from the room
			void inventory(); //outputs the birds in the bag
			void view(); //views things in the inventory

			static Player* instance; //the single instance

			//singleton stuffs
			Player();
			Player(const Player&);
			Player& operator=(const Player&);

			bool canHold() const; //checks if the bag if full

		public:
			virtual ~Player();

			static Player* getPlayer(); //accessor
			Room* getLocation() const;

			void handle(std::string);
	};
	
#endif