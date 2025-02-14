#pragma once
#include "DxLib.h"
#include <vector>

struct Enemy
{
    float x, y;//座標
    float vx;//移動速度
    float width, height;//幅と高さ
    float moveRange;//徘徊範囲 (初期位置からの移動距離)
    float initialX;//初期位置
    int img;//画像
    bool isAlive;//生存フラグ
    bool isRight;//右向きフラグ
};

struct EnemyManager
{
    std::vector<Enemy> enemies;//複数の敵を管理するリスト
    float respawnTimer = 0.0f;//リスポーンタイマー
    float respawnInterval = 5.0f;//リスポーン時間
};

extern EnemyManager enemyManager;

void InitEnemy(Enemy& enemy, float startX, float startY);//敵初期化
void UpdateEnemy(Enemy& enemy, float deltaTime);//敵更新
void DrawEnemy(const Enemy& enemy);//敵描画