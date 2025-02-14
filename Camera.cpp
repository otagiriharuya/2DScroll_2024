#include "DxLib.h"
#include "Camera.h"

Camera camera;//�J�����C���X�^���X

//�J����������
void InitCamera(Camera& camera, float width, float height)
{
    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.width = width;
    camera.height = height;
    camera.zoom = 1.0f;
}

//�J�����X
void UpdateCamera(Camera& camera, float playerX, float playerY)
{
    //�J�����̒��S���v���C���[�ɒǏ]����悤�ɂ���
    camera.x = playerX - camera.width / (2.0f * camera.zoom);
    camera.y = playerY - camera.height / (2.0f * camera.zoom);

    //�}�b�v�̒[�ŃJ�������~�܂�悤�ɂ���
    const float MapWidth = 2000.0f;//�}�b�v�̍ő啝
    const float MapHeight = 800.0f;//�}�b�v�̍ő卂��
    if (camera.x < 0.0f) camera.x = 0.0f;
    if (camera.y < 0.0f) camera.y = 0.0f;
    if (camera.x > MapWidth - camera.width / camera.zoom) camera.x = MapWidth - camera.width / camera.zoom;
    if (camera.y > MapHeight - camera.height / camera.zoom) camera.y = MapHeight - camera.height / camera.zoom;

    //�J�����̃Y�[���@�\

}

//���[���h���W���X�N���[�����W�ɕϊ�
float WorldToScreenX(const Camera& camera, float worldX)
{
    return (worldX - camera.x) * camera.zoom;
}

float WorldToScreenY(const Camera& camera, float worldY)
{
    return (worldY - camera.y) * camera.zoom;
}   