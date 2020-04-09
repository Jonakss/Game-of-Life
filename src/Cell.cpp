#include "../headers/Cell.hpp"

Cell::Cell(sf::Vector2f p){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	int a = rand() % 100;
	if (a>50){
		this->alive = true;
		this->pAlive = true;
	}else{
		this->alive = false;
		this->pAlive = false;
	}
	this->body = sf::RectangleShape();
	this->body.setPosition(p);
	this->body.setSize(sf::Vector2f(10,10));
};

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
	w->draw(body);
	//usleep(100);
};

void Cell::update(float dt){
	int c = 0;
	this->pAlive = this->alive;
	for(int i = 0; i < this->ineighborhood.size(); i++){
		if(this->ineighborhood[i]) c++;
	};
	if(this->alive == true){
		if((c<2) || (c>3)){
		   	this->alive = false;
		};
	}else{
		if(c==3){
		   	this->alive = true;
		};
	};
	if(this->alive == true){
		this->body.setFillColor(sf::Color::Red);
	}else{
		this->body.setFillColor(sf::Color::Black);
	};
};

void Cell::addNeighbor(Cell* c){
	int i = 0;
	if(c!=nullptr)
	while(i<8){
		if(this->neighborhood[i] != nullptr) i++;
		else{
			this->neighborhood[i] = c;
			i=9;
		}
		i++;
	}
};

std::vector<Cell*>* Cell::getNeighborhood(){
	return &this->vneighborhood;
};

void Cell::addNeighbor(bool b){
	this->ineighborhood.push_back(b);
};

void Cell::clearNeighborhood(){
	this->ineighborhood.clear();
};

void Cell::revive(){
	this->pAlive = this->alive = true;
	this->body.setFillColor(sf::Color::Red);
}
