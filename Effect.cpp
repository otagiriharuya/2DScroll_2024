#include "DxLib.h"
#include "Effect.h"

std::vector<Effect> jump(EffectNum);//�W�����v�p�ϐ�
std::vector<int> Jumpimg(5);//�W�����v�摜

void initEffect()
{
	//�摜�̓Ǎ�
	int result01 = LoadDivGraph("Jump.png", 5, 5, 1, 100, 100,Jumpimg.data());
	//�G���[����
	if(result01 == -1)
		MessageBox(nullptr, "�摜�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);

	//�W�����v�G�t�F�N�g�̏�����
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].isUsed = false;
		jump[i].animeNo = 0;
		jump[i].x = 0;
		jump[i].y = 0;
	}
}

void UpdateEffect(float deltaTime)
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; ++i)
	{
		jump[i].animeNo++;//�A�j���[�V������i�߂�
		//�R�}���𒴂�����G�t�F�N�g���I��������
		if (jump[i].animeNo >= JumpMaxNum)
		{
			jump[i].isUsed = false;
			jump[i].animeNo = 0;
		}
	}
}

void DrawEffect()
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].isUsed == true)
		{
			int no = jump[i].animeNo;
			DrawGraph(jump[i].x, jump[i].y, Jumpimg[no % JumpMaxNum], true);
		}
	}
}

//�W�����v�G�t�F�N�g���J�n����֐�
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