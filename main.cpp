#include "DxLib.h"
#include <vector>
#include "stg.h"

constexpr double PI = 3.141592;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) return -1;

	int bltNum = 8;

	Point p0(320, 400);
	Point p3(320, 50);
	std::vector<Point> p1(bltNum);
	std::vector<Point> p2(bltNum);

	long double rad;
	for(size_t i = 0; i < bltNum; i++) {
		rad = atan2((double)p0.y - (double)p3.y, (double)p0.x - (double)p3.x);
		p1[i] = Point(p0.x -20 + 50 + 50 * (i - bltNum / 2), p0.y + 200);
		p2[i] = Point((p0.x + p3.x) / 2  + i * cos(rad + PI / 2), (p0.y + p3.y) / 2 + i * sin(rad + PI / 2));
	}

	std::vector<Lazer *> lz(bltNum);
	for(size_t i = 0; i < bltNum; i++) lz[i] = new Lazer();

	SetDrawScreen(DX_SCREEN_BACK);
	while(ProcessMessage() == 0) {
		ClearDrawScreen();

		if(CheckHitKey(KEY_INPUT_RIGHT)) p0.x += 5;
		if(CheckHitKey(KEY_INPUT_LEFT)) p0.x -= 5;
		if(CheckHitKey(KEY_INPUT_UP)) p0.y -= 5;
		if(CheckHitKey(KEY_INPUT_DOWN)) p0.y += 5;

		for(size_t i = 0; i < bltNum; i++) {
			p1[i].x = p0.x - 20 + 50 + 50 * (i - bltNum / 2), 600;
			p1[i].y = p0.y + 200;
			rad = (double)atan2((double)p0.y - (double)p3.y, (double)p0.x - (double)p3.x);
			p2[i].x = (p0.x + p3.x) / 2 + (-40.0 * (i + 0.5 - (double)bltNum / 2.0)) * cos(rad + PI / 2);
			p2[i].y = (p0.y + p3.y) / 2 + (-40.0 * (i + 0.5 - (double)bltNum / 2.0)) * sin(rad + PI / 2);
		}

		DrawBox(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5, GetColor(255, 255, 255), true);
		DrawBox(p3.x - 5, p3.y - 5, p3.x + 5, p3.y + 5, GetColor(255, 255, 255), true);

		for(auto i: p2) DrawBox(i.x - 3, i.y - 3, i.x + 3, i.y + 3, GetColor(255, 0, 0), true);

		if(CheckHitKey(KEY_INPUT_Z)) {
			for(size_t i = 0; i < bltNum; i++) {
				if(lz[i]->isUsed() == false) lz[i] = new Lazer(p0, p1[i], p2[i], p3, 60, 10);
			}
		}

		for(auto i: lz) {
			i->move();
			if(i->isHit(p3.x - 5, p3.y - 5, 10, 10)) i->destroy();
			i->draw();
		}
		ScreenFlip();
	}

	WaitKey();
	DxLib_End();
	return 0;
}