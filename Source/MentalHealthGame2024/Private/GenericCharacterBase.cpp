// Copyright Team SortaSoda MHGJ 2024


#include "GenericCharacterBase.h"

// Sets default values
AGenericCharacterBase::AGenericCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenericCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenericCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGenericCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

