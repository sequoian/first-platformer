#ifndef INPUT_H
#define INPUT_H

#include "Helpers.h"

class Input {
public:
	Input();

	void pollForEvents();
	InputData getData();
private:
	InputData inputData;
	void reset();

};

#endif