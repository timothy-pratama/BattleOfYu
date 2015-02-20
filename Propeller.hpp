#include "Pixel.h"
#include "Screen.h"
#include "Line.h"
#include "CompositeDrawable.h"
#include "MatrixDrawable.h"
#include "Keyboard.h"
#include "Util.h"

#ifndef __PROPELLER_HPP
#define __PROPELLER_HPP

#define PROPELLER_IDLE 0
#define PROPELLER_MOVE 1
#define PROPELLER_DEAD 2
#define PROPELLER_DEFAULT_DELAY 1.0f
#define PROPELLER_DEFAULT_SPEED 0.05f
#define PROPELLER_DEFAULT_ROTATION_DEGREE 10

class Propeller {
	int state;
	Point center;
	
	CompositeDrawable* c_draw_elmt;
	int pos_x,pos_y; //left draw position
	float delay_counter; //harus mencapai ini sebelum diupdate
	float current_counter;
	float speed;
	
	void beforeDraw();
	
public:
	Propeller(string filename);
	~Propeller();
	void draw(Screen* screen);
	void setDrawPosition(int _x,int _y);
	void setState(int state);
	void translate(int dx,int dy);
	void rotate(int degree,int x0,int y0);
	void selfRotate(int degree); //rotate based on the current center
	void setCenter(Point p);
};

Propeller::Propeller(string filename){
	c_draw_elmt = new CompositeDrawable(filename);
	//m_draw_elmt = new MatrixDrawable(c_draw_elmt);
	current_counter = 0;
	speed = PROPELLER_DEFAULT_SPEED;
	delay_counter = PROPELLER_DEFAULT_DELAY;
}

Propeller::~Propeller(){
	delete (c_draw_elmt);
}

void Propeller::setDrawPosition(int _x,int _y){
	pos_x = _x; pos_y = _y;
	c_draw_elmt->setPosition(_x,_y);
}

void Propeller::setCenter(Point p){ this->center = p; }

void Propeller::draw(Screen* screen){
  this->beforeDraw();
  screen->draw(c_draw_elmt,1.0f);
}

void Propeller::setState(int _state){ state = _state; }

void Propeller::translate(int dx,int dy){
	c_draw_elmt->translate(dx,dy);
}

void Propeller::beforeDraw(){
	current_counter += speed;
	if (current_counter > delay_counter){
  	current_counter = 0;
  	c_draw_elmt->translate(-1,-1);
  	this->selfRotate(PROPELLER_DEFAULT_ROTATION_DEGREE);
  }
}

void Propeller::selfRotate(int degree){
	c_draw_elmt->rotate(degree,center.x,center.y);
}

#endif

