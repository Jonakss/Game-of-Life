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

	for(int i = 0; i < this->COLS; i++){
		for(int j = 0; j < this->ROWS; j++){
			this->board[i][j] = new Cell(sf::Vector2f(i*10+i*1, j*10+j*1));
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
		switch(this->event.type){
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::MouseButtonPressed:
				if(this->event.mouseButton.button == sf::Mouse::Left){
					int mX = this->event.mouseButton.x;
					int mY = this->event.mouseButton.y;
					if(mX > 0 && mX < (this->COLS * 10) && mY > 0 && mY < (this->COLS * 10)){
						this->board[(mX/10)][(mY/10)]->revive();
						std::cout << "Mouse pos: ("<< mX << ", " << mY << ")." <<std::endl;
					}
				}
				break;
			case sf::Event::KeyPressed:
				switch(this->event.key.code){
					case sf::Keyboard::P:
						this->pause = !this->pause;
						break;
					default: break;
				};
			default:
				break;
		}
	}
};

void Base::run(){
	while(this->window->isOpen()){
		this->updateEvents();
		if(!pause){
			this->update();
			this->updateDt();
			this->render();
		};
	}
};

