#include "enemy2.hpp"
Enemy2::Enemy2():Fighter(3){
	this->clearVertices();
	this->addVertex(-this->width/2,-this->height/4);
	this->addVertex(this->width/2,-this->height/4);
	this->addVertex(0,this->height/2);
}
Enemy2::~Enemy2(){
	
}
