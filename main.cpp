#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include "Effect.h"
#include "Camera.h"
#include "GameState.h"
#include "Enemy.h" 
#include <chrono>//時間計測用

Enemy enemy;

//ポーズ画面の選択肢
enum class PauseMenuChoice
{
    Resume,//再開
    ExitToTitle//タイトルに戻る
};
void Init();

GameState gameState = GameState::Title;//初期状態はタイトル画面
PauseMenuChoice currentChoice = PauseMenuChoice::Resume;//再開に合わせる

//時間計測用
auto prevTime = std::chrono::high_resolution_clock::now();

//タイトル画面の更新処理
void UpdateTitle(float deltaTime)
{

}

//タイトル画面の描画処理
void DrawTitle()
{
    DrawString(400, 400, "Gキーを押してゲームスタート", GetColor(255, 255, 255));
}

//ポーズ画面の更新処理
void UpdatePause(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_W))
    {
        currentChoice = PauseMenuChoice::Resume;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        currentChoice = PauseMenuChoice::ExitToTitle;
    }

    if (CheckHitKey(KEY_INPUT_RETURN))//決定キー
    {
        switch (currentChoice)
        {
        case PauseMenuChoice::Resume:
            gameState = GameState::Game;//ゲーム再開
            break;
        case PauseMenuChoice::ExitToTitle:
            Init();//ゲームを初期状態に
            gameState = GameState::Title;//タイトルに戻る
            break;
        }
    }
}

//ポーズ画面の描画処理
void DrawPause()
{
    //ポーズ画面の背景を描画
    DrawBox(0, 0, 1000, 800, GetColor(0, 0, 0), TRUE);//黒い背景
    //選択肢の描画
    int resumeColor = (currentChoice == PauseMenuChoice::Resume) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
    int exitColor = (currentChoice == PauseMenuChoice::ExitToTitle) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

    DrawString(400, 300, "Resume", resumeColor);//再開
    DrawString(400, 350, "Exit to Title", exitColor);//タイトルに戻る
}

//ゲームオーバー画面の更新処理
void UpdateGameOver(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_W))
    {
        currentChoice = PauseMenuChoice::Resume;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        currentChoice = PauseMenuChoice::ExitToTitle;
    }

    if (CheckHitKey(KEY_INPUT_RETURN))//決定キー
    {
        Init();//ゲームを初期状態に
        switch (currentChoice)
        {
        case PauseMenuChoice::Resume:
            gameState = GameState::Game;//ゲーム画面へ
            break;
        case PauseMenuChoice::ExitToTitle:
            gameState = GameState::Title;//タイトルに戻る
            break;
        }
    }
}

//ゲームオーバー画面の描画処理
void DrawGameOver()
{
    //ポーズ画面の背景を描画
    DrawBox(0, 0, 1000, 800, GetColor(0, 0, 0), TRUE);//黒い背景
    //選択肢の描画
    int resumeColor = (currentChoice == PauseMenuChoice::Resume) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
    int exitColor = (currentChoice == PauseMenuChoice::ExitToTitle) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

    DrawString(400, 300, "Retry", resumeColor);//やり直す
    DrawString(400, 350, "Exit to Title", exitColor);//タイトルに戻る
}

//初期化関数
void Init()
{
    InitMap();//マップ初期化
    InitPlayer();//プレイヤー初期化
    InitEffect();//エフェクト初期化

    InitCamera(camera, 1000.0f, 800.0f);//カメラ初期化(画面サイズに合わせる)

    InitEnemy(enemy, 700.0f, 450.0f);//敵初期位置指定
}

//更新関数
void Update(float deltaTime)
{
    UpdateMap();//マップ更新
    UpdatePlayer(deltaTime);//プレイヤー更新
    UpdateEffect(deltaTime);//エフェクト更新
    UpdateCamera(camera, player.x, player.y);//カメラ更新(プレイヤーの情報を渡す)
    UpdateEnemy(enemy, deltaTime);//敵更新
}

//描画関数
void Draw()
{
    DrawMap();//マップ描画
    DrawPlayer();//プレイヤー描画
    if (enemy.isAlive == true)
        DrawEnemy(enemy);//敵描画
    DrawEffect();//エフェクト描画
}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(true);//ウィンドウモードで起動する
    SetGraphMode(1000, 800, 16);//画面のサイズとビット数変更
    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
    {
        return -1;			// エラーが起きたら直ちに終了
    }
    SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

    Init();//初期化

    //メイン処理
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        //デルタタイムの計算
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - prevTime);
        float deltaTime = static_cast<float>(elapsed.count()) / 1000000.0f;//秒単位
        prevTime = currentTime;

        //ゲームの状態に応じて処理を分岐
        switch (gameState)
        {
            //タイトル画面
        case GameState::Title:
            //タイトル画面の処理
            UpdateTitle(deltaTime);//更新
            DrawTitle();//描画
            if (CheckHitKey(KEY_INPUT_G))//スペースキーでゲーム開始
            {
                Init();//初期化
                gameState = GameState::Game;//ゲーム画面へ
            }
            break;

            //ゲーム画面
        case GameState::Game:
            if (CheckHitKey(KEY_INPUT_P))//Pキーが押されたらポーズ画面へ
            {
                gameState = GameState::Pause;
                currentChoice = PauseMenuChoice::Resume;//ポーズ画面に入る際に選択肢を「再開」にする
            }
            //ゲームプレイ画面の処理
            Update(deltaTime);//更新
            Draw();//描画
            break;

            //ポーズ画面
        case GameState::Pause:
            //ポーズ画面の処理
            UpdatePause(deltaTime);//更新
            DrawPause();//描画
            break;

            //ゲームオーバー画面
        case GameState::GameOver:
            //ゲームオーバー画面の処理
            UpdateGameOver(deltaTime);//更新
            DrawGameOver();//描画
            break;
        }
        ScreenFlip();//裏画面と表画面の入替
        ClearDrawScreen();//裏画面の描画を全て消去
    }

    DxLib_End();// ＤＸライブラリ使用の終了処理
    return 0;// ソフトの終了 
}