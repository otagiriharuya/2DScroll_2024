#pragma once

const int EffectNum = 100;
extern int img[10];//�ő�10�R�}

struct Effect
{
	double x;
	double y;
	double animeNo = 0;//���̃R�}
	int maxAnimeNo;//�ő�R�}��
	bool enable = false;//�Đ��L���t���O
};

extern Effect effect[EffectNum];//�G�t�F�N�g�p�̕ϐ�

void initEffect();
void updateEffect();
void drawEffect();