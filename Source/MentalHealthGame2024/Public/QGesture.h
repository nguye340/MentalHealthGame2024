// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPoint.h"
#include "NestedArrayStruct.h"
#include "QGesture.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class UQGesture : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QGesture")
    TArray<FQPoint> Points;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QGesture")
    TArray<FQPoint> PointsRaw;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QGesture")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QGesture")
    TArray<FNestedArray> LUT;

    UQGesture();

    UQGesture(const TArray<FQPoint>& InPoints, const FString& GestureName = "");

    void Normalize(bool bComputeLUT = true);

private:
    const int32 SAMPLING_RESOLUTION = 64;
    const int32 MAX_INT_COORDINATES = 1024;
    const int32 LUT_SIZE = 64;
    const int32 LUT_SCALE_FACTOR = MAX_INT_COORDINATES / LUT_SIZE;

    TArray<FQPoint> Scale(const TArray<FQPoint>& InPoints);
    TArray<FQPoint> TranslateTo(const TArray<FQPoint>& InPoints, const FQPoint& P);
    FQPoint Centroid(const TArray<FQPoint>& InPoints);
    TArray<FQPoint> Resample(const TArray<FQPoint>& InPoints, int32 N);
    float PathLength(const TArray<FQPoint>& InPoints);
    void TransformCoordinatesToIntegers();
    void ConstructLUT();
};
