#pragma once

//�G�t�F�N�g�̏��
struct Effect
{
	float x, y = 0;//���W
	float animeNo = 0;//���݂̃R�}��
	bool isUsed = false;//�Đ��L���t���O
};

const int JumpMaxNum = 5;
const int EffectNum = 100;

extern int Jumpimg[JumpMaxNum];//�W�����v�摜
extern Effect jump[EffectNum];//�W�����v�p�ϐ�

void InitEffect();//�G�t�F�N�g������
void UpdateEffect(float deltaTime);//�G�t�F�N�g�X�V
void DrawEffect();//�G�t�F�N�g�`��
void StartJumpEffect(float x, float y);//�W�����v�G�t�F�N�g�p�֐�