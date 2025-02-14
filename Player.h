#pragma once

//�v���C���[�̏��
enum class PlayerState
{
    Ground,//�n�ʂɂ���
    Jump1,//�W�����v1���
    Jump2,//�W�����v2���
    Falling,//������
};

//�v���C���[�̏��
struct PlayerStatus
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
    bool isAlive;//�����Ă��邩
    PlayerState state;//���݂̏��
};

extern PlayerStatus player;

void InitPlayer();//�v���C���[�������֐�
void UpdatePlayer(float deltaTime);//�v���C���[�X�V�֐�
void DrawPlayer();//�v���C���[�`��֐�

void PlayerGra();//�d�͉����x�G�p
void PlayerMove();//�v���C���[�ړ�����
void PlayerJump();//�v���C���[�W�����v����
void PlayerPosi(float deltaTime);//�v���C���[���W�X�V
void PlayerCollision();//�v���C���[�����蔻��
void PlayerDeath();//�v���C���[���S����