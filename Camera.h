#pragma once

//カメラの情報
struct Camera
{
	float x, y;//座標(中心の)
	float width, height;//高さと幅
	float zoom;//ズーム倍率
};

extern Camera camera;//カメラインスタンス

void InitCamera(Camera& camera, float width, float height);//カメラ初期化
void UpdateCamera(Camera& camera, float playerX, float playerY);//カメラ更新
//ワールド座標をスクリーン座標に変換
float WorldToScreenX(const Camera& camera, float worldX);
float WorldToScreenY(const Camera& camera, float worldY);