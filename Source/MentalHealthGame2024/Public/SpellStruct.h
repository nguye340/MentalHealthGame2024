// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpellStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MENTALHEALTHGAME2024_API FUSpellStruct : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpellID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SpellName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Desc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> GesturePoints;
};
