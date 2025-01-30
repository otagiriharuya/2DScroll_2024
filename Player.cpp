#include "DxLib.h"
#include <vector>
#include <algorithm>
#include <cmath>//std::pow���g�p���邽��
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include "Floor.h"

//�萔
const float PlayerMoveSpeed = 3.0f;//���@�̈ړ��X�s�[�h
const float PlayerJumpPower = -11.0f;//���@�̃W�����v��
const int PlayerMaxJumps = 2;//�ő�W�����v��
const int WindowWidth = 1000;//�E�B���h�E�̉��ő吔

PlayerStatus player;

//�v���C���[������
void initPlayer()
{
	player.img = LoadGraph("Ghost.png",true);//�摜
	player.Hp = 5;//�̗�
	player.x = 500;//x���W
	player.y = 300;//y���W
	player.vx = 0;//���ړ���
	player.vy = 0;//�c�ړ���
	player.jumpPower = PlayerJumpPower;//�W�����v��
	player.r = 25;//���a
	player.jumpCount = 0;//�W�����v������
	player.maxJumps = PlayerMaxJumps;//�ő�W�����v��
	player.isSpace = false;//Space�L�[����������
	player.isRight = true;//�E�������Ă��邩
	player.state = PlayerState::Ground;//���݂̏��
}

//�d�͉����x�G�p
void PlayerGra()
{
	//�d�͂ɂ�闎��
	player.vy += Gravity;
	//��������
	if (player.state != PlayerState::Ground && player.vy > 0)
		player.state = PlayerState::Falling;//������
}

//�v���C���[�ړ�����
void PlayerMove()
{
	float MoveSpeed = PlayerMoveSpeed;//���ړ���

	//���V�t�g�������Ă���Ƃ��_�b�V��
	if (CheckHitKey(KEY_INPUT_LSHIFT))
		MoveSpeed *= 2;
	//�n�ʂɂ���Ƃ�
	if (player.state != PlayerState::Ground)
		MoveSpeed = PlayerMoveSpeed;

	//���ړ�
	if (CheckHitKey(KEY_INPUT_A))
	{
		player.vx = -MoveSpeed;
		player.isRight = false;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.vx = MoveSpeed;
		player.isRight = true;
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
		StartJumpEffect(player.x - 50, player.y - 50);

		//�n�ʂɂ��邩�W�����v�����񐔂�2�񖢖���������
		if (player.state == PlayerState::Ground || player.jumpCount < player.maxJumps)
		{
			player.vy = player.jumpPower;//y�����̈ړ��ʂ��W�����v�͂ɂ���
			++player.jumpCount;//�W�����v�񐔂𑝂₷
			if (player.state == PlayerState::Ground)
				player.state = PlayerState::Jump1;//��Ԃ��W�����v1��ڂ�
			else if (player.state == PlayerState::Jump1)
				player.state = PlayerState::Jump2;//��Ԃ��W�����v2��ڂ�
		}
	}
	if (!CheckHitKey(KEY_INPUT_SPACE))
		player.isSpace = false;
}

//���Ƃ̏Փ˔���
bool CheckCollision(float playerX, float playerY, float playerR,const Floor& floor)
{
	//�~�Ƌ�`�̓����蔻��
	float circleDistanceX = std::abs(playerX - floor.x - floor.width / 2);
	float circleDistanceY = std::abs(playerY - floor.y - floor.height / 2);

	if (circleDistanceX > (floor.width / 2 + playerR)) { return false; }
	if (circleDistanceY > (floor.height / 2 + playerR)) { return false; }

	if (circleDistanceX <= (floor.width / 2)) { return true; }
	if (circleDistanceY <= (floor.height / 2)) { return true; }

	float cornerDistanceSq = (circleDistanceX - floor.width / 2) * (circleDistanceX - floor.width / 2) +
		(circleDistanceY - floor.height / 2) * (circleDistanceY - floor.height / 2);

	return (cornerDistanceSq <= (playerR * playerR));
}

//�v���C���[�̏��Ƃ̏Փ˔���
void PlayerCollision(const std::vector<Floor>& floors)
{
	player.state = PlayerState::Falling;
	for (const auto& floor : floors)
	{
		bool isColliding = CheckCollision(player.x, player.y, player.r, floor);
		if (isColliding)
		{
			if (player.vy >= 0 && player.y - player.r < floor.y)
			{
				player.y = floor.y - player.r;
				player.vy = 0;
				player.state = PlayerState::Ground;
				player.jumpCount = 0;
			}
			else if (player.vy <= 0 && player.y + player.r > floor.y + floor.height)
			{
				player.y = floor.y + floor.height + player.r;
				player.vy = 0;
			}
		}
	}
}

//�v���C���[���W�X�V
void PlayerPosi()
{
	//��ʒ[����
	if (player.x < player.r) 
		player.x = player.r;
	if (player.x > 1000 - player.r) 
		player.x = 1000 - player.r;
	//�ړ�
	player.x += player.vx;
	player.y += player.vy;
}

//�v���C���[�X�V
void UpdatePlayer(const std::vector<Floor>& floors, float deltaTime)
{
	PlayerMove();//�ړ�
	PlayerJump();//�W�����v
	PlayerGra();//�d��
	PlayerCollision(floors);//�����蔻��
	PlayerPosi();//���W

}

//�v���C���[�`��
void DrawPlayer()
{
	//DrawCircle(player.x,player.y,player.r, GetColor(255, 255, 255), false);
	DrawReverseGraph(player.x-player.r, player.y-player.r, player.img, true,!player.isRight);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "���F%f,���F%f\n%d",Obj_Player.x,Obj_Player.y,player.jumpCount);
}
