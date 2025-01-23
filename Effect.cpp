#include "DxLib.h"
#include "Effect.h"

Effect jump[EffectNum];//�W�����v�p�̕ϐ�
int Jumpimg[5];//�W�����v�摜5�R�}

void initEffect()
{
	//�摜�̓Ǎ�
	LoadDivGraph("Jump.png", 5, 5, 1, 100, 100, Jumpimg);
}

void UpdateEffect()
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; i++)
	{
		if (jump[i].enable == true)
		{
			//�A�j���[�V������i�߂�
			jump[i].animeNo = jump[i].animeNo + 0.1;
			//�U�R�}�ڂɂȂ�����I��
			if ((int)(jump[i].animeNo) > 5) {
				jump[i].enable = false;
			}
		}
	}
}

void DrawEffect()
{
	//�W�����v�p
	for (int i = 0; i < EffectNum; i++) {
		if (jump[i].enable == true)
		{
			int no = jump[i].animeNo;
			DrawGraph(jump[i].x, jump[i].y, Jumpimg[no], true);
		}
	}
}
