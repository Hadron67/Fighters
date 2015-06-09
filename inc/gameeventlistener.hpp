#ifndef GAMEEVENTLISTENER_HPP
#define GAMEEVENTLISTENER_HPP
class Bullet;
class Wbox;
class Fighter;
class GameEventListener{
	public:
		GameEventListener(){}
		virtual ~GameEventListener(){}
		virtual void onFireBullet(Bullet* b)=0;
		virtual void onEnemyFireBullet(Bullet* b)=0;
		virtual void onFighterDestroyed(Fighter* f)=0;
		virtual void onWboxApear(Wbox* b)=0;
		virtual void onBombExplose()=0;
};
#endif
