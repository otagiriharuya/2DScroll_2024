#pragma once
#include <chrono>
#include "FloorManager.h"

//プロトタイプ宣言
void GameInitResources();//ゲームリソースの初期化
void GameInitObj();//ゲームオブジェの初期化
void GameUpdate(float deltaTime);//ゲームの更新
void GameDraw();//ゲームの描画