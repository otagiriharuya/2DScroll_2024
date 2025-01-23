#include "DxLib.h"
#include "Player.h"
#include "Action.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

PlayerStatus player;//�v���C���[�̃X�e�[�^�X
std::vector<Floor> floors;

//�v���C���[������
void initPlayer()
{
	//player.img = LoadGraph("");
	player.Hp = 5;
	player.x = 100;
	player.y = 300;
	player.vx = 0;
	player.vy = 0;
	player.jumpPower = -11.0f;//�W�����v��
	player.r = 50;
	player.jumpCount = 0;
	player.maxJumps = 2;
	player.isSpace = false;
	player.staet = 0;
	
}

//�v���C���[�X�V
void UpdatePlayer(Floor floors[], int floorCount)
{
	PlayerMove();//�ړ�
	PlayerJump();//�W�����v
	PlayerGra();//�d��
	PlayerCollision(floors, floorCount);//�����蔻��
	PlayerPosi();//���W
}

//�v���C���[�ړ�����
void PlayerMove()
{
	const float Move_Speed = 5;//���ړ���
	//���ړ�
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		player.vx = -Move_Speed;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		player.vx = Move_Speed;
	}
	else
	{
		player.vx = 0;
	}
}

//�v���C���[�W�����v����
void PlayerJump()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && !player.isSpace)
	{
		player.isSpace = true;
		//�W�����v�G�t�F�N�g
		for (int i = 0; i < EffectNum; ++i)
		{
			if (jump[i].enable == false)
			{
				jump[i].enable = true;
				jump[i].x = player.x - 50;
				jump[i].y = player.y - 50;
				jump[i].animeNo = 0;
				break;
			}
		}
		//�n�ʂɂ��邩�W�����v�����񐔂�2�񖢖���������
		if (player.staet == 0 || player.jumpCount < player.maxJumps)
		{
			player.vy = player.jumpPower;//y�����̈ړ��ʂ��W�����v�͂ɂ���
			++player.jumpCount;//�W�����v�񐔂𑝂₷
			if (player.staet == 0)
				player.staet = 1;//1��ڂ̃W�����v
			else if (player.staet == 1)
				player.staet = 2;//2��ڂ̃W�����v
		}
	}
	if (!CheckHitKey(KEY_INPUT_SPACE))
		player.isSpace = false;
}

//�v���C���[�d�͏���
void PlayerGra()
{
	//�d�͂ɂ�闎��
	player.vy += Gravity;
	//��������
	if (player.staet != 0 && player.vy > 0)
		player.staet = 3;//������
}

//�v���C���[�̏��Ƃ̏Փ˔���
void PlayerCollision(Floor floors[], int floorCount)
{
	//���Ƃ̓����蔻��
	player.staet = 3;//��������n�ʂɂ��Ă��Ȃ���Ԃɂ���
	for (int i = 0; i < floorCount; ++i)
	{
		Floor& floor = floors[i];//�������
		bool isColliding = CheckCollision(player.x, player.y, player.r
			, floor.x, floor.y, floor.width, floor.height);
		//�����蔻�肪�������Ƃ��̏���
		if (isColliding)
		{
			if (player.vy >= 0 && player.y - player.r < floor.y)
			{
				// ���̏ォ��̏Փ�
				player.y = floor.y - player.r;
				player.vy = 0;
				player.staet = 0;
				player.jumpCount = 0;
			}
			else if (player.vy <= 0 && player.y + player.r > floor.y + floor.height)
			{
				// ���̉�����̏Փ�
				player.y = floor.y + floor.height + player.r;
				player.vy = 0;
			}
		}
	}
}

//�v���C���[���W�X�V
void PlayerPosi()
{
	// ��ʒ[����
		if (player.x < player.r) player.x = player.r;
	if (player.x > 1000 - player.r) player.x = 1000 - player.r;
	// �ړ�
	player.x += player.vx;
	player.y += player.vy;
}

//�v���C���[�`��
void DrawPlayer()
{
	DrawCircle(player.x,player.y,player.r, GetColor(255, 255, 255), true);
	//DrawGraph(Cha_Player.x, Cha_Player.y, Cha_Player.img, true);

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "���F%f,���F%f\n%d",Obj_Player.x,Obj_Player.y,player.jumpCount);
}
