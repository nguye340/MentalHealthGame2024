// Copyright Team SortaSoda MHGJ 2024


#include "Character/AlmaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Player/AlmaPlayerState.h"
#include <UI/HUD/AlmaHUD.h>
#include <Player/AlmaPlayerController.h>

AAlmaCharacter::AAlmaCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAlmaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init ability actor info for the Server
	InitAbilityActorInfo();

}

void AAlmaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAlmaCharacter::InitAbilityActorInfo()
{
	AAlmaPlayerState* AlmaPlayerState = GetPlayerState<AAlmaPlayerState>();
	check(AlmaPlayerState);
	AlmaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AlmaPlayerState, this);
	AbilitySystemComponent = AlmaPlayerState->GetAbilitySystemComponent();
	AttributeSet = AlmaPlayerState->GetAtrributeSet();

	if (AAlmaPlayerController* AlmaPlayerController = Cast<AAlmaPlayerController>(GetController()))
	{
		if (AAlmaHUD* AlmaHUD = Cast<AAlmaHUD>(AlmaPlayerController->GetHUD()))
		{
			AlmaHUD->InitOverlay(AlmaPlayerState->GetPlayerController(), AlmaPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}


		
}
