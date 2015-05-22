#include "gamescene.hpp"
#include <iostream>
GameScene::GameScene(double width,double height){
	this->height=height;
	this->width=width;
	this->player=new Fighter1();//Fighter(0,0,0,100,100,0.05,0.05,0);
	this->player->moveTo(width/2,height*8/9);
}
GameScene::~GameScene(){
	delete this->player;
}
void GameScene::add_enemy(){
	int x=rand()%50000;
	int x1=rand()%((int)this->width);
	if(x>49996){
		Fighter* e;
		if(x==49997){
			e=new Enemy1();
		}
		else if(x==49998){
			e=new Enemy3();
		}
		else if(x==49999){
			e=new Enemy2();
		}
		e->moveTo(x1,-e->height/2+1);
		e->AcellarateY(1);
		this->fighters.push_back(e);
	}
}
void GameScene::check_hits(){
	for(int i=this->bullets.size()-1;i>=0;i--){
		for(int j=this->fighters.size()-1;j>=0;j--){
			if(this->bullets[i]->hitTest(this->fighters[j])){
				//std::cout<<"it works!"<<std::endl;
				this->fighters[j]->hit(this->bullets[i]);
				delete this->bullets[i];
				this->bullets.erase(this->bullets.begin()+i);
				break;
			}
		}
	}
	for(int i=this->bullets_e.size()-1;i>=0;i--){
		if(this->player->hitTest(this->bullets_e[i])){
			this->player->hit(this->bullets_e[i]);
			delete this->bullets_e[i];
			this->bullets_e.erase(this->bullets_e.begin()+i);
			break;
		}
	}
}
void GameScene::react(double dt){
	this->add_enemy();
	this->fire_enemy();
	this->player->react(dt);
	int size=this->fighters.size();
	for(int i=0;i<size;i++){
		this->fighters[i]->react(dt);
	}
	
	size=this->bullets.size();
	for(int i=0;i<size;i++){
		this->bullets[i]->react(dt);
	}
	for(int i=this->bullets_e.size()-1;i>=0;i--){
		this->bullets_e[i]->react(dt);
	}
	this->check_ranges();
	this->check_hits();
}
void GameScene::fire_enemy(){
	for(int i=this->fighters.size()-1;i>=0;i--){
		this->fighters[i]->AimAndFire(this->player,this);
	}
}
void GameScene::check_ranges(){
	for(int i=this->bullets.size()-1;i>=0;i--){
		if(this->bullets[i]->x>this->width || this->bullets[i]->x<0 || this->bullets[i]->y<0 ||this->bullets[i]->y>this->height){
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin()+i);
		}
	}
	for(int i=this->bullets_e.size()-1;i>=0;i--){
		if(this->bullets_e[i]->x>this->width || this->bullets_e[i]->x<0 || this->bullets_e[i]->y<0 ||this->bullets_e[i]->y>this->height){
			delete this->bullets_e[i];
			this->bullets_e.erase(this->bullets_e.begin()+i);
		}
	}
	for(int i=this->fighters.size()-1;i>=0;i--){
		if(this->fighters[i]->x>this->width+this->fighters[i]->width/2 || this->fighters[i]->x<-this->fighters[i]->width/2 || this->fighters[i]->y<-this->fighters[i]->height/2 ||this->fighters[i]->y>this->height+this->fighters[i]->height/2||this->fighters[i]->isDestroyed()){
			delete this->fighters[i];
			this->fighters.erase(this->fighters.begin()+i);
		}
	}
	if(this->player->x<0){
		this->player->vx=-this->player->vx;
		this->player->x=0;
	}
	if(this->player->x>this->width){
		this->player->vx=-this->player->vx;
		this->player->x=this->width;
	}
	if(this->player->y<0){
		this->player->vy=-this->player->vy;
		this->player->y=0;
	}
	if(this->player->y>this->height){
		this->player->vy=-this->player->vy;
		this->player->y=this->height;
	}
}
void GameScene::player1_move_left(double dt){
	this->player->AcellarateX(-1);
}
void GameScene::player1_move_right(double dt){
	this->player->AcellarateX(1);
}
void GameScene::player1_move_down(double dt){
	this->player->AcellarateY(1);
}
void GameScene::player1_move_up(double dt){
	this->player->AcellarateY(-1);
}
void GameScene::player1_stop(){
	/*this->player->setVx(this->player->getVx()/1.001);
	this->player->setVy(this->player->getVy()/1.001);*/
	this->player->Stop();
}
void GameScene::player1_fire(){
	this->player->fire(this);
}
void GameScene::FireBullet(Bullet* b){
	this->bullets.push_back(b);
}
void GameScene::FireBullet_e(Bullet* b){
	this->bullets_e.push_back(b);
}
void GameScene::DrawObjs(sf::RenderWindow* window){
	window->draw(*this->player);
	for(int i=this->bullets.size()-1;i>=0;i--){
		window->draw(*this->bullets[i]);
	}
	for(int i=this->bullets_e.size()-1;i>=0;i--){
		window->draw(*this->bullets_e[i]);
	}
	for(int i=this->fighters.size()-1;i>=0;i--){
		window->draw(*this->fighters[i]);
	}
}




