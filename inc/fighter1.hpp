#ifndef FIGHTER1_HPP
#define FIGHTER1_HPP
#include "fighter.hpp"
#include<SFML/Graphics.hpp>
typedef enum{
	SingleBullet=0,
	DoubleBullet,
	TriScatter,
	PentaScatter,
	Laser,
	SingleQuatumnBullet,
	DouleQuatumnBullet,
	BL	
}WeaponType;
class Fighter1:public Fighter{
	private:
		WeaponType wt;
	public:
		Fighter1();
		~Fighter1();
		Fighter1* setWeaponType(WeaponType wt);
		virtual void destroy();
		virtual void react(double dt);
		virtual void ffire(WeaponInterface* wi);
};
#endif
