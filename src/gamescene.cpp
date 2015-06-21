#include "gamescene.hpp"
#include <sstream>
#include <string>
#include <iostream>
#define DELETEALL(a) for(int i=(a).size()-1;i>=0;i--) {  \
				delete (a)[i]; \
			   } \
			   (a).clear();
#define DESTROYALL(a) for(int i=(a).size()-1;i>=0;i--) {  \
				(a)[i]->kill(); \
			   }
sf::Font* GameScene::font=NULL;
static int probs[]={40000,30000,25000,10000,8000,7000,5000,3000};
GameScene::GameScene(double width,double height){
	this->height=height;
	this->width=width;
	this->player=new Fighter1();//Fighter(0,0,0,100,100,0.05,0.05,0);
	this->player->setGameEventListener(this);
	this->player->moveTo(width/2,height*8/9);
	this->score=0;
	this->paused=0;
	this->resume_remaining_time=10;
	this->round_count=10;
	if(GameScene::font==NULL){
		GameScene::font=new sf::Font();
		GameScene::font->loadFromFile(RES_DIR "/fonts/UbuntuMono-RI.ttf");
	}
	this->shape_bomblight=sf::RectangleShape(sf::Vector2f(0, 0));
	this->shape_bomblight.setSize(sf::Vector2f(this->width,this->height));
	this->shape_bomblight.setFillColor(sf::Color(255,255,255,255));
	this->bomb_explosing=0;
	this->bomb_alpha=255;
	this->level_isshowing=1;
	
	this->clock_leveltimer.restart();	
	this->text_score.setFont(*GameScene::font);
	this->text_score.setString("test");
	this->text_score.setCharacterSize(30);
	this->text_score.setColor(sf::Color::Blue);
	this->level=0;
	
	this->text_pause.setFont(*GameScene::font);
	this->text_pause.setString("--Press Enter to continue--");
	this->text_pause.setCharacterSize(25);
	this->text_pause.setColor(sf::Color::Blue);
	this->text_pause.setPosition(this->width/8,this->height/2);
	
	this->text_life.setFont(*GameScene::font);
	this->text_life.setString("1");
	this->text_life.setCharacterSize(40);
	this->text_life.setColor(sf::Color::Red);
	this->text_life.setPosition(this->width*5/8,0);
	
	this->text_hint.setFont(*GameScene::font);
	this->text_hint.setString(
					"    --Game over--\n" 
					"Press enter key to restart\n"
					"Press Q to quit..");
	this->text_hint.setCharacterSize(30);
	this->text_hint.setColor(sf::Color::Blue);
	this->text_hint.setPosition(this->width/10,this->height/4);

	this->text_levelhint.setFont(*GameScene::font);
	this->text_levelhint.setString("Level un");
	this->text_levelhint.setCharacterSize(30);
	this->text_levelhint.setColor(sf::Color::Blue);
	this->text_levelhint.setPosition(this->width/3,this->height*2/3);
	
	this->text_bombs.setFont(*GameScene::font);
	this->text_bombs.setString("1");
	this->text_bombs.setCharacterSize(30);
	this->text_bombs.setColor(sf::Color::Red);
	this->text_bombs.setPosition(0,this->height*7/8);
	//this->text_score.setStyle(sf::Text::Bold | sf::Text::Underlined);
}
GameScene::~GameScene(){
	delete this->player;
}
void GameScene::add_enemy(){
	int x=rand()%probs[this->level];
	int x1=rand()%((int)this->width);
	//if(x>24996){
		Fighter* e=NULL;
		if(x<=5){
			e=new Enemy1();
		}
		else if(x>5&&x<=10){
			e=new Enemy3();
		}
		else if(x==21){
			e=new Enemy2();
		}
		if(e!=NULL){
			e->setGameEventListener(this);			
			e->moveTo(x1,-e->height/2+1);
			e->AcellarateY(1);
			this->fighters.push_back(e);
		}
	//}
}
void GameScene::check_hits(){
	for(int i=this->bullets.size()-1;i>=0;i--){
		for(int j=this->fighters.size()-1;j>=0;j--){
			if(this->bullets[i]->hitTest(this->fighters[j])){
				if(!this->fighters[j]->isKilled()) this->score++;
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
		}
	}
	for(int i=this->wboxes.size()-1;i>=0;i--){
		if(this->player->hitTest(this->wboxes[i])){
			this->wboxes[i]->hit(this->player);
			delete this->wboxes[i];
			this->wboxes.erase(this->wboxes.begin()+i);
			
		}
	}
}
void GameScene::react(double dt){
	if(!this->paused){
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
		for(int i=this->wboxes.size()-1;i>=0;i--){
			this->wboxes[i]->react(dt);
		}
	}
	this->check_ranges();
	this->check_hits();
	if(this->clock_leveltimer.getElapsedTime().asSeconds()>60&&!this->player->isKilled()&&!this->paused){
		this->clock_leveltimer.restart();
		this->level++;
		this->level_isshowing=1;
		this->clock_levelhint.restart();
		//std::cout<<"next level"<<std::endl;
	}
}
void GameScene::restart(){
	this->score=0;
	/*DELETEALL(this->fighters);
	DELETEALL(this->bullets);
	DELETEALL(this->bullets_e);
	DELETEALL(this->wboxes);*/
	delete this->player;
	this->player=new Fighter1();//Fighter(0,0,0,100,100,0.05,0.05,0);
	this->player->setGameEventListener(this);
	this->player->moveTo(width/2,height*8/9);
}
void GameScene::pause(){
	if(!this->player->isDestroyed()) this->paused=1;
}
void GameScene::resume(){
	this->paused=0;
}
void GameScene::fire_enemy(){
	if(!this->player->isDestroyed()){
		for(int i=this->fighters.size()-1;i>=0;i--){
			if(!this->fighters[i]->isKilled()) this->fighters[i]->AimAndFire(this->player);
		}
	}
}
void GameScene::check_ranges(){
	for(int i=this->bullets.size()-1;i>=0;i--){
		if(this->bullets[i]->x>this->width || this->bullets[i]->x<0 || this->bullets[i]->y<0 ||this->bullets[i]->y>this->height){
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin()+i);
		}
	}
	for(int i=this->wboxes.size()-1;i>=0;i--){
		if(this->wboxes[i]->x>this->width || this->wboxes[i]->x<0 || this->wboxes[i]->y<0 ||this->wboxes[i]->y>this->height){
			delete this->wboxes[i];
			this->wboxes.erase(this->wboxes.begin()+i);
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
int GameScene::isRunning(){
	return !this->player->isDestroyed();
}
void GameScene::player1_move_left(double dt){
	if(this->isRunning()) this->player->AcellarateX(-1);
}
void GameScene::player1_move_right(double dt){
	if(this->isRunning()) this->player->AcellarateX(1);
}
void GameScene::player1_move_down(double dt){
	if(this->isRunning()) this->player->AcellarateY(1);
}
void GameScene::player1_move_up(double dt){
	if(this->isRunning()) this->player->AcellarateY(-1);
}
void GameScene::player1_stop(){
	if(this->isRunning()) this->player->Stop();
}
void GameScene::player1_fire(){
	if(this->isRunning()) this->player->fire();
}
void GameScene::onFireBullet(Bullet* b){
	this->bullets.push_back(b);
}
void GameScene::onEnemyFireBullet(Bullet* b){
	this->bullets_e.push_back(b);
}
void GameScene::keypress(sf::Keyboard::Key k){
	if(!this->player->isDestroyed()){
		if(k==sf::Keyboard::Return){
			if(this->ispaused()){
				this->resume();
			}
			else{
				this->pause();
			}
		}
		else if(k==sf::Keyboard::B){
			this->player->ReleaseBomb();
		}
	}
	else {
		if(k==sf::Keyboard::Return){
			this->restart();
		}
	}
}
void GameScene::DrawObjs(sf::RenderWindow* window){
	
	//vertices test----------------------------------------
	/*for(int i=this->wboxes.size()-1;i>=0;i--){
		sf::ConvexShape convex;
		convex.setPointCount(this->wboxes[i]->verticescount);
		for(int j=0;j<this->wboxes[i]->verticescount;j++){
			convex.setPoint(j,sf::Vector2f(this->wboxes[i]->vertx[j],this->wboxes[i]->verty[j]));
		}
		convex.setPosition(this->wboxes[i]->x,this->wboxes[i]->y);
		window->draw(convex);
	}*/
	
	//-----------------------------------------------------
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
	for(int i=this->wboxes.size()-1;i>=0;i--){
		window->draw(*this->wboxes[i]);
	}
	if(this->bomb_explosing){
		window->draw(this->shape_bomblight);
		if(this->bomb_alpha>0) this->bomb_alpha--;
		else this->bomb_explosing=0;
		this->shape_bomblight.setFillColor(sf::Color(255,255,255,this->bomb_alpha));
	}
	this->draw_text(window);
	if(this->paused){
		window->draw(this->text_pause);
	}
}
void GameScene::onFighterDestroyed(Fighter* f){
	if(f==this->player){
		//TODO:Game over
		
		
	}
	else {
		//this->score++;
	}
}
void GameScene::onWboxApear(Wbox* b){
	this->wboxes.push_back(b);
}
void GameScene::onBombExplose(){
	/*DESTROYALL(this->fighters);
	DELETEALL(this->bullets);
	DELETEALL(this->bullets_e);
	DELETEALL(this->wboxes);
	this->bomb_explosing=1;
	this->bomb_alpha=255;*/
	DELETEALL(this->bullets_e);
	for(int i=0;i<300;i++){
		Bullet* b=new Bullet(1);
		b->moveTo(this->player->x,this->player->y);
		b->setVelocity(this->player->bullet_v*cos(2*3.14/300*i),this->player->bullet_v*sin(2*3.14/300*i));
		this->bullets.push_back(b);
	}
}
void GameScene::draw_text(sf::RenderWindow* window){
	static std::string levels[]={"un","deux","trois","quatre","cinq","six","sept","neuf"};
	std::ostringstream os;
	os<<"Score:";
	os<<this->score;
	this->text_score.setString(os.str());
	window->draw(this->text_score);
	std::string s="";
	std::string s2="";
	s2.append("BBBBB",this->player->getbombcount());
	this->text_bombs.setString(s2);
	window->draw(this->text_bombs);
	if(this->player->getLife()>0) {
		s.append("OOOOO",this->player->getLife());
	}
	else {
		window->draw(this->text_hint);
		this->paused=0;
		this->player->setGameEventListener(NULL);
	}
	this->text_life.setString(s);
	
	window->draw(this->text_life);
	
	if(this->level_isshowing){
		std::ostringstream os2;
		os2<<"Level ";
		os2<<levels[this->level];
		this->text_levelhint.setString(os2.str());
		window->draw(this->text_levelhint);
		if(this->clock_levelhint.getElapsedTime().asSeconds()>3){
			this->level_isshowing=0;
		}
	}
}



