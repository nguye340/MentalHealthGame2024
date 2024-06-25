// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "SpellStruct.h"
#include "SpellManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MENTALHEALTHGAME2024_API USpellManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
   
    USpellManager();
    ~USpellManager();
    
    UFUNCTION(BlueprintCallable, Category = "Spells")
    void LoadSpells();

    UFUNCTION(BlueprintCallable, Category = "Spells")
    void AddPlayerGestureToFirstRow(const TArray<FVector2D>& PlayerGesture);

//private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
    UDataTable* SpellDataTable;

    TMap<FName, FUSpellStruct> Spells;

    //void LoadSpellData();

};
