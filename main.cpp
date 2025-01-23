#include "DxLib.h"
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"


Floor floors[10];
int floorCount = 0;

void init();
void Update();
void Draw();
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

	init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		Update();

		
		
		Draw();

		ScreenFlip();//����ʂƕ\��ʂ̓���
		ClearDrawScreen();//����ʂ̕`���S�ď���
	}
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}

void init()
{
	initEffect();
	initPlayer();
	initFloors(floors, floorCount);
}
void Update()
{
	UpdateEffect();
	UpdatePlayer(floors, floorCount);
}
void Draw()
{
	DrawEffect();
	DrawPlayer();
	DrawFloors(floors, floorCount);
}