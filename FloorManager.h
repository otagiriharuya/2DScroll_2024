#pragma once
#include <vector>
#include <functional>
#include "Floor.h"

class FloorManager {
public:
    // ����ǉ�
    void AddFloor(const Floor& floor);
    // �w�肵���C���f�b�N�X�̏����폜
    void RemoveFloor(int index);

    // �����ɍ��v���鏰���폜
    void RemoveFloorIf(std::function<bool(const Floor&)> predicate);

    // ���ׂĂ̏���`��
    void DrawFloors();

    // ���ׂĂ̏��ւ̎Q�Ƃ�Ԃ�
    const std::vector<Floor>& GetFloors() const;

private:
    std::vector<Floor> floors;
};