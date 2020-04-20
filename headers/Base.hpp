#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>


#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "../headers/Cell.hpp"

class Base{
private:
	static const int COLS=25;
	static const int ROWS=25;

	const int HEIGHT = 800;
	const int WIDTH = 600;
	const char* TITLE = "SFML BASE";

	sf::RenderWindow* window;
	sf::Event event;

	sf::RectangleShape cursor;

	//Clock system
	sf::Clock dtClock;
	//delta time
	float dt;

	Cell *board[COLS][ROWS];

	bool paused = false;

	void initWindow();
public:
	Base();
	~Base();

	void updateDt();
	void render();
	void update();
	void updateEvents();
	void run();
};

#endif
