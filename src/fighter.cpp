#include "fighter.hpp"
#include "resources.hpp"
#include <math.h>
#include<iostream>

Fighter::Fighter(int group,double x=0,double y=0,double height=10,double width=10,double ax=0.1,double ay=0.1,double bullet_v=2,int which=1){
	
	sf::RectangleShape(sf::Vector2f(width, height));
	this->group=group;
	this->x=x;
	this->y=y;
	this->height=height;
	this->width=width;
	this->ax=ax;
	this->ay=ay;
	ResourceStore::loadTexture();
	this->setTexture(*ResourceStore::shoot);
	this->setTextureRect(sf::IntRect(0, 100,width, height));
	this->destroyed=0;
	this->killed=0;
	this->whichFrame=0;
	this->vx=this->vy=0;
	this->destroy_interval_time=1;
	this->initVertices();
	this->listener=NULL;
}
Fighter::Fighter(struct fighter_Properties* p){
	this->cax=this->cay=0;
	this->listener=NULL;
	sf::RectangleShape(sf::Vector2f(p->width, p->height));
	this->group= p->group;
	this->x=0;
	this->y=0;
	this->vx=this->vy=0;
	this->height= p->height;
	this->width= p->width;
	this->ax= p->ax;
	this->ay= p->ay;
	this->bullet_v=p->bullet_v;
	ResourceStore::loadTexture();
	this->setTexture(*ResourceStore::shoot);
	this->setTextureRect(sf::IntRect( p->x0[0], p->y0[0], p->width,  p->height));
	this->initVertices();
	this->destroyed=0;
	this->killed=0;
	this->destroy_interval_time=0.1;
	this->whichFrame=0;
	this->life=p->life;
	this->bullet_t=p->bullet_t;
	int i;
	for(i=0;p->x0[i]<1000;i++){
		this->x0[i]=p->x0[i];
		this->y0[i]=p->y0[i];
	}
	this->x0[i]=10000;
	this->y0[i]=10000;
}
Fighter::Fighter(int type){
	static struct fighter_Properties p[]={
		//player
		{0,5,126,102,{0,165,165,330,330,432,10000},{99,360,234,624,498,624,10000},0.05,0.05,4,0.1},
		//enermies
		{1,3,99,69,{0,432,534,603,672,741,10000},{0,525,655,655,653,653,10000},0.02,0.02,2,2},
		{1,1,43,57,{534,267,873,267,930,10000},{612,347,697,296,697,10000},0.03,0.03,2,2},
		{1,10,258,169,{335,504,0,0,839,165,673,0,10000},{750,750,486,225,748,486,748,747,10000},0.01,0.01,2,2}
	};
	new (this) Fighter(&p[type-1]);
}
Fighter::~Fighter(){
	
}
void Fighter::initVertices(){
	this->addVertex(-this->width/2,-this->height/2);
	this->addVertex(this->width/2,-this->height/2);
	this->addVertex(this->width/2,this->height/2);
	this->addVertex(-this->width/2,this->height/2);
}
void Fighter::setVx(double vx){
	this->vx=vx;
}
void Fighter::setVy(double vy){
	this->vy=vy;
}
void Fighter::moveTo(double x,double y){
	this->x=x;
	this->y=y;
	this->moveto(this->x,this->y);
	this->setPosition(this->x-this->width/2,this->y-this->height/2);
}
int Fighter::isKilled(){
	return this->killed;
}
void Fighter::setGameEventListener(GameEventListener* listener){
	this->listener=listener;
}
double Fighter::getax(){
	return this->ax;
}
double Fighter::getay(){
	return this->ay;
}
double Fighter::getWidth(){
	return this->width;
}
double Fighter::getHeight(){
	return this->height;
}
double Fighter::getVx(){
	return this->vx;
}
double Fighter::getVy(){
	return this->vy;
}
void Fighter::AcellarateX(float r){
	this->cax+=r*this->ax;
}
void Fighter::AcellarateY(float r){
	this->cay+=r*this->ay;
}
void Fighter::Stop(){
	this->cax=this->cay=0;
}
int Fighter::getLife(){
	return this->life;
}
void Fighter::react(double dt){
	this->checkDestroying();
	this->vx+=this->cax*dt;
	this->vy+=this->cay*dt;
	this->x+=this->vx*dt;
	this->y+=this->vy*dt;
	this->vx/=1.0005;
	this->vy/=1.0005;
	if(abs(this->vx)<0) this->vx=0;
	if(abs(this->vy)<0) this->vy=0;
	this->moveTo(this->x,this->y);
}
int Fighter::checkDestroying(){
	if(this->killed){
		this->destroy();
		return 1;
	}
	return 0;
}
void Fighter::fire(){
	if(this->clock_fire.getElapsedTime().asSeconds()>this->bullet_t){
		this->clock_fire.restart();
		this->ffire();
	}
	
}
void Fighter::ffire(){
	if(this->listener!=NULL){
		Bullet* b=new Bullet(1);
		b->setVelocity(this->vx,this->vy-this->bullet_v);
		b->moveTo(this->x,this->y);
		this->listener->onFireBullet(b);
	}
}
void Fighter::hit(Bullet* b){
	this->life-=b->getLifeKill();
	if(this->life<=0){
		this->Stop();
		this->killed=1;
	}
}
int Fighter::isDestroyed(){
	return this->destroyed;
	std::cout<<this->destroyed<<std::endl;
}
void Fighter::AimAndFire(Fighter* target){
	if(this->clock_fire.getElapsedTime().asSeconds()>this->bullet_t){
		this->clock_fire.restart();
		if(this->listener!=NULL){
			Bullet* b=new Bullet(2);
			b->moveTo(this->x,this->y);
			double d=sqrt((target->x-this->x)*(target->x-this->x)+(target->y-this->y)*(target->y-this->y));
			b->setVelocity((target->x-this->x)/d*this->bullet_v,(target->y-this->y)/d*this->bullet_v);
			this->listener->onEnemyFireBullet(b);
		}
	}
}
void Fighter::destroy(){
	if(this->clock_destroy.getElapsedTime().asSeconds()>=this->destroy_interval_time){
		this->clock_destroy.restart();
		if(this->x0[this->whichFrame]<1000){
			this->whichFrame++;
			this->setTextureRect(sf::IntRect(this->x0[this->whichFrame],this->y0[this->whichFrame],this->width,this->height));
		}
		else {
			this->destroyed=1;
			if(this->listener!=NULL) this->listener->onFighterDestroyed(this);
		}
	}
	
	
}
