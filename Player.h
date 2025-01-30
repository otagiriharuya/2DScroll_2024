#pragma once
#include <vector>
#include "Game.h"
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
	Type type;
};

extern PlayerStatus player;

void initPlayer();//�v���C���[������
void UpdatePlayer(const std::vector<Floor>& floors,float deltaTime);//�v���C���[�X�V
void PlayerMove();//�v���C���[�ړ�����
void PlayerJump();//�v���C���[�W�����v����
void PlayerGra();//�v���C���[�d�͏���
void PlayerCollision(const std::vector<Floor>& floors);//�v���C���[�̏��Ƃ̏Փ˔���Ə���
void PlayerPosi();//�v���C���[���W�X�V
void DrawPlayer();//�v���C���[�`��
