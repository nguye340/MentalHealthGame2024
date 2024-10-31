// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HanAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectsAssetTags, const FGameplayTagContainer&  /*AssetTags*/);

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UHanAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FEffectsAssetTags EffectsAssetTags;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec&	EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
