#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP
#include<vector>
#include<math.h>
#include "fighter.hpp"
#include "bullet.hpp"
#include "fighter1.hpp"
#include "enemy1.hpp"
#include "enemy2.hpp"
#include "enemy3.hpp"
#include "wbox.hpp"
#include "gameeventlistener.hpp"
class GameScene:public GameEventListener{
	private:
		double width,height;
		std::vector<Fighter*> fighters;
		std::vector<Bullet*> bullets;
		std::vector<Bullet*> bullets_e;
		std::vector<Wbox*> wboxes; 
		Fighter1* player;
		 //when object goes out of screen
		sf::Clock clock_player;
		sf::Text text_score;
		sf::Text text_pause;
		sf::Text text_life;
		sf::Text text_hint;
		sf::Text text_bombs;
		sf::Text text_levelhint;
		sf::Sprite sprite_pause;
		sf::RectangleShape shape_bomblight;
		sf::Clock clock_leveltimer;
		sf::Clock clock_levelhint;
		static sf::Font* font;
		void add_enemy();
		void fire_enemy();
		void check_ranges();
		void check_hits();
		void nextlevel();
		int paused;
		int level;
		int level_isshowing;
		int enemy_prob;
		int resume_remaining_time;
		int round_count;
		int bomb_explosing;
		int bomb_alpha;
		long score;
		void draw_text(sf::RenderWindow* window);
		void print_round_time();
		int isRunning();
	public:
		GameScene(double width,double height);
		virtual ~GameScene();
		Fighter* getPlayer(){return this->player;}
		std::vector<Bullet*>& getBullets(){return this->bullets;}
		int ispaused(){return this->paused;}
		void react(double dt);
		void player1_move_left(double dt);
		void player1_move_right(double dt);
		void player1_move_up(double dt);
		void player1_move_down(double dt);
		void player1_stop();
		void player1_fire();
		void pause();
		void resume();
		void DrawObjs(sf::RenderWindow* window);
		void keypress(sf::Keyboard::Key);
		void restart();
		//implementations
		void onFireBullet(Bullet* b);
		void onEnemyFireBullet(Bullet* b);
		void onFighterDestroyed(Fighter* f);
		void onWboxApear(Wbox* b);
		void onBombExplose();
		//friend class MainWindow;
};
#endif
