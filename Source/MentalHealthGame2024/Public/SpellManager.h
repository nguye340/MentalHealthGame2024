// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "QPoint.h"
#include "QGesture.h"
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
	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static UQGesture* CreateGesture(const TArray<FVector2D>& Vector2DPoints, FString GestureName, bool isPlayerRawInput);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static FString SpellRecognizer(const TArray<FVector2D>& PlayerRawInPoints, TMap<FString, FUSpellStruct> SpellTemplates);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static bool ArePointsValid(const TArray<FVector2D>& Points);

	static void CheckGesturePoints(const UQGesture* Gesture, const FString& GestureName);

    USpellManager();
 //   ~USpellManager();
   
    UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	FString LoadSpellTemplates(TMap<FString, FUSpellStruct> SpellTemplates);

private:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
	USpellManager* SpellManagerInstance;*/
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
    UDataTable* SpellDataTable;
	
	//TMap<FString, FUSpellStruct> SpellTemplates;
//
//    //void LoadSpellData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
	TArray<UQGesture*> GestureTemplates;
};
