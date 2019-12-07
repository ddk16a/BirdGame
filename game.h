#ifndef GAME_H
#define GAME_H

	#include <iostream>
	#include "control.h"

	class Game : public Control{
		private:

			static Game* instance; //the single instance
			static const int TIME; //Time for dlayed output

			//Private for singleton
			Game();
			Game(const Game&);
			Game& operator=(const Game&);


		public:
			static Game* getGame(); //acccessor

			virtual ~Game();

			void load(); //loads the game

			void handle(std::string); //sends commands down the chain
			static void print(std::string); //prints out common text strings
			static std::string correct(std::string);
			static std::string input(); //This is cin with a throw statement attached and deals with case
			static std::string line(); //This is getline with a throw statement and deals with case
	};

#endif
