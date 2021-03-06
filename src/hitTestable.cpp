#include "hitTestable.hpp"
#define CROSS(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define OPPOSITE(a,b) (((a>0)&&(b<0))||((a<0)&&(b>0)))
#include<math.h>
HitTestable::HitTestable(){
	this->rotation=0;
	this->verticescount=0;
	this->x=this->y=0;
}
HitTestable::~HitTestable(){
	
}
void HitTestable::addVertex(double x,double y){
	this->vertx.push_back(x);
	this->verty.push_back(y);
	this->verticescount++;
}
int HitTestable::line_istangled(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4){ //A B C D
	double a=CROSS(x2-x1,y2-y1,x3-x1,y3-y1);// AB^AC
	double b=CROSS(x2-x1,y2-y1,x4-x1,y4-y1);// AB^AD
	double c=CROSS(x4-x3,y4-y3,x1-x3,y1-y3);// CD^CA
	double d=CROSS(x4-x3,y4-y3,x2-x3,y2-y3);// CD^CB
	return (OPPOSITE(a,b)&&OPPOSITE(c,d));
}
void HitTestable::moveto(double x,double y){
	this->x=x;
	this->y=y;
}
void HitTestable::rotateto(double r){
	this->rotation=r;
}
void HitTestable::clearVertices(){
	this->moveto(0,0);
	this->rotateto(0);
	this->vertx.clear();
	this->verty.clear();
	this->verticescount=0;
}
int HitTestable::hitTest(HitTestable* MovieClip){
	int i,j;
	for(i=0;i<this->verticescount;i++){
		for(j=0;j<MovieClip->verticescount;j++){
			int i2=(i==this->verticescount-1)?0:i+1;
			int j2=(j==MovieClip->verticescount-1)?0:j+1;
			double x1=this->vertx[i]*cos(this->rotation)-this->verty[i]*sin(this->rotation);
			double y1=this->vertx[i]*sin(this->rotation)+this->verty[i]*cos(this->rotation);
			double x2=this->vertx[i2]*cos(this->rotation)-this->verty[i2]*sin(this->rotation);
			double y2=this->vertx[i2]*sin(this->rotation)+this->verty[i2]*cos(this->rotation);
			
			double x3=MovieClip->vertx[j]*cos(MovieClip->rotation)-MovieClip->verty[j]*sin(MovieClip->rotation);
			double y3=MovieClip->vertx[j]*sin(MovieClip->rotation)+MovieClip->verty[j]*cos(MovieClip->rotation);
			double x4=MovieClip->vertx[j2]*cos(MovieClip->rotation)-MovieClip->verty[j2]*sin(MovieClip->rotation);
			double y4=MovieClip->vertx[j2]*sin(MovieClip->rotation)+MovieClip->verty[j2]*cos(MovieClip->rotation);
			int a=this->line_istangled(x1+this->x,y1+this->y,x2+this->x,y2+this->y,x3+MovieClip->x,
			y3+MovieClip->y,x4+MovieClip->x,y4+MovieClip->y);
			
			if(a) return 1;
		}
	}
	return 0;
}
