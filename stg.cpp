#include "stg.h"

// --------------------------------------- Point class ---------------------------------------
Point::Point() {
}

Point::Point(int x, int y) : x(x), y(y) {
}

// -------------------------------------- Bullet class ----------------------------------------
Bullet::Bullet() : flag(false) {
}

Bullet::Bullet(Point p0, Point p1, Point p2, int speed): p0(p0), p1(p1), p2(p2), coord(p0), speed(speed), cnt(0), flag(true) {
}

void Bullet::move() {
	if(flag == false) return;
	double t = (1.0 / speed) * cnt;
	coord.x = (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x;
	coord.y = (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y;
	cnt++;
	if(coord.x < 0 || coord.x > 640 || coord.y < 0 || coord.y > 480) flag = false;
}

void Bullet::draw() {
	if(flag == false) return;
	DrawBox(coord.x -2, coord.y - 2, coord.x + 2, coord.y + 2, GetColor(255, 155, 155), true);
}
