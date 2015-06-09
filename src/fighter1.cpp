#include "fighter1.hpp"
//#include <iostream>
#define PI 3.1415926
#include <math.h>
Fighter1::Fighter1():Fighter(1)/*Player*/{
	this->initVertices();
	this->wt=SingleBullet;
	this->bombcount=3;
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
void Fighter1::ffire(){
	if(this->listener!=NULL){
		if(this->wt==SingleBullet){
			Bullet* b1=new Bullet(1);
			b1->setVelocity(this->vx,this->vy-this->bullet_v);
			b1->moveTo(this->x,this->y-this->height/2);
			this->listener->onFireBullet(b1);
		}
		else if(this->wt==DoubleBullet){
			Bullet* b1=new Bullet(1);
			b1->setVelocity(this->vx,this->vy-this->bullet_v);
			b1->moveTo(this->x-b1->getWidth()/2,this->y-this->height/2);
			Bullet* b2=new Bullet(1);
			b2->setVelocity(this->vx,this->vy-this->bullet_v);
			b2->moveTo(this->x+b2->getWidth()/2,this->y-this->height/2);
			this->listener->onFireBullet(b1);
			this->listener->onFireBullet(b2);
		}
		else if(this->wt==TriScatter){
			for(double a=PI/6;a<=PI*5/6;a+=PI/3){
				Bullet* b=new Bullet(1);
				b->moveTo(this->x,this->y-this->height/2);
				b->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				this->listener->onFireBullet(b);
			}
		}
		else if(this->wt==DoubleTriScatter){
			for(double a=PI/6;a<=PI*5/6;a+=PI/3){
				Bullet* b1=new Bullet(1);
				Bullet* b2=new Bullet(1);
				b1->moveTo(this->x-b1->getWidth()/2,this->y-this->height/2);
				b1->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				b2->moveTo(this->x+b1->getWidth()/2,this->y-this->height/2);
				b2->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				this->listener->onFireBullet(b1);
				this->listener->onFireBullet(b2);
			}
		}
		else if(this->wt==PentaScatter){
			for(int i=0;i<5;i++){
				double a=PI/6+i*PI/6;
				Bullet* b=new Bullet(1);
				b->moveTo(this->x,this->y-this->height/2);
				b->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				this->listener->onFireBullet(b);
			}
		}
		else {
			for(int i=0;i<5;i++){
				double a=PI/6+i*PI/6;
				Bullet* b1=new Bullet(1);
				Bullet* b2=new Bullet(1);
				b1->moveTo(this->x-b1->getWidth()/2,this->y-this->height/2);
				b1->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				b2->moveTo(this->x+b1->getWidth()/2,this->y-this->height/2);
				b2->setVelocity(this->vx+this->bullet_v*cos(a),this->vy-this->bullet_v*sin(a));
				this->listener->onFireBullet(b1);
				this->listener->onFireBullet(b2);
			}
		}
	}
}
void Fighter1::initVertices(){
	this->clearVertices();
	this->addVertex(0,-this->height*3/8);
	this->addVertex(-this->width/2,this->height/5);
	this->addVertex(this->width/2,this->height/5);
}
int Fighter1::getbombcount(){
	return this->bombcount;
}
void Fighter1::ReleaseBomb(){
	if(this->bombcount>0){
		this->bombcount--;
		this->listener->onBombExplose();
	}
}
void Fighter1::onTouchBullet(){
	int t=(int)this->wt;
	t++;
	this->wt=(WeaponType)t;
	//std::cout<<"it works"<<std::endl;
}
void Fighter1::onTouchBomb(){
	if(this->bombcount<5){
		this->bombcount++;
	}
}
