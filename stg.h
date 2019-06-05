#pragma once
#include "DxLib.h"

// for coord, vector, etc
class Point {
public:
	Point();
	Point(int x, int y);

	int x, y;
};

// bullet
class Bullet {
public:
	Bullet();

	Bullet(Point p0, Point p1, Point p2, int speed);

	Point p0, p1, p2;
	Point coord;

	// Speed of a bullet. 
	// correspondence divide number
	int speed;
	unsigned int cnt;

	bool flag;

	// Bezier curve
	void move();

	void draw();

};