#ifndef GAMEEVENTLISTENER_HPP
#define GAMEEVENTLISTENER_HPP
#include "bullet.hpp"
class GameEventListener{
	public:
		GameEventListener(){};
		virtual ~GameEventListener(){};
		virtual void onFireBullet(Bullet* b)=0;
		virtual void onEnemyFireBullet(Bullet* b)=0;
};
#endif
