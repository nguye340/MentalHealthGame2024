// Copyright Team SortaSoda MHGJ 2024


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AlmaAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAlmaAttributeSet* AlmaAttributeSet = CastChecked<UAlmaAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AlmaAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AlmaAttributeSet->GetMaxHealth());

}
