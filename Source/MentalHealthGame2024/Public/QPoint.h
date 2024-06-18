// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QPoint.generated.h"

/**
 * 
 
UCLASS()
class MENTALHEALTHGAME2024_API UQPoint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
*/
USTRUCT(BlueprintType)
struct FQPoint
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPoint")
    float X;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPoint")
    float Y;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPoint")
    int32 StrokeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPoint")
    int32 intX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPoint")
    int32 intY;

    FQPoint() : X(0), Y(0), StrokeID(0), intX(0), intY(0) {}

    FQPoint(float InX, float InY, int32 InStrokeID)
        : X(InX), Y(InY), StrokeID(InStrokeID), intX(0), intY(0) {}
};
