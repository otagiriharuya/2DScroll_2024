#include "DxLib.h"
#include <chrono>
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "FloorManager.h"
#include "Floor.h"

//�O���[�o���C���X�^���X
FloorManager floorManager;

//�v���g�^�C�v�錾
void GameInitResources();//�Q�[�����\�[�X�̏�����
void GameInitObj();//�Q�[���I�u�W�F�̏�����
void GameUpdate(float deltaTime);//�Q�[���̍X�V
void GameDraw();//�Q�[���̕`��
std::chrono::system_clock::time_point prevTime;//���Ԍv���p

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

	GameInitResources();//�Q�[�����\�[�X�̏�����
	GameInitObj();//�Q�[���I�u�W�F�̏�����

	prevTime = std::chrono::system_clock::now();//�O�񎞊Ԃ��擾

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//����ʂ̕`���S�ď���
		//���Ԍv��
		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();//���ݎ��Ԏ擾
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - prevTime).count() / 1000000.0f;
		prevTime = currentTime;

		GameUpdate(deltaTime);//�X�V
		GameDraw();//�`��

		ScreenFlip();//����ʂƕ\��ʂ̓���
	}
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}

//�Q�[�����\�[�X������
void GameInitResources()
{
	initEffect();
}

//�Q�[���I�u�W�F������
void GameInitObj()
{
	initPlayer();
	initFloors(floorManager);
}

//�Q�[���X�V
void GameUpdate(float deltaTime)
{
	UpdateEffect(deltaTime);
	UpdatePlayer(floorManager.GetFloors(), deltaTime);

	// ��F�X�y�[�X�L�[����������V��������ǉ�
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		Floor newFloor = { 100, 100, 50, 50 };
		newFloor.img = LoadGraph("Bloc01.jpg", true);
		floorManager.AddFloor(newFloor);
	}

	if (CheckHitKey(KEY_INPUT_1) == 1) {
		// ��Fx���W��500�ȏ�̏����폜
		floorManager.RemoveFloorIf([](const Floor& floor) { return floor.x > 500; });
	}
}

//�Q�[���`��
void GameDraw()
{
	DrawEffect();
	DrawPlayer();
	floorManager.DrawFloors();
}