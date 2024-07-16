#include "QGesture.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/DateTime.h"

UQGesture::UQGesture()
{
}

void UQGesture::Initialize(const TArray<FQPoint>& InPoints, const FString& GestureName)
{
    PointsRaw = InPoints;
    Normalize();
    Name = GestureName;
}

TArray<FQPoint> UQGesture::Convert(const TArray<FVector2D>& Vector2DPoints, bool bIsPlayerRawInput)
{
    TArray<FQPoint> NewPoints;
    int32 StrokeID = 0;

    if (!bIsPlayerRawInput)
    {
        // Generate a random non-zero StrokeID using current time and a random seed
        do
        {
            int64 CurrentTime = FDateTime::Now().GetTicks();
            int32 RandomSeed = FMath::Rand();
            StrokeID = CurrentTime ^ RandomSeed;
        } while (StrokeID == 0);
    }

    //Generate random hash id everytime a new gesture i.e new array of points is created
    /*Insert random hash index*/
    for (int32 Index = 0; Index < Vector2DPoints.Num(); ++Index)
    {
        const FVector2D& Point = Vector2DPoints[Index];
        
        // Just in case - If player input, strokeID = 0, if not player input - strokeID is randomized/unique (for each template gesture)
        NewPoints.Add(FQPoint(Point.X, Point.Y, bIsPlayerRawInput ? 0 : StrokeID));
    }

    return NewPoints;
}

void UQGesture::Normalize(bool bComputeLUT)
{
     Points = Resample(PointsRaw, SAMPLING_RESOLUTION);
     for (int32 i = 0; i < Points.Num(); i++)
     {
        const FQPoint& Point = Points[i];
        if (Point.intX < 0 || Point.intY < 0)
        {
            UE_LOG(LogTemp, Error, TEXT("QGESTURE: Invalid point found at index %d for gesture - intX: %d, intY: %d, Point.StrokeID: %d, Points.Num(): %d"), i, Point.intX, Point.intY, Point.StrokeID, Points.Num());
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("QGESTURE: Point at index %d for gesture is valid - intX: %d, intY: %d, Point.StrokeID: %d, Points.Num(): %d"), i, Point.intX, Point.intY, Point.StrokeID, Points.Num());
        }
    }
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
    // Check if the input points array is empty
    if (InPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("QGESTURE: Resample: InPoints is empty"));
        return TArray<FQPoint>();
    }
    else UE_LOG(LogTemp, Warning, TEXT("QGESTURE: InPoints: %d, N: %d"), InPoints.Num(), N);

    // Initialize the new points array and add the first point from InPoints
    TArray<FQPoint> NewPoints;
    NewPoints.Add(InPoints[0]);
    int32 NumPoints = 1;

    float I = PathLength(InPoints) / (N - 1);
    UE_LOG(LogTemp, Error, TEXT("QGESTURE: PathLength: %f"), I);
    float D = 0;

    for (int32 i = 1; i < InPoints.Num(); i++)
    {
        UE_LOG(LogTemp, Error, TEXT("InPoints[i].StrokeID: %d, InPoints[i - 1].StrokeID: %d"), InPoints[i].StrokeID, InPoints[i - 1].StrokeID);
        
        // Check if the stroke ID of the current point matches the previous point
        if (InPoints[i].StrokeID == InPoints[i - 1].StrokeID)
        {
            float d = FMath::Sqrt(FMath::Pow(InPoints[i].X - InPoints[i - 1].X, 2) + FMath::Pow(InPoints[i].Y - InPoints[i - 1].Y, 2));
            UE_LOG(LogTemp, Error, TEXT("QGESTURE: distance between 2 consecutive pointRes: %f"), d);

            if (D + d >= I)
            {
                FQPoint FirstPoint = InPoints[i - 1];
                while (D + d >= I)
                {
                    // add interpolated point
                    float t = FMath::Clamp((I - D) / d, 0.0f, 1.0f);
                    
                    if (FMath::IsNaN(t)) t = 0.5f;
                    
                    NewPoints.Add(FQPoint(
                        (1.0f - t) * FirstPoint.X + t * InPoints[i].X,
                        (1.0f - t) * FirstPoint.Y + t * InPoints[i].Y,
                        InPoints[i].StrokeID
                    ));
                    
                    UE_LOG(LogTemp, Error, TEXT("Resample: Added interpolated point at index %d - X: %f, Y: %f"), NewPoints.Num() - 1, NewPoints.Last().X, NewPoints.Last().Y);

                    // update partial length
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

    // Add the last point if the number of points is one less than N
    // sometimes we fall a rounding-error short of adding the last point, so add it if so
    if (NumPoints == N - 1)
        NewPoints.Add(FQPoint(InPoints[InPoints.Num() - 1].X, InPoints[InPoints.Num() - 1].Y, InPoints[InPoints.Num() - 1].StrokeID));
        //NewPoints.Add(InPoints.Last());

    UE_LOG(LogTemp, Error, TEXT("Resample: Final NewPoints.Num(): %d"), NewPoints.Num());

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