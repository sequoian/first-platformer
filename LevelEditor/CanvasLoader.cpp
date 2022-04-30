#include "CanvasLoader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include "Globals.h"

std::string g_fileName; // declare externed global...?


Canvas* CanvasLoader::getCanvas(SDL_Texture* texture) {
	canvasTexture_ = texture;
	return intro();
}

Canvas* CanvasLoader::intro() {
	Canvas* canvas = nullptr;

	char option;
	bool done = false;
	do {
		std::cout << "Create [n]ew level or [o]pen existing level." << std::endl;
		std::cin >> option;
		if (option == 'n') {
			std::cout << "new" << std::endl;
			canvas = newCanvas();
			done = true;

		}
		else if (option == 'o') {
			std::cout << "open" << std::endl;
			canvas = openCanvas();
			done = true;
		}
		else {
			std::cout << "Invalid option." << std::endl;
		}
	} while (done == false);

	return canvas;
}

Canvas* CanvasLoader::newCanvas() {

	bool validName = false;
	do {
		std::string name;
		std::cout << "What is the name of your file? (be sure to include '.txt') : ";
		std::cin >> name;
		if (name.size() > 0) {
			validName = true;
			g_fileName = name;
		}
		else {
			std::cout << "Invalid name." << std::endl;
		}
	} while (validName == false);

	int width;
	std::cout << "What is the level width? : ";
	std::cin >> width;

	int height;
	std::cout << "What is the level height? : ";
	std::cin >> height;

	std::cout << "Name: " << g_fileName << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	return new Canvas(width, height, g_tileWidth, g_tileHeight, canvasTexture_);
}

Canvas* CanvasLoader::openCanvas() {

	std::string name;
	std::string fileName;
	std::ifstream file;

	do {
		std::cout << "Which file would you like to open? : ";
		std::cin >> name;
		fileName = name;

		name.insert(0, g_filePath);
		name.insert(name.size(), g_fileFormat);

		file.open(name);
		
		if (!file.is_open()) {
			std::cout << "File does not exist..." << std::endl;
		}
	} while (!file.is_open());

	g_fileName = fileName;

	char line[50];



	file.getline(line, 10, ',');
	int width = atoi(line);
	file.getline(line, 10, '\n');
	int height = atoi(line);
	Canvas* canvas = new Canvas(width, height, g_tileWidth, g_tileHeight, canvasTexture_);
	//Canvas* canvas = new Canvas(800, 600, g_tileWidth, g_tileHeight, canvasTexture_);

	// draw canvas
	while (!file.eof()) {
		file.getline(line, 10, ',');
		int x = atoi(line);
		file.getline(line, 10, ',');
		int y = atoi(line);
		file.getline(line, 30, '\n');
		int type = atoi(line);

		switch (type) {			
		case 0: {
			// Player
			SDL_Rect clip = { 40, 0, 20, 20 };
			canvas->setSpawn(x, y, Entity_Player, canvasTexture_, &clip); // TODO: will making a stack clip ruin this?	
			break;
		}
		case 1: {
			// Solid Tile
			SDL_Rect clip = { 20, 0, 20, 20 };
			canvas->draw(x, y, Entity_SolidTile, canvasTexture_, &clip);
			break;
		}
		case 2: {
			// Air Tile
			SDL_Rect clip = { 0, 20, 20, 20 };
			canvas->draw(x, y, Entity_AirTile, canvasTexture_, &clip);
			break;
		}
		case 3: {
			// Damage Tile
			SDL_Rect clip = { 20, 20, 20, 20 };
			canvas->draw(x, y, Entity_DamageTile, canvasTexture_, &clip);
			break;
		}
		case 4: {
			// Goal Tile
			SDL_Rect clip = { 0, 0, 20, 20 };
			canvas->draw(x, y, Entity_StageGoal, canvasTexture_, &clip);
			break;
		}
		}
	}
	file.close();

	return canvas;
}