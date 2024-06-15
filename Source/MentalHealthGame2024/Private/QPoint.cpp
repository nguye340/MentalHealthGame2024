#include "QPoint.h"

UQPoint::UQPoint()
    : X(0.0f), Y(0.0f), StrokeID(0), IntX(0), IntY(0)
{
}

void UQPoint::Initialize(float InX, float InY, int32 InStrokeID)
{
    X = InX;
    Y = InY;
    StrokeID = InStrokeID;
    IntX = 0;
    IntY = 0;
}
