#include "DxLib.h"	
#include "Enemy.h"
#include "Map.h"
#include "Camera.h"

Enemy enemy;

//�~�Ƌ�`�̓����蔻��
bool CheckCollision(float circleX, float circleY, float circleR,
    float rectX, float rectY, float rectWidth, float rectHeight);

//�G������
void InitEnemy(Enemy& enemy, float startX, float startY)
{
    enemy.x = startX;
    enemy.y = startY;
    enemy.vx = 100.0f;//�ړ����x
    enemy.width =80.0f;
    enemy.height =80.0f;
    enemy.moveRange = 100.0f;//�p�j�͈�
    enemy.initialX = startX;
    enemy.img = LoadGraph("Reaper.png", true);//�G�̉摜�����[�h
    enemy.isAlive = true;
    enemy.isRight = true;
}

//�G�X�V
void UpdateEnemy(Enemy& enemy, float deltaTime)
{
    //�p�j�͈͂𒴂����甽�]
    if (enemy.x >= enemy.initialX + enemy.moveRange)
    {
        enemy.vx = -abs(enemy.vx);
        enemy.isRight = false;
    }
    else if (enemy.x <= enemy.initialX - enemy.moveRange)
    {
        enemy.vx = abs(enemy.vx);
        enemy.isRight = true;
    }

    //�ړ�
    enemy.x += enemy.vx * deltaTime;

    bool isCollision = false;
    //���̐�����
    for (int i = 0; i < MaxFloors; ++i)
    {
        //�~�Ƌ�`�̓����蔻��
        if (CheckCollision(enemy.x, enemy.y, enemy.width / 2,
            floors[i].x, floors[i].y, floors[i].width, floors[i].height))
        {
            isCollision = true;
            //�����蔻�莞�̏���(��F�������~�߂�)
            //if (enemy.vy > 0)
            {
                enemy.y = floors[i].y - enemy.height / 2;//�߂荞�ݗʂ����߂�
                //enemy.vy = 0;
                //enemy.state = PlayerState::Ground;
                //enemy.jumpCount = 0;
            }
        }
    }
}

//�G�`��
void DrawEnemy(const Enemy& enemy)
{
    DrawReverseGraph(WorldToScreenX(camera, enemy.x), WorldToScreenY(camera, enemy.y),
        enemy.img, true, !enemy.isRight);
}