#ifndef CANVAS_LOADER_H_INCLUDED
#define CANVAS_LOADER_H_INCLUDED

#include "Canvas.h"

class CanvasLoader {
public:
	Canvas* getCanvas(SDL_Texture* texture);
private:
	SDL_Texture* canvasTexture_;

	Canvas* intro();
	Canvas* newCanvas();
	Canvas* openCanvas();

};

#endif