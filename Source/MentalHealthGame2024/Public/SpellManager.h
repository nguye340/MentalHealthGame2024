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
class MENTALHEALTHGAME2024_API USpellManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static UQGesture* CreateGesture(const TArray<FVector2D>& Vector2DPoints, FString GestureName, bool isPlayerRawInput);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static FString SpellRecognizer(const TArray<FVector2D>& PlayerRawInPoints, TMap<FString, FUSpellStruct> SpellTemplates);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static FString SpellRecognizer_Optimized(const TArray<FVector2D>& PlayerRawInPoints, TArray<UQGesture*> SpellTemplates);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static bool ArePointsValid(const TArray<FVector2D>& Points);

	static void CheckGesturePoints(const UQGesture* Gesture, const FString& GestureName);

	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static void ClearGestureTemplates(TArray<UQGesture*> GestureTemplates);

    USpellManager();
 //   ~USpellManager();
   

	// Function to get pre-made templates of spells
	//const TArray<UQGesture*>& GetTemplates() const { return PremadeTemplates; }

private:
	UFUNCTION(BlueprintCallable, Category = "Spell Manager")
	static TArray<UQGesture*> LoadSpellTemplates(TMap<FString, FUSpellStruct> SpellTemplates, TArray<UQGesture*> PremadeTemplates);/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
	USpellManager* SpellManagerInstance;*/
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
    UDataTable* SpellDataTable;
	
	//TMap<FString, FUSpellStruct> SpellTemplates;
//
//    //void LoadSpellData();
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells", meta = (AllowPrivateAccess = "true"))
	TArray<UQGesture*> PremadeTemplates;
	*/
	
};
