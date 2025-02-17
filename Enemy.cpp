#include "DxLib.h"	
#include "Enemy.h"
#include "Map.h"
#include "Camera.h"

Enemy enemy;

//â~Ç∆ãÈå`ÇÃìñÇΩÇËîªíË
bool CheckCollision(float circleX, float circleY, float circleR,
    float rectX, float rectY, float rectWidth, float rectHeight);

//ìGèâä˙âª
void InitEnemy(Enemy& enemy, float startX, float startY)
{
    enemy.x = startX;
    enemy.y = startY;
    enemy.vx = 100.0f;//à⁄ìÆë¨ìx
    enemy.width =80.0f;
    enemy.height =80.0f;
    enemy.moveRange = 100.0f;//úpújîÕàÕ
    enemy.initialX = startX;
    enemy.img = LoadGraph("Reaper.png", true);//ìGÇÃâÊëúÇÉçÅ[Éh
    enemy.isAlive = true;
    enemy.isRight = true;
}

//ìGçXêV
void UpdateEnemy(Enemy& enemy, float deltaTime)
{
    //úpújîÕàÕÇí¥Ç¶ÇΩÇÁîΩì]
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

    //à⁄ìÆ
    enemy.x += enemy.vx * deltaTime;

    bool isCollision = false;
    //è∞ÇÃêîï™âÒÇ∑
    for (int i = 0; i < MaxFloors; ++i)
    {
        //â~Ç∆ãÈå`ÇÃìñÇΩÇËîªíË
        if (CheckCollision(enemy.x, enemy.y, enemy.width / 2,
            floors[i].x, floors[i].y, floors[i].width, floors[i].height))
        {
            isCollision = true;
            //ìñÇΩÇËîªíËéûÇÃèàóù(ó·ÅFóéâ∫Çé~ÇﬂÇÈ)
            //if (enemy.vy > 0)
            {
                enemy.y = floors[i].y - enemy.height / 2;//ÇﬂÇËçûÇ›ó ÇæÇØñﬂÇ∑
                //enemy.vy = 0;
                //enemy.state = PlayerState::Ground;
                //enemy.jumpCount = 0;
            }
        }
    }
}

//ìGï`âÊ
void DrawEnemy(const Enemy& enemy)
{
    DrawReverseGraph(WorldToScreenX(camera, enemy.x), WorldToScreenY(camera, enemy.y),
        enemy.img, true, !enemy.isRight);
}