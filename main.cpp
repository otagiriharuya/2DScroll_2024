#include "DxLib.h"
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

//�O���[�o���ϐ�
Floor floors[10];
int floorCount = 0;

//�v���g�^�C�v�錾
void GameInit();//�Q�[���̏�����
void GameUpdate();//�Q�[���̍X�V
void GameDraw();//�Q�[���̕`��
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//�E�B���h�E���[�h�ŋN������
	SetGraphMode(1000, 800, 16);//��ʂ̃T�C�Y�ƃr�b�g���ύX
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

	GameInit();//������

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//����ʂ̕`���S�ď���

		GameUpdate();//�X�V
		GameDraw();//�`��

		ScreenFlip();//����ʂƕ\��ʂ̓���
	}
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}

void GameInit()
{
	initEffect();
	initPlayer();
	initFloors(floors, floorCount);
}
void GameUpdate()
{
	UpdateEffect();
	UpdatePlayer(floors, floorCount);
}
void GameDraw()
{
	DrawEffect();
	DrawPlayer();
	DrawFloors(floors, floorCount);
}