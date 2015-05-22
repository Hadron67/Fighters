#include "fighter1.hpp"
Fighter1::Fighter1():Fighter(1)/*Player*/{
	
}
Fighter1::~Fighter1(){
	
}
Fighter1* Fighter1::setWeaponType(WeaponType wt){
	this->wt=wt;
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
