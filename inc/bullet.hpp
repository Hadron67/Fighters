#ifndef BULLET_HPP
#define BULLET_HPP
#include<SFML/Graphics.hpp>
#include "hitTestable.hpp"
#ifndef RES_DIR
#define RES_DIR "./res"
#endif
class GameScene;
struct bullet_Properties{
	double height;
	double width;
	int life_kill;
	double x0;
	double y0;
	
};
class Bullet:public sf::Sprite,public HitTestable{
	private:
		double x,y,vx,vy,height,width;
		int life_kill;
	public:
		Bullet(struct bullet_Properties* b);
		Bullet(int type);
		double getWidth(){return this->width;}
		virtual ~Bullet();
		virtual void initVertices();
		Bullet* moveTo(double x,double y);
		Bullet* rotateTo(double r);
		Bullet* setVelocity(double vx,double vy);
		void react(double dt);
		int getLifeKill();
		friend class GameScene;
};
#endif
