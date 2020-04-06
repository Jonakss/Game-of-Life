#include "../headers/Cell.hpp"

Cell::Cell(sf::Vector2f p){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	int a = rand() % 100;
	if (a>50){
		this->alive = this->pAlive = true;
	}else{
		this->alive = this->pAlive = false;
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
	usleep(100);
	w->draw(body);
};

void Cell::update(float dt){
	int c = 0;
	//for(int i = 0; i < this->vneighborhood.size(); i++){
	//	if(this->vneighborhood[i]->wasAlive()) c++;
	//}
	for(int i = 0; i < this->ineighborhood.size(); i++){
		if(this->ineighborhood[i]) c++;
	}
	
	//while(i<8){
	//	if(this->neighborhood[i] != nullptr && neighborhood[i]->wasAlive()){ 
	//		c++;
	//	}
	//	i++;
	//}
	this->pAlive = this->alive;
	if(this->alive)
		if(c<2 || c>3) this->alive = false;
	else{
//		std::cout << "I born!" << std::endl;
		if(c=3) this->alive = true;
	};

	if(this->alive)
		this->body.setFillColor(sf::Color::Blue);
	else
		this->body.setFillColor(sf::Color::Red);	
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
