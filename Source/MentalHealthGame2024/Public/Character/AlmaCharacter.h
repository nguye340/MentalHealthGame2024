// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GenericCharacterBase.h"
#include "GameFramework/PlayerState.h"

#include "AlmaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API AAlmaCharacter : public AGenericCharacterBase
{
	GENERATED_BODY()
	
public:
	AAlmaCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState();

private:
	void InitAbilityActorInfo();
};
