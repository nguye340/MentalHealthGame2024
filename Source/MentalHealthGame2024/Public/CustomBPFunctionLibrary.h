// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomBPFunctionLibrary.generated.h"


UCLASS()
class MENTALHEALTHGAME2024_API UCustomBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Basics | Utils", Meta = (WorldContext = "Context", ToolTip = "Triggers a 'OnClicked' event on a button"))
	static void TriggerButtonClick(UButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Basics | UMG", Meta = (WorldContext = "Context", ToolTip = "Triggers a 'OnPressed' event on a button"))
	static void TriggerButtonPress(UButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Basics | UMG", Meta = (WorldContext = "Context", ToolTip = "Triggers a 'OnReleased' event on a button"))
	static void TriggerButtonReleased(UButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Basics | UMG", Meta = (WorldContext = "Context", ToolTip = "Triggers a 'OnHovered' event on a button"))
	static void TriggerButtonHovered(UButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Basics | UMG", Meta = (WorldContext = "Context", ToolTip = "Triggers a 'OnUnhovered' event on a button"))
	static void TriggerButtonUnhovered(UButton* Button);
};
