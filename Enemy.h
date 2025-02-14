#pragma once
#include "DxLib.h"
#include <vector>

struct Enemy
{
    float x, y;//���W
    float vx;//�ړ����x
    float width, height;//���ƍ���
    float moveRange;//�p�j�͈� (�����ʒu����̈ړ�����)
    float initialX;//�����ʒu
    int img;//�摜
    bool isAlive;//�����t���O
    bool isRight;//�E�����t���O
};

struct EnemyManager
{
    std::vector<Enemy> enemies;//�����̓G���Ǘ����郊�X�g
    float respawnTimer = 0.0f;//���X�|�[���^�C�}�[
    float respawnInterval = 5.0f;//���X�|�[������
};

extern EnemyManager enemyManager;

void InitEnemy(Enemy& enemy, float startX, float startY);//�G������
void UpdateEnemy(Enemy& enemy, float deltaTime);//�G�X�V
void DrawEnemy(const Enemy& enemy);//�G�`��