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
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	); 
	//.AddUObject(this, &UOverlayWidgetController::HealthChanged);

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	); 
	
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	); 
	
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AlmaAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	); 
	
	Cast<UHanAbilitySystemComponent>(AbilitySystemComponent)->EffectsAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// For example, say that Tag = Message.HealthPotion
				// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				// FGameplayTag::RequestGameplayTag(FName("TagNameHere")) - If tag exists in proj or one of our config files, can get tag with static func
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{
					// Uncomment to check what specific MessageTag get parsed in
					// const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
					// GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
					
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}	
	);
}
/*
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
*/