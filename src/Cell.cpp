#include "../headers/Cell.hpp"

Cell::Cell(sf::Vector2f p){
//	this->pos = p;
	int a = rand() % 100;
	if (a>50){
		this->alive = this->pAlive = true;
	}else{
		this->alive = this->pAlive = false;
	}
	this->body = sf::RectangleShape();
	this->body.setPosition(p);
	this->body.setSize(sf::Vector2f(10,10));
};;

Cell::~Cell(){
//	delete this->neighborhood;
};

bool Cell::isAlive(){
	return this->alive;
};

bool Cell::wasAlive(){
	return this->pAlive;
};

void Cell::draw(sf::RenderWindow* w){
	if(this->alive)
		this->body.setFillColor(sf::Color::Blue);
	else
		this->body.setFillColor(sf::Color::Red);	
	
	w->draw(body);
};

void Cell::update(float dt){
	this->pAlive = this->alive;
	int c = 0, i =0;
	while(i<8 && c<3){
		if(this->neighborhood[i] != nullptr){
			if(this->neighborhood[i]->wasAlive()) c++;
		}
		i++;
	}

	if(this->alive)
		if(c<2 || c>3) this->alive = false;
	else
		if(c=3) this->alive = true;

	if(this->alive)
		this->body.setFillColor(sf::Color::Blue);
	else
		this->body.setFillColor(sf::Color::Red);	
};

void Cell::addNeighbor(Cell *c){
	int i = 0;
	if(c != nullptr)
		while(i<8 && neighborhood[i] == nullptr){
			this->neighborhood[i] = c;
			i++;
		};
};



