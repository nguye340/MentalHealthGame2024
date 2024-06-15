#include "QGesture.h"
#include "QGeometry.h"

const int32 UQGesture::SAMPLING_RESOLUTION = 64;
const int32 UQGesture::MAX_INT_COORDINATES = 1024;
const int32 UQGesture::LUT_SIZE = 64;
const int32 UQGesture::LUT_SCALE_FACTOR = MAX_INT_COORDINATES / LUT_SIZE;

void UQGesture::Initialize(const TArray<UQPoint*>& InPoints, const FString& GestureName, bool ComputeLUT)
{
    Name = GestureName;
    PointsRaw = InPoints;

    // Deep copy points
    for (UQPoint* Point : InPoints)
    {
        PointsRaw.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(), Point->X, Point->Y, Point->ID));
    }

    Normalize(ComputeLUT);
}

void UQGesture::Normalize(bool ComputeLUT)
{
    Points = Resample(PointsRaw, SAMPLING_RESOLUTION);
    Points = Scale(Points);
    Points = TranslateTo(Points, Centroid(Points));

    if (ComputeLUT)
    {
        TransformCoordinatesToIntegers();
        ConstructLUT();
    }
}

TArray<UQPoint*> UQGesture::Resample(const TArray<UQPoint*>& InPoints, int32 N)
{
    TArray<UQPoint*> NewPoints;
    NewPoints.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(), InPoints[0]->X, InPoints[0]->Y, InPoints[0]->ID));
    int32 NumPoints = 1;

    float I = PathLength(InPoints) / (N - 1);
    float D = 0;
    for (int32 i = 1; i < InPoints.Num(); i++)
    {
        if (InPoints[i]->ID == InPoints[i - 1]->ID)
        {
            float d = UQGeometry::EuclideanDistance(InPoints[i - 1], InPoints[i]);
            if (D + d >= I)
            {
                UQPoint* FirstPoint = InPoints[i - 1];
                while (D + d >= I)
                {
                    float t = FMath::Clamp((I - D) / d, 0.0f, 1.0f);
                    if (FMath::IsNaN(t)) t = 0.5f;

                    NewPoints.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(),
                        (1.0f - t) * FirstPoint->X + t * InPoints[i]->X,
                        (1.0f - t) * FirstPoint->Y + t * InPoints[i]->Y,
                        InPoints[i]->ID));

                    d = D + d - I;
                    D = 0;
                    FirstPoint = NewPoints[NumPoints++];
                }
                D = d;
            }
            else
            {
                D += d;
            }
        }
    }

    if (NumPoints == N - 1)
    {
        NewPoints.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(), InPoints.Last()->X, InPoints.Last()->Y, InPoints.Last()->ID));
    }

    return NewPoints;
}

TArray<UQPoint*> UQGesture::Scale(const TArray<UQPoint*>& InPoints)
{
    float MinX = TNumericLimits<float>::Max();
    float MinY = TNumericLimits<float>::Max();
    float MaxX = TNumericLimits<float>::Min();
    float MaxY = TNumericLimits<float>::Min();

    for (UQPoint* Point : InPoints)
    {
        MinX = FMath::Min(MinX, Point->X);
        MinY = FMath::Min(MinY, Point->Y);
        MaxX = FMath::Max(MaxX, Point->X);
        MaxY = FMath::Max(MaxY, Point->Y);
    }

    float ScaleFactor = FMath::Max(MaxX - MinX, MaxY - MinY);
    TArray<UQPoint*> NewPoints;

    for (UQPoint* Point : InPoints)
    {
        NewPoints.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(),
            (Point->X - MinX) / ScaleFactor,
            (Point->Y - MinY) / ScaleFactor,
            Point->ID));
    }

    return NewPoints;
}

TArray<UQPoint*> UQGesture::TranslateTo(const TArray<UQPoint*>& InPoints, UQPoint* P)
{
    TArray<UQPoint*> NewPoints;
    for (UQPoint* Point : InPoints)
    {
        NewPoints.Add(NewObject<UQPoint>(this, UQPoint::StaticClass(),
            Point->X - P->X,
            Point->Y - P->Y,
            Point->ID));
    }

    return NewPoints;
}

UQPoint* UQGesture::Centroid(const TArray<UQPoint*>& InPoints)
{
    float SumX = 0;
    float SumY = 0;

    for (UQPoint* Point : InPoints)
    {
        SumX += Point->X;
        SumY += Point->Y;
    }

    return NewObject<UQPoint>(this, UQPoint::StaticClass(), SumX / InPoints.Num(), SumY / InPoints.Num(), 0);
}

float UQGesture::PathLength(const TArray<UQPoint*>& InPoints)
{
    float Length = 0;
    for (int32 i = 1; i < InPoints.Num(); i++)
    {
        if (InPoints[i]->ID == InPoints[i - 1]->ID)
        {
            Length += UQGeometry::EuclideanDistance(InPoints[i - 1], InPoints[i]);
        }
    }
    return Length;
}

void UQGesture::TransformCoordinatesToIntegers()
{
    for (UQPoint* Point : Points)
    {
        Point->IntX = static_cast<int32>((Point->X + 1.0f) / 2.0f * (MAX_INT_COORDINATES - 1));
        Point->IntY = static_cast<int32>((Point->Y + 1.0f) / 2.0f * (MAX_INT_COORDINATES - 1));
    }
}

void UQGesture::ConstructLUT()
{
    LUT.SetNum(LUT_SIZE);
    for (int32 i = 0; i < LUT_SIZE; i++)
    {
        LUT[i].SetNum(LUT_SIZE);
    }

    for (int32 i = 0; i < LUT_SIZE; i++)
    {
        for (int32 j = 0; j < LUT_SIZE; j++)
        {
            int32 MinDistance = TNumericLimits<int32>::Max();
            int32 IndexMin = -1;

            for (int32 t = 0; t < Points.Num(); t++)
            {
                int32 Row = Points[t]->IntY / LUT_SCALE_FACTOR;
                int32 Col = Points[t]->IntX / LUT_SCALE_FACTOR;
                int32 Distance = FMath::Square(Row - i) + FMath::Square(Col - j);

                if (Distance < MinDistance)
                {
                    MinDistance = Distance;
                    IndexMin = t;
                }
            }
            LUT[i][j] = IndexMin;
        }
    }
}
