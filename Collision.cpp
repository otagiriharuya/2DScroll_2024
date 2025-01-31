#include "DxLib.h"
#include <iostream>
#include "Game.h"

static bool CheckCollision(float circleX, float circleY, float circleR,
    float rectX, float rectY, float rectWidth, float rectHeight)
{
    float distX = abs(circleX - (rectX + rectWidth / 2));
    float distY = abs(circleY - (rectY + rectHeight / 2));

    if (distX > (rectWidth / 2 + circleR))
        return false;
    if (distY > (rectHeight / 2 + circleR))
        return false;

    if (distX <= (rectWidth / 2))
        return true;
    if (distY <= (rectHeight / 2))
        return true;

    float dx = distX - rectWidth / 2;
    float dy = distY - rectHeight / 2;
    return (dx * dx + dy * dy <= (circleR * circleR));
}