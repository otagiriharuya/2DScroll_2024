#pragma once
#include "Game.h"
#include "Floor.h"

//�v���C���[�̍\����
extern struct  PlayerStatus
{
	float x, y;//���W
	float vx, vy;//�ړ���
	float Hp;//�̗�
	float r;//���a
	float jumpPower;//�W�����v��
	int img;//�摜
	int jumpCount;//�W�����v������
	int maxJumps;//�ő�W�����v��
	int staet;//���݂̏��(0:�n��1:1�i�W�����v��2:2�i�W�����v��3:������)
	bool isSpace;//�X�y�[�X�L�[�������ꂽ��
	bool isRight;//�E�������Ă��邩
	Type type;
};

void initPlayer();//�v���C���[������
void UpdatePlayer(Floor floors[],int floorCount);//�v���C���[�X�V
void PlayerMove();//�v���C���[�ړ�����

void PlayerJump();//�v���C���[�W�����v����
void PlayerGra();//�v���C���[�d�͏���
void PlayerCollision(class Floor floors[], int floorCount);//�v���C���[�̏��Ƃ̏Փ˔���Ə���
void PlayerPosi();//�v���C���[���W�X�V
void DrawPlayer();//�v���C���[�`��
