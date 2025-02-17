#pragma once

//プレイヤーの状態
enum class PlayerState
{
    Ground,//地面にいる
    Jump1,//ジャンプ1回目
    Jump2,//ジャンプ2回目
    Falling,//落下中
};

//プレイヤーの情報
struct PlayerStatus
{
    float x, y;//座標
    float vx, vy;//移動量
    float r;//半径
    float jumpPower;//ジャンプ力
    int img;//画像
    int jumpCount;//ジャンプした回数
    int maxJumps;//最大ジャンプ数
    bool isSpace;//スペースキーが押されたか
    bool isRight;//右を向いているか
    bool isAlive;//生きているか
    PlayerState state;//現在の状態

    //体力関連
    float maxHp;//最大体力
    float Hp;//体力
    float hitCoolDownTime;//当たり判定クールダウン時間
    float hitCoolDownTimer;//当たり判定クールダウンタイマー
    int hpFullImg;//体力満タン画像
    int hpHalfImg;//体力半分画像
    int hpEmptyImg;//体力空画像
    int hpX, hpY;//体力表示座標
    int hpOffsetX;//ハートの間隔
};

extern PlayerStatus player;

void InitPlayer();//プレイヤー初期化関数
void UpdatePlayer(float deltaTime);//プレイヤー更新関数
void DrawPlayer();//プレイヤー描画関数
void DrawHp();//体力描画

void PlayerGra();//重力加速度敵用
void PlayerMove();//プレイヤー移動処理
void PlayerJump();//プレイヤージャンプ処理
void PlayerPosi(float deltaTime);//プレイヤー座標更新
void PlayerCollision(float deltaTime);//プレイヤー当たり判定
void PlayerDeath();//プレイヤー死亡判定