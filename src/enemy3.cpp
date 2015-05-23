#include "enemy3.hpp"
#include<math.h>
#define PI 3.1415926
Enemy3::Enemy3():Fighter(4){
	this->clearVertices();
	this->addVertex(-this->width*3/8,-this->height/2);
	this->addVertex(-this->width*5/16,-this->height/2);
	this->addVertex(-this->width*5/16,-this->height/8);
	this->addVertex(-this->width*5/16,this->height/8);
	this->addVertex(-this->width*5/16,-this->height/2);
	this->addVertex(this->width*3/8,-this->height/2);
	this->addVertex(this->width*3/8,this->height/6);
	this->addVertex(this->width/2,this->height/4);
	this->addVertex(this->width/8,this->height*7/16);
	this->addVertex(-this->width/8,this->height*7/16);
	this->addVertex(-this->width/2,this->height/4);
	this->addVertex(-this->width*3/8,this->height/6);
}
Enemy3::~Enemy3(){
	
}
void Enemy3::react(double dt){
	this->Fighter::react(dt);
	if(this->clock_frame.getElapsedTime().asSeconds()>0.2&&!this->killed){
		this->clock_frame.restart();
		if(this->whichFrame==0){
			this->whichFrame=1;
		}
		else {
			this->whichFrame=0;
		}
		this->setTextureRect(sf::IntRect(this->x0[this->whichFrame],this->y0[this->whichFrame],this->width,this->height));
	}
}
void Enemy3::AimAndFire(Fighter* target,WeaponInterface* wi){
	if(this->clock_fire.getElapsedTime().asSeconds()>this->bullet_t){
		this->Fighter::AimAndFire(target,wi);
		this->clock_fire.restart();
		Bullet* b1=new Bullet(2);
		Bullet* b2=new Bullet(2);
		Bullet* b3=new Bullet(2);
		Bullet* b4=new Bullet(2);
		b1->moveTo(this->x,this->y+this->height/2);
		b2->moveTo(this->x,this->y+this->height/2);
		b3->moveTo(this->x,this->y+this->height/2);
		b4->moveTo(this->x,this->y+this->height/2);
		b1->setVelocity(this->bullet_v,0);
		b4->setVelocity(-this->bullet_v,0);
		b2->setVelocity(this->bullet_v/1.414,this->bullet_v/1.414);
		b3->setVelocity(-this->bullet_v/1.414,this->bullet_v/1.414);
		wi->FireBullet_e(b1);
		wi->FireBullet_e(b2);
		wi->FireBullet_e(b3);
		wi->FireBullet_e(b4);
		
	}
}
