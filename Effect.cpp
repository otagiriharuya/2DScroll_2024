#include "DxLib.h"
#include "Effect.h"
#include "Camera.h"

Effect jump[EffectNum];//�W�����v�p�ϐ�
int Jumpimg[JumpMaxNum];//�W�����v�摜
const float AnimationSpeed = 10.0f;//�A�j���[�V�������x

//�G�t�F�N�g������
void InitEffect()
{
	//�摜�̓Ǎ�
	LoadDivGraph("Jump.png", 5, 5, 1, 100, 100, Jumpimg);
	//�W�����v�G�t�F�N�g�̏�����
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].isUsed = false;
		jump[i].animeNo = 0;
		jump[i].x = 0;
		jump[i].y = 0;
	}
}

//�G�t�F�N�g�̍X�V
void UpdateEffect(float deltaTime)
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].animeNo += AnimationSpeed * deltaTime;//�A�j���[�V������i�߂�
		//�R�}���𒴂�����G�t�F�N�g���I��������
		if (jump[i].animeNo >= JumpMaxNum)
		{
			jump[i].isUsed = false;
			jump[i].animeNo = 0;
		}
	}
}

//�G�t�F�N�g�`��
void DrawEffect()
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].isUsed)
		{
			int no = jump[i].animeNo;
			DrawGraph(WorldToScreenX(camera, jump[i].x), WorldToScreenY(camera, jump[i].y), Jumpimg[no], true);
		}
	}
}

//�W�����v�G�t�F�N�g�p�֐�
void StartJumpEffect(float x, float y)
{
	for (int i = 0; i < EffectNum; ++i)
	{
		if (!jump[i].isUsed)
		{
			jump[i].isUsed = true;
			jump[i].x = x;
			jump[i].y = y;
			jump[i].animeNo = 0;
			break;
		}
	}
}