#ifndef FIGHTER1_HPP
#define FIGHTER1_HPP
#include<SFML/Graphics.hpp>
#include "wboxlistener.hpp"
#include "fighter.hpp"
typedef enum{
	SingleBullet=0,
	DoubleBullet,
	TriScatter,
	DoubleTriScatter,
	PentaScatter,
	DoublePentaScatter,
	Laser,
	SingleQuatumnBullet,
	DouleQuatumnBullet,
	BL
}WeaponType;
class Fighter1:public Fighter,public WboxListener{
	private:
		WeaponType wt;
		int bombcount;
	public:
		Fighter1();
		~Fighter1();
		Fighter1* setWeaponType(WeaponType wt);
		int getbombcount();
		void ReleaseBomb();
		virtual void destroy();
		virtual void react(double dt);
		virtual void ffire();
		virtual void initVertices();
		//implementations
		virtual void onTouchBullet();
		virtual void onTouchBomb();
};
#endif
