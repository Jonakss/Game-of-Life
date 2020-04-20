#include "../headers/Base.hpp"

void Base::initWindow(){

	std::ifstream ifs("config/window.conf");

	sf::VideoMode windowConf(800,600);
	std::string title = "None";
	unsigned frameRateLimit = 120;
	bool vSync = false;

	if(ifs.is_open()){
		std::getline(ifs, title);
		ifs >> windowConf.width >> windowConf.height;
		ifs >> frameRateLimit;
		ifs >> vSync;
	}

	ifs.close();

	this->window = new sf::RenderWindow(windowConf, title);
	this->window->setFramerateLimit(frameRateLimit);
	this->window->setVerticalSyncEnabled(vSync);

	this->cursor = sf::RectangleShape();
	this->cursor.setPosition(0, 0);
	this->cursor.setSize(sf::Vector2f(10,10));
	this->cursor.setFillColor(sf::Color::Transparent);
	this->cursor.setOutlineThickness(1);
	this->cursor.setOutlineColor(sf::Color::Green);

	for(int i = 0; i < this->COLS; i++){
		for(int j = 0; j < this->ROWS; j++){
			this->board[i][j] = new Cell(sf::Vector2f(i*10/*+i*1*/, j*10/*+j*1*/));
		}
	}
	for(int i = 0; i < this->COLS; i++){
		for(int j = 0; j < this->ROWS; j++){
			for(int a = -1; a < 2; a++){
				for(int b = -1; b < 2; b++){
					int x = (a+i+this->COLS)%this->COLS;
					int y = (b+j+this->ROWS)%this->ROWS;
					if(!((a == 0) && (b == 0))){
						this->board[i][j]->addNeighbor(this->board[x][y]->wasAlive());
					}
				}
			}
		}
	}
};

Base::Base(){
	this->initWindow();

};

Base::~Base(){
	delete this->window;
};

void Base::updateDt(){
	//Update the dt variable with the time it takes to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
};


void Base::render(){
	this->window->clear();

	//render functions
	for(int i = 0; i < this->COLS; i++){
		for(int j =0; j < this->ROWS; j++){
			this->board[i][j]->draw(this->window);
		}
	}

	this->window->draw(this->cursor);

	this->window->display();
};

void Base::update(){

	for(int i = 0; i < this->COLS; i++){
		for(int j = 0; j < this->ROWS; j++){
			this->board[i][j]->clearNeighborhood();
			for(int a = -1; a < 2; a++){
				for(int b = -1; b < 2; b++){
					int x = (a+i+this->COLS)%this->COLS;
					int y = (b+j+this->ROWS)%this->ROWS;
					if(!((a == 0) && (b==0))){
						this->board[i][j]->addNeighbor(this->board[x][y]->wasAlive());
					}
				}
			}
		}
	}
	for(int i = 0; i < this->COLS; i++){
		for(int j = 0; j < this->ROWS; j++){
			this->board[i][j]->update(this->dt);
		}
	}

};

void Base::updateEvents(){
	while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed)
				this->window->close();
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::P)
				this->paused = !this->paused;
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::R){
				for(int i = 0; i < this->COLS; i++){
					for(int j = 0; j < this->ROWS; j++){
						unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
						srand(seed);
						int a = rand() % 100;
						this->board[i][j]->setLive(a>75);
					}
				}
			};
		if(this->event.type == sf::Event::MouseMoved){
			int mx = sf::Mouse::getPosition(*this->window).x/10;
			int my = sf::Mouse::getPosition(*this->window).y/10;
			if(((mx>=0)&&(mx<COLS))&&((my>=0)&&(my<ROWS)))
				this->cursor.setPosition(mx*10, my*10);
		}
		if (this->event.type == sf::Event::MouseButtonPressed){
				int mx = sf::Mouse::getPosition(*this->window).x/10;
				int my = sf::Mouse::getPosition(*this->window).y/10;
				if(((mx>=0)&&(mx<COLS))&&((my>=0)&&(my<ROWS))){
					if (event.mouseButton.button == sf::Mouse::Left)
						this->board[mx][my]->toggle();
					else if (event.mouseButton.button == sf::Mouse::Right)
						continue;
					else if (event.mouseButton.button == sf::Mouse::Middle)
						continue;
				};
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
			for(int i = 0; i < this->COLS; i++){
				for(int j = 0; j < this->ROWS; j++){
					this->board[i][j]->setLive(false);
				}
			}
		}
	}
};

void Base::run(){
	while(this->window->isOpen()){
		this->updateEvents();
		if(!this->paused){
			this->updateDt();
			this->update();
		}
		this->render();
	}
};
