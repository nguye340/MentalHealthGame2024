// Copyright Team SortaSoda MHGJ 2024


#include "GenericCharacterBase.h"

// Sets default values
AGenericCharacterBase::AGenericCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AGenericCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AGenericCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


