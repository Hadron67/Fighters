//abstract class
#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP
#include<vector>
#include<math.h>
class MainWindow;
#include "weaponinterface.hpp"
#include "fighter.hpp"
#include "bullet.hpp"
#include "fighter1.hpp"
#include "enemy1.hpp"
#include "enemy2.hpp"
#include "enemy3.hpp"
class GameScene:public WeaponInterface{
	private:
		double width,height;
		std::vector<Fighter*> fighters;
		std::vector<Bullet*> bullets;
		std::vector<Bullet*> bullets_e;
		Fighter1* player;
		 //when object goes out of screen
		sf::Clock clock_player;
		void add_enemy();
		void fire_enemy();
		void check_ranges();
		void check_hits();
	public:
		GameScene(double width,double height);
		virtual ~GameScene();
		Fighter* getPlayer(){return this->player;}
		std::vector<Bullet*>& getBullets(){return this->bullets;}
		void react(double dt);
		void player1_move_left(double dt);
		void player1_move_right(double dt);
		void player1_move_up(double dt);
		void player1_move_down(double dt);
		void player1_stop();
		void player1_fire();
		void DrawObjs(sf::RenderWindow* window);
		//implementations
		void FireBullet(Bullet* b);
		void FireBullet_e(Bullet* b);
		//friend class MainWindow;
};
#endif
