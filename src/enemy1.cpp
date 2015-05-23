#include "enemy1.hpp"
Enemy1::Enemy1():Fighter(2){
	this->clearVertices();
	this->addVertex(0,-this->height/2);
	this->addVertex(this->width/2,0);
	this->addVertex(0,this->height*3/8);
	this->addVertex(-this->width/2,0);
}
Enemy1::~Enemy1(){
	
} 
