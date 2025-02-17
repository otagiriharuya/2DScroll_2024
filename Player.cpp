#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include "Effect.h"
#include "Enemy.h"
#include "Camera.h"
#include "GameState.h"
#include <algorithm>
#include <math.h>

// �萔
const float Gravity = 7.0f;//�d��
const float MAX_VY = 1000.0f; // �ő嗎�����x
const float MoveSpeed = 300.0f;//���@�̈ړ��X�s�[�h
const float JumpPower = -500.0f;//���@�̃W�����v��
const int MaxJumps = 2;//�ő�W�����v��
const int WindowWidth = 2000;//�E�B���h�E�̉��ő吔

PlayerStatus player;//�v���C���[�C���X�^���X

//�v���C���[�������֐�
void InitPlayer()
{
	player.img = LoadGraph("Ghost.png", true);//�摜
	player.x = 150;//x���W
	player.y = 600;//y���W
	player.vx = 0;//���ړ���
	player.vy = 0;//�c�ړ���
	player.jumpPower = JumpPower;//�W�����v��
	player.r = 25;//���a
	player.jumpCount = 0;//�W�����v������
	player.maxJumps = MaxJumps;//�ő�W�����v��
	player.isSpace = false;//Space�L�[����������
	player.isRight = true;//�E�������Ă��邩
	player.isAlive = true;//�����Ă��邩
	player.state = PlayerState::Ground;//���݂̏��

	//�̗͉摜�ǂݍ���
	player.hpFullImg = LoadGraph("Life1.0.png");//�ő�
	player.hpHalfImg = LoadGraph("Life0.5.png");//����
	player.hpEmptyImg = LoadGraph("Life0.0.png");//��

	//�̗͊֘A������g
	player.maxHp = 5;//�ő�̗�
	player.Hp = 5;//�̗�
	player.hitCoolDownTime = 1.0f;//�N�[���_�E���^�C����ݒ�
	player.hitCoolDownTimer = 0.0f;//�N�[���_�E���^�C�}�[
	player.hpX = 10;//�̗͕\��X���W
	player.hpY = 10;//�̗͕\��Y���W
	player.hpOffsetX = 40;//�n�[�g�̊Ԋu
}

//�v���C���[�X�V�֐�
void UpdatePlayer(float deltaTime)
{
	PlayerMove();
	PlayerJump();
	PlayerGra();
	PlayerPosi(deltaTime);
	PlayerCollision(deltaTime);
	PlayerDeath();
}

//�v���C���[�ړ�����
void PlayerMove()
{
	float MS = MoveSpeed;
	//���V�t�g�������Ă���Ƃ��_�b�V��
	if (CheckHitKey(KEY_INPUT_LSHIFT))
		MS *= 2;
	//�n�ʂɂ��Ȃ��Ƃ��X�s�[�h���Z�b�g
	if (player.state != PlayerState::Ground)
		MS = MoveSpeed;

	//���ړ�
	if (CheckHitKey(KEY_INPUT_A))
	{
		player.vx = -MS;
		player.isRight = false;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.vx = MS;
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

		//�n�ʂɂ��邩�W�����v�����񐔂�2�񖢖���������
		if (player.state == PlayerState::Ground || player.jumpCount < player.maxJumps)
		{
			//�W�����v�G�t�F�N�g
			StartJumpEffect(player.x - 50, player.y - 50);
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

//�v���C���[�d�͓K�p
void PlayerGra()
{
	//�d�͂ɂ�闎��
	player.vy += Gravity;
	//��������
	if (player.state != PlayerState::Ground && player.vy > 0)
		player.state = PlayerState::Falling;//������
}

//�v���C���[���W�X�V
void PlayerPosi(float deltaTime)
{
	//��ʒ[����
	if (player.x < player.r)
		player.x = player.r;
	if (player.x > WindowWidth - player.r)
		player.x = WindowWidth - player.r;
	//�ړ�
	player.x += player.vx * deltaTime;
	if (player.vy >= MAX_VY)player.vy = MAX_VY;//�ő嗎�����x�𒴂���ꍇ�͐���
	player.y += player.vy * deltaTime;
}

//�~�Ƌ�`�̓����蔻��
bool CheckCollision(float circleX, float circleY, float circleR,
	float rectX, float rectY, float rectWidth, float rectHeight)
{
	//�~�̒��S�Ƌ�`�̒��S�Ƃ̋������v�Z
	float distX = fabs(circleX - (rectX + rectWidth / 2));
	float distY = fabs(circleY - (rectY + rectHeight / 2));

	//�~����`���痣��Ă���ꍇ
	if (distX > (rectWidth / 2 + circleR))
		return false;//�Փ˂��Ă��Ȃ�
	if (distY > (rectHeight / 2 + circleR))
		return false;//�Փ˂��Ă��Ȃ�

	//�~�̒��S����`�̓����ɂ���ꍇ
	if (distX <= (rectWidth / 2))
		return true;//�Փ˂��Ă���
	if (distY <= (rectHeight / 2))
		return true;//�Փ˂��Ă���

	//�p�̏Փ˔���
	float dx = distX - rectWidth / 2;
	float dy = distY - rectHeight / 2;
	//�����ɂ߂荞��ł��邩����
	return (dx * dx + dy * dy <= (circleR * circleR));
}

//�~���m�̓����蔻��
bool CheckCollisionCircles(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));//����
	return distance < r1 + r2;//�������Ă��邩
}

//�v���C���[�����蔻��
void PlayerCollision(float deltaTime)
{
	//���Ƃ̓����蔻��
	bool isCollision = false;
	//���̐�����
	for (int i = 0; i < MaxFloors; ++i)
	{
		if (CheckCollision(player.x, player.y, player.r,
			floors[i].x, floors[i].y, floors[i].width, floors[i].height))
		{
			isCollision = true;
			//�����蔻�莞�̏����i��F�������~�߂�j
			if (player.vy > 0) {
				float penetration = (player.y + player.r) - floors[i].y; // �߂荞�ݗʂ��v�Z
				player.y -= penetration; // �߂荞�ݗʂ����߂�
				player.vy = 0;
				player.state = PlayerState::Ground;
				player.jumpCount = 0;
			}
		}
	}

	//�n�ʂɂ��Ȃ��ꍇ
	if (!isCollision)
		player.state = PlayerState::Falling;

	//�����蔻��N�[���_�E���^�C�}�[���X�V
	if (player.hitCoolDownTimer > 0.0f)
	{
		player.hitCoolDownTimer -= deltaTime;
	}

	float damage = 0.5f; //��x�Ɍ��炷�̗�

	//�G�Ƃ̓����蔻��
    float enemyRadius = enemy.width / 2.0f;
	//
	if (enemy.isAlive && player.hitCoolDownTimer <= 0.0f && CheckCollisionCircles(player.x, player.y, player.r, enemy.x, enemy.y, enemyRadius))
	{
		//���炷�̗͂����݂�HP�𒴂��Ȃ��悤�ɂ���
		if (damage > player.Hp)
		{
			damage = player.Hp;
		}
		player.Hp -= damage;//�̗͂����炷

		if (player.Hp < 0.0f)
			player.Hp = 0.0f;//�̗͂�0�����ɂȂ�Ȃ��悤�ɂ���
		player.hitCoolDownTimer = player.hitCoolDownTime;//�N�[���_�E���^�C�}�[�����Z�b�g
	}
}

//�v���C���[���S����
void PlayerDeath()
{	//�̗͂�0�ȉ��ɂȂ�����
	if (player.Hp <= 0)
	{
		player.Hp = 0;
		player.isAlive = false;
		//�Q�[���I�[�o�[��Ԃɂ���
		gameState = GameState::GameOver;//�Q�[���I�[�o�[��Ԃɂ���
	}
	//�������đ̗͂��c���Ă�����
	if (player.y >= 800 && player.Hp > 0)
	{
		player.Hp--;
		player.isRight = true;
		player.x = 150;//x���W
		player.y = 600;//y���W
	}
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", player.Hp);
}


//�v���C���[�`��֐�
void DrawPlayer()
{
	//�`����X���W,�`����Y���W,�摜,���߂��邩,���]�����邩
	DrawReverseGraph(WorldToScreenX(camera, player.x - 25), WorldToScreenY(camera, player.y - 25),
		player.img, true, !player.isRight);

	DrawHp();
}

//�̗͕`��֐�
void DrawHp()
{
    for (int i = 0; i < player.maxHp; ++i)
    {
        int imgHandle = player.hpEmptyImg;//�ŏ��͋�̃n�[�g

        if (player.Hp >= i + 1)
        {
            imgHandle = player.hpFullImg;//���^���̃n�[�g
        }
        else if (player.Hp > i && player.Hp < i + 1)//�����\��
        {
            imgHandle = player.hpHalfImg;//�����̃n�[�g
        }

        DrawGraph(player.hpX + i * player.hpOffsetX, player.hpY, imgHandle, TRUE);
    }
}