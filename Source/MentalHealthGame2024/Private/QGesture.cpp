#include "QGesture.h"
#include "Math/UnrealMathUtility.h"

UQGesture::UQGesture()
{
}

UQGesture::UQGesture(const TArray<FQPoint>& InPoints, const FString& GestureName)
    : Name(GestureName)
{
    PointsRaw = InPoints;
    Normalize();
}

static const TArray<FQPoint> UQGesture::Convert(const TArray<FVector2D>& Vector2DPoints)
{
    TArray<FQPoint> NewPoints;

    for (int32 Index = 0; Index < Vector2DPoints.Num(); ++Index)
    {
        const FVector2D& Point = Vector2DPoints[Index];
        NewPoints.Add(FQPoint(Point.X, Point.Y, Index);
    }

    return NewPoints;
}

void UQGesture::Normalize(bool bComputeLUT)
{
    Points = Resample(PointsRaw, SAMPLING_RESOLUTION);
    Points = Scale(Points);
    Points = TranslateTo(Points, Centroid(Points));

    if (bComputeLUT)
    {
        TransformCoordinatesToIntegers();
        ConstructLUT();
    }
}

TArray<FQPoint> UQGesture::Scale(const TArray<FQPoint>& InPoints)
{
    float MinX = TNumericLimits<float>::Max();
    float MinY = TNumericLimits<float>::Max();
    float MaxX = TNumericLimits<float>::Lowest();
    float MaxY = TNumericLimits<float>::Lowest();

    for (const FQPoint& Point : InPoints)
    {
        if (MinX > Point.X) MinX = Point.X;
        if (MinY > Point.Y) MinY = Point.Y;
        if (MaxX < Point.X) MaxX = Point.X;
        if (MaxY < Point.Y) MaxY = Point.Y;
    }

    TArray<FQPoint> NewPoints;
    float Scale = FMath::Max(MaxX - MinX, MaxY - MinY);

    for (const FQPoint& Point : InPoints)
    {
        NewPoints.Add(FQPoint((Point.X - MinX) / Scale, (Point.Y - MinY) / Scale, Point.StrokeID));
    }

    return NewPoints;
}

TArray<FQPoint> UQGesture::TranslateTo(const TArray<FQPoint>& InPoints, const FQPoint& P)
{
    TArray<FQPoint> NewPoints;

    for (const FQPoint& Point : InPoints)
    {
        NewPoints.Add(FQPoint(Point.X - P.X, Point.Y - P.Y, Point.StrokeID));
    }

    return NewPoints;
}

FQPoint UQGesture::Centroid(const TArray<FQPoint>& InPoints)
{
    float CX = 0;
    float CY = 0;

    for (const FQPoint& Point : InPoints)
    {
        CX += Point.X;
        CY += Point.Y;
    }

    return FQPoint(CX / InPoints.Num(), CY / InPoints.Num(), 0);
}

TArray<FQPoint> UQGesture::Resample(const TArray<FQPoint>& InPoints, int32 N)
{
    TArray<FQPoint> NewPoints;
    NewPoints.Add(InPoints[0]);
    int32 NumPoints = 1;

    float I = PathLength(InPoints) / (N - 1);
    float D = 0;

    for (int32 i = 1; i < InPoints.Num(); ++i)
    {
        if (InPoints[i].StrokeID == InPoints[i - 1].StrokeID)
        {
            float d = FMath::Sqrt(FMath::Pow(InPoints[i].X - InPoints[i - 1].X, 2) + FMath::Pow(InPoints[i].Y - InPoints[i - 1].Y, 2));
            if (D + d >= I)
            {
                FQPoint FirstPoint = InPoints[i - 1];
                while (D + d >= I)
                {
                    float t = FMath::Clamp((I - D) / d, 0.0f, 1.0f);
                    if (FMath::IsNaN(t)) t = 0.5f;
                    NewPoints.Add(FQPoint(
                        (1.0f - t) * FirstPoint.X + t * InPoints[i].X,
                        (1.0f - t) * FirstPoint.Y + t * InPoints[i].Y,
                        InPoints[i].StrokeID
                    ));

                    d = D + d - I;
                    D = 0;
                    FirstPoint = NewPoints.Last();
                    NumPoints++;
                }
                D = d;
            }
            else D += d;
        }
    }

    if (NumPoints == N - 1)
        NewPoints.Add(InPoints.Last());

    return NewPoints;
}

float UQGesture::PathLength(const TArray<FQPoint>& InPoints)
{
    float Length = 0;

    for (int32 i = 1; i < InPoints.Num(); ++i)
    {
        if (InPoints[i].StrokeID == InPoints[i - 1].StrokeID)
        {
            Length += FMath::Sqrt(FMath::Pow(InPoints[i].X - InPoints[i - 1].X, 2) + FMath::Pow(InPoints[i].Y - InPoints[i - 1].Y, 2));
        }
    }

    return Length;
}

void UQGesture::TransformCoordinatesToIntegers()
{
    for (FQPoint& Point : Points)
    {
        Point.intX = static_cast<int32>((Point.X + 1.0f) / 2.0f * (MAX_INT_COORDINATES - 1));
        Point.intY = static_cast<int32>((Point.Y + 1.0f) / 2.0f * (MAX_INT_COORDINATES - 1));
    }
}

void UQGesture::ConstructLUT()
{
    // Resize LUT to the appropriate size
    LUT.SetNum(LUT_SIZE);

    for (int32 i = 0; i < LUT_SIZE; ++i)
    {
        // Resize each inner array
        LUT[i].SetSize(LUT_SIZE);
    }

    for (int32 i = 0; i < LUT_SIZE; ++i)
    {
        for (int32 j = 0; j < LUT_SIZE; ++j)
        {
            int32 MinDistance = TNumericLimits<int32>::Max();
            int32 IndexMin = -1;

            for (int32 t = 0; t < Points.Num(); ++t)
            {
                int32 Row = Points[t].intY / LUT_SCALE_FACTOR;
                int32 Col = Points[t].intX / LUT_SCALE_FACTOR;
                int32 Dist = FMath::Square(Row - i) + FMath::Square(Col - j);

                if (Dist < MinDistance)
                {
                    MinDistance = Dist;
                    IndexMin = t;
                }
            }

            // Set the value in the inner array
            LUT[i][j] = IndexMin;
        }
    }
}

int32 UQGesture::GetLUTScaleFactor()
{
    return LUT_SCALE_FACTOR;
}