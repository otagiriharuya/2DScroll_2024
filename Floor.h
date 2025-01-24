#pragma once
#include <vector>

//°‚Ì\‘¢‘Ì
struct Floor
{
	float x, y;//À•W
	float width, height;//•‚Æ‚‚³
	int img;//‰æ‘œ
};

// °‚Ì‰Šú‰»
void initFloors(Floor floors[],int& floorCount);

// °‚Ì•`‰æ
void DrawFloors(Floor floors[], int& floorCount);