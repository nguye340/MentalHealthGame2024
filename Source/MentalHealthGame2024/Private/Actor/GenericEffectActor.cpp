// Copyright Team SortaSoda MHGJ 2024


#include "Actor/GenericEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystem/AlmaAttributeSet.h>

// Sets default values
AGenericEffectActor::AGenericEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AGenericEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!

	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAlmaAttributeSet* AlmaAttributeSet = Cast<UAlmaAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAlmaAttributeSet::StaticClass()));
		UAlmaAttributeSet* MutableAlmaAttributeSet = const_cast<UAlmaAttributeSet*>(AlmaAttributeSet);
		MutableAlmaAttributeSet->SetHealth(AlmaAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AGenericEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void AGenericEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGenericEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGenericEffectActor::EndOverlap);
}

