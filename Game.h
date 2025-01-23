#pragma once

extern enum Type 
{
	Player,//自機
	Enemy,//敵
	Figurine,//置物
	Wall,//壁
	Ground//床
};

const float Gravity = 0.3f;//重力加速度