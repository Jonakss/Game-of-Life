#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <unistd.h>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Color.hpp"

class Cell{
private:
	Cell *neighborhood[8] = {};
	bool alive, pAlive;

	sf::RectangleShape body;
//	sf::Vector2f pos;
	sf::Color color;
public:
	Cell(sf::Vector2f p);
	~Cell();

	bool isAlive();
	bool wasAlive();
	void draw(sf::RenderWindow* w);
	void update(float dt);
	void addNeighbor(Cell *c);
};

#endif
