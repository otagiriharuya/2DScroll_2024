#include "DxLib.h"
#include "FloorManager.h"
#include <algorithm>

void FloorManager::AddFloor(const Floor& floor)
{
    floors.push_back(floor);
}

void FloorManager::RemoveFloor(int index)
{
    if (index >= 0 && index < floors.size())
        floors.erase(floors.begin() + index);
}

void FloorManager::RemoveFloorIf(std::function<bool(const Floor&)> predicate)
{
    floors.erase(std::remove_if(floors.begin(), floors.end(), predicate), floors.end());
}

void FloorManager::DrawFloors()
{
    for (const auto& floor : floors)
    {
        DrawGraph(floor.x, floor.y, floor.img, true);
    }
}

const std::vector<Floor>& FloorManager::GetFloors() const
{
    return floors;
}