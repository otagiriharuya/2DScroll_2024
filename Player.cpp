#include "DxLib.h"
#include "Player.h"
#include "Action.h"

PlayerStatus player;//�v���C���[�̃X�e�[�^�X
void PlayerMove();//�ړ�
void PlayerJump();//�W�����v

//�v���C���[������
void initPlayer()
{
	player.Hp = 5;
	player.x = 40;
	player.y = 700;
	player.r = 35;
	player.vx = 2;
	player.vy = 5;
	player.isJump = false;
	player.JumpSu = 0;
	//player.img = 
}

//�v���C���[�X�V
void UpdatePlayer()
{
	PlayerMove();
	PlayerJump();
}

//�ړ�
void PlayerMove()
{
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		player.x -= player.vx;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		player.x += player.vx;
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		player.y -= player.vy;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		player.y += player.vy;
	}
}

//�W�����v
void PlayerJump()
{

}

//�v���C���[�`��
void DrawPlayer()
{
	DrawCircle(player.x, player.y, player.r, GetColor(255, 255, 255), true);
}
