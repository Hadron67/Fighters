#ifndef ENEMY1_HPP
#define ENEMY1_HPP
#include "fighter.hpp"
class Enemy1:public Fighter{
	public:
		Enemy1();
		virtual ~Enemy1();
		virtual void destroy();
};
#endif
