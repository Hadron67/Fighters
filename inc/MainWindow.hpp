#ifndef WINDOW_MAIN_HPP
#define WINDOW_MAIN_HPP
#include<SFML/Graphics.hpp>
#include<iostream>

#include "gamescene.hpp"
class MainWindow:public sf::RenderWindow,public GameScene {
	public:
		MainWindow();
		~MainWindow();
		void MainLoop();
	private:
		int keystate;
		sf::Sprite sp_bg;
		void check_operates(double dt);
};
#endif
