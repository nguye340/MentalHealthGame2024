// Copyright Team SortaSoda MHGJ 2024


#include "AbilitySystem/HanAbilitySystemComponent.h"

void UHanAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UHanAbilitySystemComponent::EffectApplied);
}

void UHanAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                               const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("EffectApplied!"));
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectsAssetTags.Broadcast(TagContainer);
}
