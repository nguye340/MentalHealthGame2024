// Copyright Team SortaSoda MHGJ 2024


#include "Player/AlmaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/HanAbilitySystemComponent.h"
#include "Input/AlmaInputComponent.h"
#include "EnhancedInputComponent.h"


AAlmaPlayerController::AAlmaPlayerController()
{
	bReplicates = true;
}

void AAlmaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AlmaContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AlmaContext, 0);

	};

	/** Uncomment to show mouse cursor
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	*/
}

void AAlmaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAlmaPlayerController::Move);
	*/
	UAlmaInputComponent* AlmaInputComponent = CastChecked<UAlmaInputComponent>(InputComponent);
	AlmaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAlmaPlayerController::Move);
	AlmaInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAlmaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);

	}
}

void AAlmaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}
void AAlmaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}
void AAlmaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UHanAbilitySystemComponent* AAlmaPlayerController::GetASC()
{
	if (HanAbilitySystemComponent == nullptr)
	{
		HanAbilitySystemComponent = Cast<UHanAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return HanAbilitySystemComponent;
}