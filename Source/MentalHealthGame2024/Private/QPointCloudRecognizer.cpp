#pragma once

#include "CoreMinimal.h"
#include "QGesture.h"
#include "QPoint.h"
#include "QGeometry.h"
#include "QPointCloudRecognizer.generated.h"

UCLASS(BlueprintType)
class YOURPROJECT_API UQPointCloudRecognizer : public UObject
{
    GENERATED_BODY()

public:
    // Main function of the $P and $P+ recognizer
    UFUNCTION(BlueprintCallable, Category = "PointCloudRecognizer")
        static FString Classify(UQGesture* Candidate, const TArray<UQGesture*>& TrainingSet);

    // Optimization flags
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PointCloudRecognizer")
        static bool UseEarlyAbandoning;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PointCloudRecognizer")
        static bool UseLowerBounding;

private:
    // Greedy cloud matching
    static float GreedyCloudMatch(const TArray<UQPoint*>& Points1, const TArray<UQPoint*>& Points2, float MinSoFar);

    // Cloud distance calculation
    static float CloudDistance(const TArray<UQPoint*>& Points1, const TArray<UQPoint*>& Points2, int32 StartIndex, float MinSoFar);

    // Lower bound calculation
    static TArray<float> ComputeLowerBound(const TArray<UQPoint*>& Points1, const TArray<UQPoint*>& Points2, const TArray<TArray<int32>>& LUT, int32 Step);

    // Helper function for closest point matching
    static float GetClosestPointFromCloud(const UQPoint* P, float Theta, const TArray<UQPoint*>& Cloud, const TArray<float>& ThetaCloud, int32& IndexMin);

    // Compute local shape descriptors
    static TArray<float> ComputeLocalShapeDescriptors(const TArray<UQPoint*>& Points);

    // Compute shortest angle
    static float ShortAngle(const UQPoint* A, const UQPoint* B, const UQPoint* C);
};
