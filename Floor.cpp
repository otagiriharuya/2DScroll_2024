#include "DxLib.h"
#include <vector>
#include "Player.h"
#include "Floor.h"

std::vector<Floor> floors;//床のリスト

//床の初期化
void initFloors()
{
    Floor floor0 = { 50,400,200,50 };
    int result = LoadGraph("Bloc03.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc03.jpgの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
        return;//追加
    }
    else
        floor0.img = result;
    floors.push_back(floor0);

    Floor floor1 = { 300, 300, 150, 50 };
    result = LoadGraph("Bloc02.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc02.jpgの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
        return;//追加
    }
    else
        floor1.img = result;
    floors.push_back(floor1);

    Floor floor2 = { 600, 250, 100, 50 };
    result = LoadGraph("Bloc01.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc01.jpgの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
        return;//追加
    }
    else
        floor2.img = result;
    floors.push_back(floor2);

    Floor floor3 = { 900, 80, 100, 50 };
    result = LoadGraph("Bloc01.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc01.jpgの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
        return;//追加
    }
    else
        floor3.img = result;
    floors.push_back(floor3);

    Floor floor4 = { 0, 700, 1000, 100 };
    result = LoadGraph("Ground.png", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Ground.pngの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);
        return;//追加
    }
    else
        floor4.img = result;
    floors.push_back(floor4);
}

//床の描画
void DrawFloors()
{
    for (const auto& floor : floors)
    {
        DrawGraph(floor.x, floor.y, floor.img, true);
    }
}
