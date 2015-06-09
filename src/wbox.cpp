#include "wbox.hpp"
#include "resources.hpp"
Wbox::Wbox(struct wbox_Properties* p){
	sf::RectangleShape(sf::Vector2f(p->width,p->height));
	this->x=this->y=this->vx=this->vy=0;
	this->height=p->height;
	this->width=p->width;
	ResourceStore::loadTexture();
	this->setTexture(*ResourceStore::shoot);
	this->setTextureRect(sf::IntRect( p->x0, p->y0, p->width,  p->height));
	this->addVertex(-this->width/2,-this->height/2);
	this->addVertex(this->width/2,-this->height/2);
	this->addVertex(this->width/2,this->height/2);
	this->addVertex(-this->width/2,this->height/2);
}
Wbox::Wbox(int type){
	static wbox_Properties p[]={
		{88,58,267,398},
		{107,60,102,118}
	};
	new (this) Wbox(&p[type-1]);
}
Wbox::~Wbox(){
	
}
void Wbox::moveTo(double x,double y){
	this->x=x;
	this->y=y;
	this->moveto(this->x,this->y);
	this->setPosition(this->x-this->width/2,this->y-this->height/2);
}
void Wbox::setVelocity(double vx,double vy){
	this->vx=vx;
	this->vy=vy;
}
void Wbox::react(double dt){
	this->x+=this->vx*dt;
	this->y+=this->vy*dt;
	this->moveTo(this->x,this->y);
}

BulletBox::BulletBox():Wbox(1){
	this->clearVertices();
	this->addVertex(-this->width/2,-this->height/2);
	this->addVertex(this->width/2,-this->height/2);
	this->addVertex(this->width/2,this->height/2);
	this->addVertex(-this->width/2,this->height/2);
}
BulletBox::~BulletBox(){
	
}
void BulletBox::hit(WboxListener* f){
	f->onTouchBullet();
}

BombBox::BombBox():Wbox(2){
	
}
BombBox::~BombBox(){
	
}
void BombBox::hit(WboxListener* f){
	f->onTouchBomb();
}
