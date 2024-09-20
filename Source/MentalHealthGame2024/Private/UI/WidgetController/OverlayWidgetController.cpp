// Copyright Team SortaSoda MHGJ 2024


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AlmaAttributeSet.h"
#include "AbilitySystem/HanAbilitySystemComponent.h"


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

	Cast<UHanAbilitySystemComponent>(AbilitySystemComponent)->EffectsAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
			}
		}	
	);
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
