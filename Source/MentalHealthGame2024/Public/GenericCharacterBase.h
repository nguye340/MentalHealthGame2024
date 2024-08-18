// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

#include "GenericCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class MENTALHEALTHGAME2024_API AGenericCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenericCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY() 
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
