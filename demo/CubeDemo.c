
#include "../Pixel.h"
#include "../Screen.h"
#include "../Line.h"
#include "../Line3D.h"
#include <iostream>

Line* transform (Line3D* ln);
void translate (Line* ln, int x, int y);

float scale = 0.001;

int main () {
	Line3D* cube [12];
	Line* cube2D [12];
	int length = 100;
	double speed = 0.01;
	cube [0] = new Line3D(0,0,0,length,0,0);
	cube [1] = new Line3D(0,0,0,0,length,0);
	cube [2] = new Line3D(0,0,0,0,0,length);
	cube [3] = new Line3D(length,0,0,length,length,0);
	cube [4] = new Line3D(length,0,0,length,0,length);
	cube [5] = new Line3D(0,length,0,0,length,length);
	cube [6] = new Line3D(0,length,0,length,length,0);
	cube [7] = new Line3D(0,0,length,0,length,length);
	cube [8] = new Line3D(0,0,length,length,0,length);
	cube [9] = new Line3D(length,length,0,length,length,length);
	cube [10] = new Line3D(0,length,length,length,length,length);
	cube [11] = new Line3D(length,0,length,length,length,length);

	for (int i = 0; i < 12; i++) {
		cube[i]->translate(-length/2,-length/2,0);
		cube2D[i] = transform((cube[i]));
		translate(cube2D[i], length, length);
	}

	Screen screen;
	for (int j = 0; j < 100000; j++) {
		screen.beginBatch();
		for (int i = 0; i < 12; i++) {
			cube[i]->translate(speed,speed,0);
			cube2D[i] = transform((cube[i]));
			translate(cube2D[i], length, length);
			screen.draw((cube2D[i]));
		}
		screen.endBatch();
	}
	
	for (int i = 0; i < 12; i++) {
		delete cube2D[i];
		delete cube[i];
	}
}


Line* transform (Line3D* ln) {
	Point first, last;
	first.x = ln->p1.x / (ln->p1.z*scale + 1);
	first.y = ln->p1.y / (ln->p1.z*scale + 1);
	last.x = ln->p2.x / (ln->p2.z*scale + 1);
	last.y = ln->p2.y / (ln->p2.z*scale + 1);
	Color white(255,255,255,0);
	Line* l = new Line(first,last,white);
	return l;
}

void translate (Line* ln, int x, int y) {
	Point p1 = ln->getBeginPoint();
	Point p2 = ln->getEndPoint();
	Color c = ln->getColor();
	p1.x = p1.x + x;
	p1.y = p1.y + y;
	p2.x = p2.x + x;
	p2.y = p2.y + y;
	ln->setBeginPoint(p1);
	ln->setEndPoint(p2);
}
