#include "MainWindow.hpp"
#include<vector>
using namespace sf;
MainWindow::MainWindow():RenderWindow(VideoMode(450,600),"Experiment"),GameScene(450,600){
	sf::Texture* texture=new sf::Texture();
	if(texture->loadFromFile(RES_DIR "/img/background.png")){
		this->sp_bg.setTexture(*texture);
	}
	this->keystate=0;
}
MainWindow::~MainWindow(){
	delete this->sp_bg.getTexture();
}
void MainWindow::MainLoop(){
	sf::Clock clock;
	while(this->isOpen()){
		Event event;
		while(this->pollEvent(event)){
			if(event.type==Event::Closed){
				this->close();
			}
			if(event.type==Event::KeyPressed){
				if(event.key.code==sf::Keyboard::Return){
					if(this->ispaused()){
						this->resume();
					}
					else{
						this->pause();
					}
				}
			}
		}
		double t=clock.restart().asSeconds()*100;
		this->check_operates(t);
		this->react(t);
		this->clear();
		this->draw(this->sp_bg);
		this->DrawObjs(this);
		this->display();
	}
}
void MainWindow::check_operates(double dt){
	this->player1_stop();
	if(Keyboard::isKeyPressed(Keyboard::Left)){
		this->player1_move_left(dt);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right)){
		this->player1_move_right(dt);
	}
	if(Keyboard::isKeyPressed(Keyboard::Up)){
		this->player1_move_up(dt);
	}
	if(Keyboard::isKeyPressed(Keyboard::Down)){
		this->player1_move_down(dt);
	}
	if(Keyboard::isKeyPressed(Keyboard::Space)){
		this->player1_fire();
	}
	
}
