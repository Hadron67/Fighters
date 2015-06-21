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
void Enemy1::destroy(){
	this->Fighter::destroy();
	int t=rand()%20;
	if(this->isDestroyed()&&t<10){
		int select=rand()%2;
		//select=1;
		Wbox* b;
		if(select==0){
			b=new BulletBox();	
		}
		else {
			b=new BombBox();
		}
		b->moveTo(this->x,this->y);
		b->setVelocity(0,2);
		this->listener->onWboxApear(b);
	}
}
