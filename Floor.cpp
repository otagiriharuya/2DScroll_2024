#include "DxLib.h"
#include "Player.h"
#include "Floor.h"

//°‚Ì‰Šú‰»
void initFloors(Floor floors[], int& floorCount)
{
	floorCount = 5;
	floors[0] = { 50, 400, 200, 30 };
	floors[1] = { 300, 300, 150, 30 };
	floors[2] = { 600, 250, 100, 30 };
	floors[3] = { 900,80,100,20 };
	floors[4] = { 0, 700, 1000, 100 };//Å‰º•”‚Ì°
}

//°‚Ì•`‰æ
void DrawFloors(Floor floors[], int& floorCount)
{
	for (int i = 0; i < floorCount; ++i)
	{
		DrawBox(floors[i].x, floors[i].y, (floors[i].x + floors[i].width), (floors[i].y+floors[i].height), GetColor(0, 255, 0), true);
	}
}
