#pragma once

//�J�����̏��
struct Camera
{
	float x, y;//���W(���S��)
	float width, height;//�����ƕ�
	float zoom;//�Y�[���{��
};

extern Camera camera;//�J�����C���X�^���X

void InitCamera(Camera& camera, float width, float height);//�J����������
void UpdateCamera(Camera& camera, float playerX, float playerY);//�J�����X�V
//���[���h���W���X�N���[�����W�ɕϊ�
float WorldToScreenX(const Camera& camera, float worldX);
float WorldToScreenY(const Camera& camera, float worldY);