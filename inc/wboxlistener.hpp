#ifndef WBOXLISTENER_HPP
#define WBOXLISTENER_HPP
class WboxListener{
	public:
		WboxListener(){}
		virtual ~WboxListener(){}
		virtual void onTouchBullet()=0;
		virtual void onTouchBomb()=0;
};
#endif
