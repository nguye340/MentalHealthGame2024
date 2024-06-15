#pragma once

#include "CoreMinimal.h"
#include "QPoint.h"
#include "QGesture.generated.h"

UCLASS(BlueprintType)
class YOURPROJECT_API UQGesture : public UObject
{
    GENERATED_BODY()

public:
    // Gesture points (normalized)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QGesture")
        TArray<UQPoint*> Points;

    // Gesture points (not normalized, as captured from the input device)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QGesture")
        TArray<UQPoint*> PointsRaw;

    // Gesture class
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QGesture")
        FString Name;

    // Lookup table
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QGesture")
        TArray<TArray<int32>> LUT;

    static const int32 SAMPLING_RESOLUTION;
    static const int32 MAX_INT_COORDINATES;
    static const int32 LUT_SIZE;
    static const int32 LUT_SCALE_FACTOR;

    // Constructor
    UFUNCTION(BlueprintCallable, Category = "QGesture")
        void Initialize(const TArray<UQPoint*>& InPoints, const FString& GestureName = "", bool ComputeLUT = true);

private:
    void Normalize(bool ComputeLUT);

    TArray<UQPoint*> Resample(const TArray<UQPoint*>& Points, int32 N);
    TArray<UQPoint*> Scale(const TArray<UQPoint*>& Points);
    TArray<UQPoint*> TranslateTo(const TArray<UQPoint*>& Points, UQPoint* P);
    UQPoint* Centroid(const TArray<UQPoint*>& Points);
    float PathLength(const TArray<UQPoint*>& Points);
    void TransformCoordinatesToIntegers();
    void ConstructLUT();
};
