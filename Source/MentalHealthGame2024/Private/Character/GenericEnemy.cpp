// Copyright Team SortaSoda MHGJ 2024


#include "Character/GenericEnemy.h"
#include "AbilitySystem/HanAbilitySystemComponent.h"
#include "AbilitySystem/AlmaAttributeSet.h"

AGenericEnemy::AGenericEnemy()
{
	//GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UHanAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAlmaAttributeSet>("AttributeSet");
}

void AGenericEnemy::BeginPlay()
{
	Super::BeginPlay();
	// check(AbilitySystemComponent); // Check if null
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

}
