#include "bullet.hpp"
#include<math.h>
#define PI 3.1415926
static double arctan(double x,double y){
	double theta=asin(y/sqrt(x*x+y*y));
	if(x>=0&&y>=0){
		return theta;
	}
	else if(x<0&&y>=0){
		return PI-theta;
	}
	else if(x<0&&y<0){
		return PI-theta;
	}
	else if(x>=0&&y<0){
		return 2*PI+theta;
	}
}
sf::Texture* Bullet::tex=NULL;
Bullet::Bullet(struct bullet_Properties* b){
	this->x=this->y=0;
	this->height=b->height;
	this->width=b->width;
	this->life_kill=b->life_kill;
	if(Bullet::tex==NULL){
		Bullet::tex=new sf::Texture();
		Bullet::tex->loadFromFile(RES_DIR "/img/shoot.png");
	}
	this->setTexture(*Bullet::tex);
	this->setTextureRect(sf::IntRect( b->x0, b->y0, b->width,  b->height));
	//for hitTest
	this->initVertices();
}
Bullet::Bullet(int type){
	static struct bullet_Properties b[]={
		{21,9,1,1004,978},
		{21,9,1,69,78}
	};
	new (this) Bullet(&b[type-1]);
}
Bullet::~Bullet(){
	
}
void Bullet::initVertices(){
	this->addVertex(-this->width/2,-this->height/2);
	this->addVertex(this->width/2,-this->height/2);
	this->addVertex(this->width/2,this->height/2);
	this->addVertex(-this->width/2,this->height/2);
}
Bullet* Bullet::moveTo(double x,double y){
	this->x=x;
	this->y=y;
	this->moveto(this->x,this->y);
	this->setPosition(this->x-this->width/2,this->y-this->height/2);
	return this;
}
Bullet* Bullet::rotateTo(double r){
	this->rotateto(r);
	this->setRotation(r*180/3.1415926+90);
	return this;
}
Bullet* Bullet::setVelocity(double vx,double vy){
	this->vx=vx;
	this->vy=vy;
	return this;
}
void Bullet::react(double dt){
	this->x+=this->vx*dt;
	this->y+=this->vy*dt;
	this->rotateTo(arctan(this->vx,this->vy));
	this->moveTo(this->x,this->y);
}
int Bullet::getLifeKill(){
	return this->life_kill;
}
