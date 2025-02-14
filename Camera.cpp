#include "DxLib.h"
#include "Camera.h"

Camera camera;//カメラインスタンス

//カメラ初期化
void InitCamera(Camera& camera, float width, float height)
{
    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.width = width;
    camera.height = height;
    camera.zoom = 1.0f;
}

//カメラ更
void UpdateCamera(Camera& camera, float playerX, float playerY)
{
    //カメラの中心がプレイヤーに追従するようにする
    camera.x = playerX - camera.width / (2.0f * camera.zoom);
    camera.y = playerY - camera.height / (2.0f * camera.zoom);

    //マップの端でカメラが止まるようにする
    const float MapWidth = 2000.0f;//マップの最大幅
    const float MapHeight = 800.0f;//マップの最大高さ
    if (camera.x < 0.0f) camera.x = 0.0f;
    if (camera.y < 0.0f) camera.y = 0.0f;
    if (camera.x > MapWidth - camera.width / camera.zoom) camera.x = MapWidth - camera.width / camera.zoom;
    if (camera.y > MapHeight - camera.height / camera.zoom) camera.y = MapHeight - camera.height / camera.zoom;

    //カメラのズーム機能

}

//ワールド座標をスクリーン座標に変換
float WorldToScreenX(const Camera& camera, float worldX)
{
    return (worldX - camera.x) * camera.zoom;
}

float WorldToScreenY(const Camera& camera, float worldY)
{
    return (worldY - camera.y) * camera.zoom;
}   