// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "QPoint.h"
#include "QGeometry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MENTALHEALTHGAME2024_API UQGeometry : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "QGeometry")
    static float SqrEuclideanDistance(const FQPoint& A, const FQPoint& B);

    UFUNCTION(BlueprintCallable, Category = "QGeometry")
    static float EuclideanDistance(const FQPoint& A, const FQPoint& B);
};
