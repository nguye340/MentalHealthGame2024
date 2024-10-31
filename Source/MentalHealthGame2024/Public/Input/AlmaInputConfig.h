// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AlmaInputConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAlmaInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UAlmaInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAlmaInputAction> AbilityInputActions;
};

