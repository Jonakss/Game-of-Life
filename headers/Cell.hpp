#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <unistd.h>
#include <chrono>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Color.hpp"

class Cell{
private:
	Cell *neighborhood[8] = {};
	std::vector<Cell*> vneighborhood = {};
	std::vector<bool> ineighborhood = {};
	bool alive, pAlive;

	sf::RectangleShape body;
//	sf::Vector2f pos;
	sf::Color color;
public:
	Cell(sf::Vector2f p);
	~Cell();

	void random();
	bool isAlive();
	bool wasAlive();
	void draw(sf::RenderWindow* w);
	void updateColor();
	void update(float dt);
	void addNeighbor(Cell* c);
	std::vector<Cell*>* getNeighborhood();
	void addNeighbor(bool b);
	void clearNeighborhood();
	void setLive(bool b);
	void toggle();
};

#endif
