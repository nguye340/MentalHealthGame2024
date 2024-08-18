// Copyright Team SortaSoda MHGJ 2024


#include "Player/AlmaPlayerState.h"
#include "AbilitySystem/AlmaAttributeSet.h"
#include "AbilitySystem/HanAbilitySystemComponent.h"

AAlmaPlayerState::AAlmaPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UHanAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAlmaAttributeSet>("AttributeSet");
	
	// Rate per second at which updates are sent to clients
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAlmaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
