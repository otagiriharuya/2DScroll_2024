#pragma once

void initPlayer();//�v���C���[������
void UpdatePlayer();//�v���C���[�X�V
void DrawPlayer();//�v���C���[�`��

//�v���C���[�̃X�e�[�^�X
extern struct  PlayerStatus
{
	double Hp;//�̗�
	double x;//x���W
	double y;//y���W
	double r;//���a
	double vx;//x�̈ړ���
	double vy;//y�̈ړ���
	int img;//�摜
	int JumpSu;//�W�����v������
	bool isJump;//�W�����v������
};
