#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Base{
private:
	const int HEIGHT = 800;
	const int WIDTH = 600;
	const char* TITLE = "SFML BASE";
	sf::RenderWindow* window;
	sf::Event event;

	//Clock
	sf::Clock dtClock;
	//delta time
	float dt;

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
