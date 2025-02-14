#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include "Effect.h"
#include "Camera.h"
#include "GameState.h"
#include "Enemy.h" 
#include <chrono>//���Ԍv���p

Enemy enemy;

//�|�[�Y��ʂ̑I����
enum class PauseMenuChoice
{
    Resume,//�ĊJ
    ExitToTitle//�^�C�g���ɖ߂�
};
void Init();

GameState gameState = GameState::Title;//������Ԃ̓^�C�g�����
PauseMenuChoice currentChoice = PauseMenuChoice::Resume;//�ĊJ�ɍ��킹��

//���Ԍv���p
auto prevTime = std::chrono::high_resolution_clock::now();

//�^�C�g����ʂ̍X�V����
void UpdateTitle(float deltaTime)
{

}

//�^�C�g����ʂ̕`�揈��
void DrawTitle()
{
    DrawString(400, 400, "G�L�[�������ăQ�[���X�^�[�g", GetColor(255, 255, 255));
}

//�|�[�Y��ʂ̍X�V����
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

    if (CheckHitKey(KEY_INPUT_RETURN))//����L�[
    {
        switch (currentChoice)
        {
        case PauseMenuChoice::Resume:
            gameState = GameState::Game;//�Q�[���ĊJ
            break;
        case PauseMenuChoice::ExitToTitle:
            Init();//�Q�[����������Ԃ�
            gameState = GameState::Title;//�^�C�g���ɖ߂�
            break;
        }
    }
}

//�|�[�Y��ʂ̕`�揈��
void DrawPause()
{
    //�|�[�Y��ʂ̔w�i��`��
    DrawBox(0, 0, 1000, 800, GetColor(0, 0, 0), TRUE);//�����w�i
    //�I�����̕`��
    int resumeColor = (currentChoice == PauseMenuChoice::Resume) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
    int exitColor = (currentChoice == PauseMenuChoice::ExitToTitle) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

    DrawString(400, 300, "Resume", resumeColor);//�ĊJ
    DrawString(400, 350, "Exit to Title", exitColor);//�^�C�g���ɖ߂�
}

//�Q�[���I�[�o�[��ʂ̍X�V����
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

    if (CheckHitKey(KEY_INPUT_RETURN))//����L�[
    {
        Init();//�Q�[����������Ԃ�
        switch (currentChoice)
        {
        case PauseMenuChoice::Resume:
            gameState = GameState::Game;//�Q�[����ʂ�
            break;
        case PauseMenuChoice::ExitToTitle:
            gameState = GameState::Title;//�^�C�g���ɖ߂�
            break;
        }
    }
}

//�Q�[���I�[�o�[��ʂ̕`�揈��
void DrawGameOver()
{
    //�|�[�Y��ʂ̔w�i��`��
    DrawBox(0, 0, 1000, 800, GetColor(0, 0, 0), TRUE);//�����w�i
    //�I�����̕`��
    int resumeColor = (currentChoice == PauseMenuChoice::Resume) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
    int exitColor = (currentChoice == PauseMenuChoice::ExitToTitle) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

    DrawString(400, 300, "Retry", resumeColor);//��蒼��
    DrawString(400, 350, "Exit to Title", exitColor);//�^�C�g���ɖ߂�
}

//�������֐�
void Init()
{
    InitMap();//�}�b�v������
    InitPlayer();//�v���C���[������
    InitEffect();//�G�t�F�N�g������

    InitCamera(camera, 1000.0f, 800.0f);//�J����������(��ʃT�C�Y�ɍ��킹��)

    InitEnemy(enemy, 700.0f, 450.0f);//�G�����ʒu�w��
}

//�X�V�֐�
void Update(float deltaTime)
{
    UpdateMap();//�}�b�v�X�V
    UpdatePlayer(deltaTime);//�v���C���[�X�V
    UpdateEffect(deltaTime);//�G�t�F�N�g�X�V
    UpdateCamera(camera, player.x, player.y);//�J�����X�V(�v���C���[�̏���n��)
    UpdateEnemy(enemy, deltaTime);//�G�X�V
}

//�`��֐�
void Draw()
{
    DrawMap();//�}�b�v�`��
    DrawPlayer();//�v���C���[�`��
    if (enemy.isAlive == true)
        DrawEnemy(enemy);//�G�`��
    DrawEffect();//�G�t�F�N�g�`��
}

//�v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(true);//�E�B���h�E���[�h�ŋN������
    SetGraphMode(1000, 800, 16);//��ʂ̃T�C�Y�ƃr�b�g���ύX
    if (DxLib_Init() == -1)		// �c�w���C�u��������������
    {
        return -1;			// �G���[���N�����璼���ɏI��
    }
    SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

    Init();//������

    //���C������
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        //�f���^�^�C���̌v�Z
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - prevTime);
        float deltaTime = static_cast<float>(elapsed.count()) / 1000000.0f;//�b�P��
        prevTime = currentTime;

        //�Q�[���̏�Ԃɉ����ď����𕪊�
        switch (gameState)
        {
            //�^�C�g�����
        case GameState::Title:
            //�^�C�g����ʂ̏���
            UpdateTitle(deltaTime);//�X�V
            DrawTitle();//�`��
            if (CheckHitKey(KEY_INPUT_G))//�X�y�[�X�L�[�ŃQ�[���J�n
            {
                Init();//������
                gameState = GameState::Game;//�Q�[����ʂ�
            }
            break;

            //�Q�[�����
        case GameState::Game:
            if (CheckHitKey(KEY_INPUT_P))//P�L�[�������ꂽ��|�[�Y��ʂ�
            {
                gameState = GameState::Pause;
                currentChoice = PauseMenuChoice::Resume;//�|�[�Y��ʂɓ���ۂɑI�������u�ĊJ�v�ɂ���
            }
            //�Q�[���v���C��ʂ̏���
            Update(deltaTime);//�X�V
            Draw();//�`��
            break;

            //�|�[�Y���
        case GameState::Pause:
            //�|�[�Y��ʂ̏���
            UpdatePause(deltaTime);//�X�V
            DrawPause();//�`��
            break;

            //�Q�[���I�[�o�[���
        case GameState::GameOver:
            //�Q�[���I�[�o�[��ʂ̏���
            UpdateGameOver(deltaTime);//�X�V
            DrawGameOver();//�`��
            break;
        }
        ScreenFlip();//����ʂƕ\��ʂ̓���
        ClearDrawScreen();//����ʂ̕`���S�ď���
    }

    DxLib_End();// �c�w���C�u�����g�p�̏I������
    return 0;// �\�t�g�̏I�� 
}