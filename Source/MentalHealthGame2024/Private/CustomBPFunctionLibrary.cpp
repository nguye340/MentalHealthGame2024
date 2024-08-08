// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBPFunctionLibrary.h"

void UCustomBPFunctionLibrary::TriggerButtonClick(UButton* Button)
{
	if (!IsValid(Button))
	{
		return;
	}
	Button->OnClicked.Broadcast();
}

void UCustomBPFunctionLibrary::TriggerButtonPress(UButton* Button)
{
	if (!IsValid(Button))
	{
		return;
	}
	Button->OnPressed.Broadcast();
}

void UCustomBPFunctionLibrary::TriggerButtonReleased(UButton* Button)
{
	if (!IsValid(Button))
	{
		return;
	}
	Button->OnReleased.Broadcast();
}

void UCustomBPFunctionLibrary::TriggerButtonHovered(UButton* Button)
{
	if (!IsValid(Button))
	{
		return;
	}
	Button->OnHovered.Broadcast();
}

void UCustomBPFunctionLibrary::TriggerButtonUnhovered(UButton* Button)
{
	if (!IsValid(Button))
	{
		return;
	}
	Button->OnUnhovered.Broadcast();
}