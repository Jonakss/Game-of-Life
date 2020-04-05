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

	this->window->display();
};

void Base::update(){
	this->updateEvents();
};

void Base::updateEvents(){
	while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed)
			this->window->close();
	}
};

void Base::run(){
	while(this->window->isOpen()){
		this->updateDt();
		this->update();
		this->render();
	}
};

