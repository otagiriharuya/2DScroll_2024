#pragma once

enum class Type 
{
	Player,//自機
	Enemy,//敵
	Figurine,//置物
	Wall,//壁
	Ground//床
};

const float Gravity = 0.3f;//重力加速度

//円と矩形の当たり判定関数
bool CheckCollision(float circleX, float circleY, float circleR,
	float rectX, float rectY, float rectWidth, float rectHeight);