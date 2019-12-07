#include <iostream>
#include <cstddef>
#include "control.h"
using namespace std;

//control inserted after this
void Control::insert(Control* c) {
	next = c;
}

Control::Control() {
	next = NULL;
}

Control::~Control() {
	next = NULL;
}

void Control::handle(string s) {
	if(next)
		return next->handle(s);

	string junk;
	getline(cin, junk);
	throw string(s + " is not a supported command");
}