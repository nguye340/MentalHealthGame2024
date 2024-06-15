#include "QGeometry.h"
#include "Math/UnrealMathUtility.h"

float UQGeometry::SqrEuclideanDistance(const UQPoint* A, const UQPoint* B)
{
    if (A == nullptr || B == nullptr) return 0.0f;
    return FMath::Square(A->X - B->X) + FMath::Square(A->Y - B->Y);
}

float UQGeometry::EuclideanDistance(const UQPoint* A, const UQPoint* B)
{
    if (A == nullptr || B == nullptr) return 0.0f;
    return FMath::Sqrt(SqrEuclideanDistance(A, B));
}
