#include "DxLib.h"	
#include "Enemy.h"
#include "Map.h"
#include "Camera.h"

Enemy enemy;

//円と矩形の当たり判定
bool CheckCollision(float circleX, float circleY, float circleR,
    float rectX, float rectY, float rectWidth, float rectHeight);

//敵初期化
void InitEnemy(Enemy& enemy, float startX, float startY)
{
    enemy.x = startX;
    enemy.y = startY;
    enemy.vx = 100.0f;//移動速度
    enemy.width =80.0f;
    enemy.height =80.0f;
    enemy.moveRange = 100.0f;//徘徊範囲
    enemy.initialX = startX;
    enemy.img = LoadGraph("Reaper.png", true);//敵の画像をロード
    enemy.isAlive = true;
    enemy.isRight = true;
}

//敵更新
void UpdateEnemy(Enemy& enemy, float deltaTime)
{
    //徘徊範囲を超えたら反転
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

    //移動
    enemy.x += enemy.vx * deltaTime;

    bool isCollision = false;
    //床の数分回す
    for (int i = 0; i < MaxFloors; ++i)
    {
        //円と矩形の当たり判定
        if (CheckCollision(enemy.x, enemy.y, enemy.width / 2,
            floors[i].x, floors[i].y, floors[i].width, floors[i].height))
        {
            isCollision = true;
            //当たり判定時の処理(例：落下を止める)
            //if (enemy.vy > 0)
            {
                enemy.y = floors[i].y - enemy.height / 2;//めり込み量だけ戻す
                //enemy.vy = 0;
                //enemy.state = PlayerState::Ground;
                //enemy.jumpCount = 0;
            }
        }
    }
}

//敵描画
void DrawEnemy(const Enemy& enemy)
{
    DrawReverseGraph(WorldToScreenX(camera, enemy.x), WorldToScreenY(camera, enemy.y),
        enemy.img, true, !enemy.isRight);
}