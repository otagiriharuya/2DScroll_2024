#pragma once
#include <vector>
#include "Floor.h"

enum class PlayerState
{
	Ground,//�n�ʂɂ���
	Jump1,//�W�����v1���
	Jump2,//�W�����v2���
	Falling,//������
};

//�v���C���[�̍\����
struct  PlayerStatus
{
	float x, y;//���W
	float vx, vy;//�ړ���
	float Hp;//�̗�
	float r;//���a
	float jumpPower;//�W�����v��
	int img;//�摜
	int jumpCount;//�W�����v������
	int maxJumps;//�ő�W�����v��
	bool isSpace;//�X�y�[�X�L�[�������ꂽ��
	bool isRight;//�E�������Ă��邩
	PlayerState state;//���݂̏��
};

//�d�͉����x
const float Gravity = 0.8f;

//�v���C���[������
void initPlayer();
//�v���C���[�X�V
void UpdatePlayer(const std::vector<Floor>& floors, float deltaTime);
//�v���C���[�`��
void DrawPlayer();
