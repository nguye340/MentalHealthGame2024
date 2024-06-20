// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QPoint.h"
#include "QGesture.h"
#include "QGeometry.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPointCloudRecognizer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MENTALHEALTHGAME2024_API UQPointCloudRecognizer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "QRecognizer")
    static FString Classify(const UQGesture* Candidate, const TArray<UQGesture*>& TemplateSet);

private:
    static bool bUseEarlyAbandoning;
    static bool bUseLowerBounding;

    static float GreedyCloudMatch(const UQGesture* Gesture1, const UQGesture* Gesture2, float MinSoFar);
    static TArray<float> ComputeLowerBound(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, const TArray<FNestedArray>& LUT, int32 Step);
    static float CloudDistance(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, int32 StartIndex, float MinSoFar);
};

