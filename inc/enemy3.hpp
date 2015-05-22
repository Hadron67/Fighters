#ifndef ENEMY3_HPP
#define ENEMY3_HPP
#include "fighter.hpp"
#include<SFML/Graphics.hpp>
class Enemy3:public Fighter{
	private:
		sf::Clock clock_frame;
	public:
		Enemy3();
		virtual ~Enemy3();
		virtual void react(double dt);
		virtual void AimAndFire(Fighter* target,WeaponInterface* wi);
};
#endif
