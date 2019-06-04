#include "DxLib.h"
#include <vector>

class Point {
public:
	Point() {
	}

	Point(int x, int y): x(x), y(y) {
	}
	int x, y;

	void Draw() {
		DrawBox(x-1, y-1, x+1, y+1, GetColor(255, 255, 255), true);
	}
};

class Bullet {
public:
	Bullet(): flag(false) {
	}

	Bullet(Point p0, Point p1, Point p2, int speed): p0(p0), p1(p1), p2(p2), coord(p0), speed(speed), cnt(0), flag(true) {
	}
	
	Point p0, p1, p2;
	Point coord;

	// Speed of a bullet. 
	// correspondence divide number
	int speed;
	unsigned int cnt;

	bool flag;

	void move() {
		if(flag == false) return;
		double t = (1.0 / speed) * cnt;
		coord.x = (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x;
		coord.y = (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y;
		cnt++;
		if(coord.x < 0 || coord.x > 640 || coord.y < 0 || coord.y > 480) flag = false;
	}

	void draw() {
		if(flag == false) return;
		DrawBox(coord.x -2, coord.y - 2, coord.x + 2, coord.y + 2, GetColor(255, 155, 155), true);
	}

};



void DrawBezier(Point p0, Point p1, Point p2, unsigned int DivNum) {
	double t;
	int px, py;
	for(size_t i = 0; i <= DivNum; i++) {
		t = (1.0 / DivNum) * i;
		px = (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x;
		py = (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y;
		DrawBox(px - 1, py - 1, px + 1, py + 1, GetColor(255, 255, 255), true);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) return -1;

	unsigned int bltNum = 8;

	// start point
	Point p0(320, 400);
	
	// control points
	std::vector<Point> p1(bltNum);
	for(size_t i = 0; i < bltNum; i++) {
		p1[i] = Point(p0.x -20 + 40 + 40 * (i - bltNum / 2), 600);
	}

	// end point
	Point p2(320, 50);

	std::vector<Bullet *> blt(bltNum);
	for(size_t i = 0; i < bltNum; i++) {
		blt[i] = new Bullet();
	}

	SetDrawScreen(DX_SCREEN_BACK);
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		
		DrawBox(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5, GetColor(255, 255, 255), true);
		DrawBox(p2.x - 5, p2.y - 5, p2.x + 5, p2.y + 5, GetColor(255, 255, 255), true);
		
		if(CheckHitKey(KEY_INPUT_Z)) {
			for(size_t i = 0; i < bltNum; i++) {
				if(blt[i]->flag == false) blt[i] = new Bullet(p0, p1[i], p2, 80);
			}
		}

		for(size_t i = 0; i < bltNum; i++) {
			blt[i]->move();
			blt[i]->draw();
		}

		ScreenFlip();
	}

	WaitKey();
	DxLib_End();
	return 0;
}