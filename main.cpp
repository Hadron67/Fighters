#include<SFML/Graphics.hpp>
#include<iostream>
#include "MainWindow.hpp"
#include "hitTestable.hpp"
using namespace std;
int main(int agv ,char* ags[]){
	MainWindow m;
	m.MainLoop();
	//PackParser p("./res/img/shoot.pack");
	/*HitTestable h;
	cout<<h.line_istangled(0,0,1,1,0,1,1,0)<<endl;
	HitTestable h1;
	h1.addVertex(0,0);
	h1.addVertex(1,0);
	h1.addVertex(1,1);
	h1.addVertex(0,1);
	HitTestable h2;
	h2.addVertex(1,1);
	h2.addVertex(0,1);
	h2.addVertex(0,0);
	h2.moveTo(0.5,0);
	cout<<h1.hitTest(&h2)<<endl;*/
	return 0;
}
