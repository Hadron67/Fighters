#include "fighter1.hpp"
Fighter1::Fighter1():Fighter(1)/*Player*/{
	this->initVertices();
}
Fighter1::~Fighter1(){
	
}
Fighter1* Fighter1::setWeaponType(WeaponType wt){
	this->wt=wt;
	return this;
}
void Fighter1::react(double dt){
	if(!this->killed){		
		if(this->cay<0){
			this->setTextureRect(sf::IntRect(this->x0[0],this->y0[0],this->width,this->height));
		}
		else{
			this->setTextureRect(sf::IntRect(this->x0[1],this->y0[1],this->width,this->height));
		}
	}
	this->Fighter::react(dt);
}
void Fighter1::destroy(){
	//TODO:add destroying animation
	this->Fighter::destroy();
}
void Fighter1::ffire(GameEventListener* wi){
	this->Fighter::ffire(wi);
}
void Fighter1::initVertices(){
	this->clearVertices();
	this->addVertex(0,-this->height*3/8);
	this->addVertex(-this->width/2,this->height/5);
	this->addVertex(this->width/2,this->height/5);
}
