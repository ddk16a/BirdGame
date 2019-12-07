#ifndef CONTROL_H
#define CONTROL_H

	#include <iostream>
	#include <cstddef>

	class Control {
		private:
			Control* next; //Makes the linked lilst work

		protected:
			void insert(Control*); //Adds an item to the command chain
			void remove(Control*); //removes an item form the chain
			void replaceNext(Control*);

		public:
			Control();
			~Control();
			
			virtual void handle(std::string); //This handles commands
	};

#endif