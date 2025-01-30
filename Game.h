#pragma once

enum class Type 
{
	Player,//���@
	Enemy,//�G
	Figurine,//�u��
	Wall,//��
	Ground//��
};

const float Gravity = 0.3f;//�d�͉����x

//�~�Ƌ�`�̓����蔻��֐�
bool CheckCollision(float circleX, float circleY, float circleR,
	float rectX, float rectY, float rectWidth, float rectHeight);