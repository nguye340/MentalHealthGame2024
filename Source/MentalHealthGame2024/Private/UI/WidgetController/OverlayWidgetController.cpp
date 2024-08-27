// Copyright Team SortaSoda MHGJ 2024


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AlmaAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAlmaAttributeSet* AlmaAttributeSet = CastChecked<UAlmaAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AlmaAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AlmaAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AlmaAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AlmaAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	const UAlmaAttributeSet* AlmaAttributeSet = CastChecked<UAlmaAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
