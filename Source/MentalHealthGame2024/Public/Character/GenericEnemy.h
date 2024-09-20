// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GenericCharacterBase.h"
#include "GenericEnemy.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;

UCLASS(Abstract)
class MENTALHEALTHGAME2024_API AGenericEnemy : public AGenericCharacterBase
{
	GENERATED_BODY()

public:
	AGenericEnemy();
	

	/** Enemy Interface Below */
	/** End Enemy Interface */

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
