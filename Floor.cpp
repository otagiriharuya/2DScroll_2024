#include "DxLib.h"
#include "Floor.h"
#include "FloorManager.h"

extern FloorManager floorManager;//�t���A�}�l�[�W���[�̃C���X�^���X��錾

//���̏�����
void initFloors(FloorManager& floorManager)
{
    Floor floor0 = { 50,400,200,50 };
    int result = LoadGraph("Bloc03.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc03.jpg�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
        //return;
    }
    else
        floor0.img = result;
    floorManager.AddFloor(floor0);

    Floor floor1 = { 300, 300, 150, 50 };
    result = LoadGraph("Bloc02.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc02.jpg�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
        return;
    }
    else
        floor1.img = result;
    floorManager.AddFloor(floor1);

    Floor floor2 = { 600, 250, 100, 50 };
    result = LoadGraph("Bloc01.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc01.jpg�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
        return;
    }
    else
        floor2.img = result;
    floorManager.AddFloor(floor2);

    Floor floor3 = { 900, 80, 100, 50 };
    result = LoadGraph("Bloc01.jpg", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Bloc01.jpg�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
        return;
    }
    else
        floor3.img = result;
    floorManager.AddFloor(floor3);

    Floor floor4 = { 0, 700, 1000, 100 };
    result = LoadGraph("Ground.png", true);
    if (result == -1)
    {
        MessageBox(nullptr, "Ground.png�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);
        return;
    }
    else
        floor4.img = result;
    floorManager.AddFloor(floor4);
}