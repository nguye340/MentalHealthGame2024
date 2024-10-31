// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AlmaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAlmaInputConfig;
class UHanAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API AAlmaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAlmaPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AlmaContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAlmaInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UHanAbilitySystemComponent> HanAbilitySystemComponent;
	UHanAbilitySystemComponent* GetASC();
};
