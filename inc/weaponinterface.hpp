#ifndef WEAPONINTERFACE_HPP
#define WEAPONINTERFACE_HPP
#include "bullet.hpp"
class WeaponInterface{
	public:
		WeaponInterface(){};
		virtual ~WeaponInterface(){};
		virtual void FireBullet(Bullet* b)=0;
		virtual void FireBullet_e(Bullet* b)=0;
};
#endif
