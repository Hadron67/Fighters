#ifndef HITTESTABLE_HPP
#define HITTESTABLE_HPP
//interface HitTestable
#include <vector>
class HitTestable{
	private:
		double x,y;
		std::vector<double> vertx;
		std::vector<double> verty;
		int verticescount;
		double rotation;
	public:
		HitTestable();
		virtual ~HitTestable();
		int line_istangled(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);
		void addVertex(double x,double y);
		void moveto(double x,double y);
		void rotateto(double r);
		virtual int hitTest(HitTestable* MovieClip);
};
#endif
