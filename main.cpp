#include "DxLib.h"
#include <vector>
#include "stg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) return -1;

	unsigned int bltNum = 8;
	Point p0(320, 400);
	Point p1(200, 600);
	Point p2(320, 50);
	Bullet *blt = new Bullet();

	SetDrawScreen(DX_SCREEN_BACK);
	while(ProcessMessage() == 0) {
		ClearDrawScreen();

		DrawBox(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5, GetColor(255, 255, 255), true);
		DrawBox(p2.x - 5, p2.y - 5, p2.x + 5, p2.y + 5, GetColor(255, 255, 255), true);

		if(blt->flag == false && CheckHitKey(KEY_INPUT_Z)) blt = new Bullet(p0, p1, p2, 80);

		blt->move();
		blt->draw();
		ScreenFlip();
	}

	/*
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
	*/

	WaitKey();
	DxLib_End();
	return 0;
}