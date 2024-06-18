// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NestedArrayStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MENTALHEALTHGAME2024_API FNestedArray
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NestedArray")
    TArray<int32> InnerArray;
};