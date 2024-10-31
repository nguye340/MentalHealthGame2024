// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AlmaGameplayAbility.h"
#include "AlmaProjectileSpell.generated.h"

class AAlmaProjectile;
/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UAlmaProjectileSpell : public UAlmaGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAlmaProjectile> ProjectileClass;
};
