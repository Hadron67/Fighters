#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#define RES_DIR "./res/"
#include<SFML/Graphics.hpp>
#include "bullet.hpp"
#include "hitTestable.hpp"
#include "weaponinterface.hpp"
struct fighter_Properties{
	int group;
	int life;
	double height;
	double width;
	double x0[10];
	double y0[10];
	double ax;
	double ay;
	double bullet_v;
	double bullet_t;
};
class GameScene;
class Fighter:public sf::Sprite,public HitTestable{
	private :
		int life;
		double destroy_interval_time;
		int group;
		int destroyed;
		static sf::Texture* tex;
		sf::Clock clock;
		sf::Clock clock_destroy;
		int checkDestroying();
	protected:
		double bullet_v;
		double ax,ay;
		double cax,cay;
		sf::Clock clock_fire;
		double x,y,vx,vy;
		double bullet_t;
		int killed;
		double x0[10],y0[10];
		double height,width;
		int whichFrame;
	public:
		Fighter(int group,double x,double y,double height,double width,double ax,double ay,double bullet_v,int which);
		Fighter(struct fighter_Properties* p);
		Fighter(int type);
		virtual ~Fighter();
		virtual void initVertices();
		int getLife();
		void setVx(double vx);
		void setVy(double vy);
		void moveTo(double x,double y); //Hyper-distance interaction
		double getVx();
		double getHeight();
		double getWidth();
		double getVy();
		double getax();
		double getay();
		void AcellarateX(float r);// -1<=r<=1
		void AcellarateY(float r);
		void Stop();
		int isDestroyed();
		int isKilled();
		void fire(WeaponInterface* wi);
		virtual void destroy();
		virtual void ffire(WeaponInterface* wi);//firing more than one bullets
		
		virtual void AimAndFire(Fighter* target,WeaponInterface* wi); //for Enemies
		virtual void react(double dt);
		virtual void hit(Bullet* b);
		friend class GameScene;
};
#endif
