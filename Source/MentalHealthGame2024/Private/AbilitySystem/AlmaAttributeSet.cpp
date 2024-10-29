// Copyright Team SortaSoda MHGJ 2024


#include "AbilitySystem/AlmaAttributeSet.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"

UAlmaAttributeSet::UAlmaAttributeSet()
{
	InitHealth(20.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);

}

void UAlmaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAlmaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAlmaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAlmaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAlmaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAlmaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}
void UAlmaAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProps) const
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Health from GetHealth(): %f"), GetHealth());
		UE_LOG(LogTemp, Warning, TEXT("Magnitude: %f"), Data.EvaluatedData.Magnitude);

	}

	// Source = the causer/trigger of the effect, target = target of the effect (owner of this AttributeSet)
	EffectProps.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProps.SourceASC = EffectProps.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProps.SourceASC) && EffectProps.SourceASC->AbilityActorInfo.IsValid() && EffectProps.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProps.SourceAvatarActor = EffectProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProps.SourceController = EffectProps.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (EffectProps.SourceController == nullptr && EffectProps.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProps.SourceAvatarActor))
			{
				EffectProps.SourceController = Pawn->GetController();
			}
		}
		if (EffectProps.SourceController)
		{
			EffectProps.SourceCharacter = Cast<ACharacter>(EffectProps.SourceController->GetPawn());
		}

	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.Get())
	{
		EffectProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProps.TargetCharacter = Cast<ACharacter>(EffectProps.TargetAvatarActor);
		EffectProps.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProps.TargetAvatarActor);
	}
}
void UAlmaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProps;
	SetEffectProperties(Data, EffectProps);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UAlmaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlmaAttributeSet, Health, OldHealth)
}

void UAlmaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlmaAttributeSet, MaxHealth, OldMaxHealth)
}

void UAlmaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlmaAttributeSet, Mana, OldMana)
}

void UAlmaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlmaAttributeSet, MaxMana, OldMaxMana)
}


