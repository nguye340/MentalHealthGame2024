#pragma once

#include "CoreMinimal.h"
#include "QPoint.h"
#include "QGeometry.generated.h"

UCLASS(BlueprintType)
class YOURPROJECT_API UQGeometry : public UObject
{
    GENERATED_BODY()

public:
    // Computes the Squared Euclidean Distance between two points in 2D
    UFUNCTION(BlueprintCallable, Category = "QGeometry")
        static float SqrEuclideanDistance(const UQPoint* A, const UQPoint* B);

    // Computes the Euclidean Distance between two points in 2D
    UFUNCTION(BlueprintCallable, Category = "QGeometry")
        static float EuclideanDistance(const UQPoint* A, const UQPoint* B);
};
