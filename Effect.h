#pragma once

const int EffectNum = 100;
extern int Jumpimg[5];//�W�����v�摜5�R�}

struct Effect
{
	float x;
	float y;
	float animeNo = 0;//���̃R�}
	int maxAnimeNo;//�ő�R�}��
	bool enable = false;//�Đ��L���t���O
};

extern Effect jump[EffectNum];//�W�����v�p�̕ϐ�

void initEffect();
void UpdateEffect();
void DrawEffect();