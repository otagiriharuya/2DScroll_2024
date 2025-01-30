#include "DxLib.h"
#include <chrono>
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

//�v���g�^�C�v�錾
void GameInitResources();//�Q�[�����\�[�X�̏�����
void GameInitObj();//�Q�[���I�u�W�F�̏�����
void GameUpdate(float deltaTime, std::vector<Floor>& floors);//�Q�[���̍X�V
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
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - prevTime).count()/ 1000000.0f;
		prevTime = currentTime;
		
		GameUpdate(deltaTime,floors);//�X�V
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
	initFloors();
}

//�Q�[���X�V
void GameUpdate(float deltaTime, std::vector<Floor>& floors)
{
	UpdateEffect(deltaTime);
	UpdatePlayer(floors, deltaTime);
}

//�Q�[���`��
void GameDraw()
{
	DrawEffect();
	DrawPlayer();
	DrawFloors();
}