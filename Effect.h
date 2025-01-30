#pragma once
#include <vector>

const int JumpMaxNum = 5;//�W�����v�G�t�F�N�g�̍ő�R�}��
const int EffectNum = 100;//�G�t�F�N�g�ő吔

struct Effect
{
	float x,y =0;//���W
	int animeNo = 0;//���݂̃R�}��
	bool isUsed = false;//�Đ��L���t���O
};

//�W�����v�G�t�F�N�g�̔z��
extern std::vector<int> Jumpimg;//�W�����v�摜
extern std::vector<Effect> jump;//�W�����v�p�̕ϐ�

void initEffect();
void UpdateEffect(float deltaTime);
void DrawEffect();
void StartJumpEffect(float x, float y);