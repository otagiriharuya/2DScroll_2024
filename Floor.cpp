#include "DxLib.h"
#include "Player.h"
#include "Floor.h"

int Groundimg;
//è∞ÇÃèâä˙âª
void initFloors(Floor floors[], int& floorCount)
{
	floorCount = 5;
	floors[0] = { 50, 400, 200, 50 ,LoadGraph("Bloc03.jpg",true)};
	floors[1] = { 300, 300, 150, 50,LoadGraph("Bloc02.jpg",true) };
	floors[2] = { 600, 250, 100, 50 ,LoadGraph("Bloc01.jpg",true) };
	floors[3] = { 900,80,100,50 ,LoadGraph("Bloc01.jpg",true) };
	floors[4] = { 0, 700, 1000, 100 ,LoadGraph("Ground.png",true)};//ç≈â∫ïîÇÃè∞
}

//è∞ÇÃï`âÊ
void DrawFloors(Floor floors[], int& floorCount)
{
	for (int i = 0; i < floorCount; ++i)
	{
		DrawGraph(floors[i].x, floors[i].y, floors[i].img, true);
	}
}
