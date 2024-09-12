// Copyright Team SortaSoda MHGJ 2024


#include "Actor/GenericEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystem/AlmaAttributeSet.h>
#include <AbilitySystemBlueprintLibrary.h>

// Sets default values
AGenericEffectActor::AGenericEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	/*
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
		MutableAlmaAttributeSet->SetMana(AlmaAttributeSet->GetMana() - 10.f);
		Destroy();
	}*/
}

/*
void AGenericEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
*/
// Called when the game starts or when spawned
void AGenericEffectActor::BeginPlay()
{
	Super::BeginPlay();
	/*
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGenericEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGenericEffectActor::EndOverlap);*/
}

void AGenericEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{		
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) 
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
		/*IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);
	if (ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();

	}
*/
}

void AGenericEffectActor::ApplyMultipleEffectsToTarget(
	AActor* TargetActor, 
	TMap<TSubclassOf<UGameplayEffect>, EEffectApplicationPolicy> EffectClassesAndPoliciesApplication)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (TTuple<TSubclassOf<UGameplayEffect>, EEffectApplicationPolicy> EffectClassAndPolicyApplication : EffectClassesAndPoliciesApplication)
	{
		check(EffectClassAndPolicyApplication.Key);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectClassAndPolicyApplication.Key, 1.f, EffectContextHandle);
		FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void AGenericEffectActor::RemoveMultipleEffectsToTarget(AActor* TargetActor, TMap<TSubclassOf<UGameplayEffect>, EEffectRemovalPolicy> EffectClassesAndPoliciesRemoval)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (TTuple<TSubclassOf<UGameplayEffect>, EEffectRemovalPolicy> EffectClassAndPolicyRemoval : EffectClassesAndPoliciesRemoval)
	{
		check(EffectClassAndPolicyRemoval.Key);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectClassAndPolicyRemoval.Key, 1.f, EffectContextHandle);
		FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if (bIsInfinite && EffectClassAndPolicyRemoval.Value == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}
}

void AGenericEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) 
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	for (TTuple<TSubclassOf<UGameplayEffect>, EEffectApplicationPolicy> EffectClassAndPolicyApplication : ApplyInfiniteEffectClassesAndPolicies)
	{
		if (EffectClassAndPolicyApplication.Value == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectClassAndPolicyApplication.Key);
		}

	}
}

void AGenericEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	for (TTuple<TSubclassOf<UGameplayEffect>, EEffectApplicationPolicy> EffectClassAndPolicyApplication : ApplyInfiniteEffectClassesAndPolicies)
	{
		if (EffectClassAndPolicyApplication.Value == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectClassAndPolicyApplication.Key);
		}
	}
	/* Below is for single infinite effect removal policy - more than one Infinite effect use TMap with RemoveInfiniteEffectClassesAndPolicies */
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetActor)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);// 1 to remove 1 stack at a time, default -1 remove all stack upon exist 1 source
				HandlesToRemove.Add(HandlePair.Key);
			}		
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
	
	for (TTuple<TSubclassOf<UGameplayEffect>, EEffectRemovalPolicy> EffectClassAndPolicyRemoval : RemoveInfiniteEffectClassesAndPolicies)
	{
		if (EffectClassAndPolicyRemoval.Value == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if (!IsValid(TargetActor)) return;

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);// 1 to remove 1 stack at a time, default -1 remove all stack upon exist 1 source
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}

		}

	}
}

