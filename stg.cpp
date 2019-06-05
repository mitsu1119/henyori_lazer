#include "stg.h"

// --------------------------------------- Point class ---------------------------------------
Point::Point():x(0),y(0) {
}

Point::Point(int x, int y) : x(x), y(y) {
}

// -------------------------------------- Bullet class ----------------------------------------
Bullet::Bullet() : flag(false) {
}

Bullet::Bullet(Point *p0, Point *p1, Point *p2, int speed): p0(p0), p1(p1), p2(p2), speed(speed), cnt(0), flag(true) {
	coord = new Point(*p0);
}

Bullet::~Bullet() {
	delete coord;
}

bool Bullet::isUsed() {
	return flag;
}

Point Bullet::move() {
	if(flag == false) return Point();
	double t = (1.0 / speed) * cnt;
	coord->x = (1 - t) * (1 - t) * p0->x + 2 * (1 - t) * t * p1->x + t * t * p2->x;
	coord->y = (1 - t) * (1 - t) * p0->y + 2 * (1 - t) * t * p1->y + t * t * p2->y;
	cnt++;
	if(coord->x < 0 || coord->x > 640 || coord->y < 0 || coord->y > 480) flag = false;

	return Point(coord->x, coord->y);
}

void Bullet::draw() {
	if(flag == false) return;
	DrawBox(coord->x -2, coord->y - 2, coord->x + 2, coord->y + 2, GetColor(255, 155, 155), true);
}

// ---------------------------------------- Lazer class ---------------------------------------------
Lazer::Lazer() : state(0) {
	tracing = {};
	tip = new Bullet();
}

Lazer::Lazer(Point *p0, Point *p1, Point *p2, int speed, unsigned int tracingSize) : state(1), tracingSize(tracingSize) {
	tracing.emplace_back(p0->x, p0->y);
	tip = new Bullet(p0, p1, p2, speed);
}

Lazer::~Lazer() {
	delete tip;
}

bool Lazer::isUsed() {
	if(state == 0) return false;
	return true;
}

void Lazer::move() {
	if(isUsed() == false) return;

	if(tracing.size() >= tracingSize) {
		tracing.pop_front();
		tracing.emplace_back(tip->move());
	} else {
		tracing.emplace_back(tip->move());
	}

	if(tip->isUsed() == false) state = 0;
}

void Lazer::draw() {
	if(isUsed() == false) return;
	for(auto i: tracing) DrawBox(i.x - 2, i.y - 2, i.x + 2, i.y + 2, GetColor(0, 255, 0), true);
}
