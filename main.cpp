#include "DxLib.h"
#include <vector>
#include "stg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) return -1;

	unsigned int bltNum = 8;

	Point p0(320, 400);
	std::vector<Point> p1(bltNum);
	for(size_t i = 0; i < bltNum; i++) p1[i] = Point(p0.x -20 + 40 + 40 * (i - bltNum / 2), 600);
	Point p2(320, 50);

	std::vector<Lazer *> lz(bltNum);
	for(size_t i = 0; i < bltNum; i++) lz[i] = new Lazer();

	SetDrawScreen(DX_SCREEN_BACK);
	while(ProcessMessage() == 0) {
		ClearDrawScreen();

		DrawBox(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5, GetColor(255, 255, 255), true);
		DrawBox(p2.x - 5, p2.y - 5, p2.x + 5, p2.y + 5, GetColor(255, 255, 255), true);

		if(CheckHitKey(KEY_INPUT_Z)) {
			for(size_t i = 0; i < bltNum; i++) {
				if(lz[i]->isUsed() == false) lz[i] = new Lazer(&p0, &p1[i], &p2, 80, 10);
			}
		}

		for(auto i: lz) {
			i->move();
			i->draw();
		}
		ScreenFlip();
	}

	WaitKey();
	DxLib_End();
	return 0;
}