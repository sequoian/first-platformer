#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "Helpers.h"


// Processes input events into data.  Stores and retrieves that data.
class Input {
public:
	Input();
	void pollForEvents();
	InputData getData();
private:
	InputData inputData_;

	void storePreviousInput();
};

#endif

/****

Possible Changes:
- Associate SDL_Keycodes (e.g. SDLK_LEFT) with InputData members (or functions).  Perhaps with a table?
- Take InputData declaration out of Helpers.h and put it here.
- Make InputData struct store 2 other structs: CurrentInput and PreviousInput.


****/