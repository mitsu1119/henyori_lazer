#pragma once
#include "DxLib.h"
#include <deque>

// for coord, vector, etc
class Point {
public:
	Point();
	Point(int x, int y);

	int x, y;
};

// bullet
class Bullet {
private:
	Point p0, p1, p2, p3;
	Point *coord;
	bool flag;

	// Speed of a bullet. 
	// correspondence divide number
	int speed;
	unsigned int cnt;

public:
	Bullet();
	Bullet(Point p0, Point p1, Point p2, Point p3, int speed);
	~Bullet();

	bool isUsed();
	bool isHit(int x, int y, int sizeX, int sizeY);

	// Bezier curve
	Point move();

	void draw();
};

// lazer
class Lazer {
private:
	Bullet *tip;
	int state;		// 0: not existing, 1: existing, 2:existing only tracing

	unsigned int tracingSize;
	std::deque<Point> tracing;

public:
	Lazer();
	Lazer(Point p0, Point p1, Point p2, Point p3, int speed, unsigned int tracingSize);
	~Lazer();

	// state: 1 -> 2
	void destroy();

	bool isHit(int x, int y, int sizeX, int sizeY);

	bool isUsed();
	void move();
	void draw();
};