#pragma once
#include <vector>
#include <cstdint>//int32_t���g�p���邽��

//���̍\����
struct Floor
{
	float x, y;//���W
	float width, height;//���ƍ���
	int img;//�摜
};

extern std::vector<Floor> floors;

//���̏�����
void initFloors();

//���̕`��
void DrawFloors();