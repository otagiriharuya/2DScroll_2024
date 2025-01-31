#pragma once
#include <vector>
#include <functional>
#include "Floor.h"

class FloorManager {
public:
    // 床を追加
    void AddFloor(const Floor& floor);
    // 指定したインデックスの床を削除
    void RemoveFloor(int index);

    // 条件に合致する床を削除
    void RemoveFloorIf(std::function<bool(const Floor&)> predicate);

    // すべての床を描画
    void DrawFloors();

    // すべての床への参照を返す
    const std::vector<Floor>& GetFloors() const;

private:
    std::vector<Floor> floors;
};