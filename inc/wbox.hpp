#ifndef WBOX_HPP
#define WBOX_HPP
#include <SFML/Graphics.hpp>
#include "hitTestable.hpp"
#include "wboxlistener.hpp"
struct wbox_Properties{
	int height;
	int width;
	int x0;
	int y0;
	
};
class GameScene;
class Wbox:public sf::Sprite,public HitTestable{
	private:
	protected:
		double height,width;
		double x,y,vx,vy;
	public:
		Wbox(struct wbox_Properties* p);
		Wbox(int type);
		virtual ~Wbox();
		virtual void moveTo(double x,double y);
		virtual void react(double dt);
		virtual void setVelocity(double vx,double vy);
		virtual void hit(WboxListener* f){}
	friend class GameScene;
};
class BulletBox:public Wbox{
	public:
		BulletBox();
		virtual ~BulletBox();
		virtual void hit(WboxListener* f);
};
class BombBox:public Wbox{
	private:
	
	public:
		BombBox();
		virtual ~BombBox();
		virtual void hit(WboxListener* f);
		
};
#endif
