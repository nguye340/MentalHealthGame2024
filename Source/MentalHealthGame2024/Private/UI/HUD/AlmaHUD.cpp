// Copyright Team SortaSoda MHGJ 2024


#include "UI/HUD/AlmaHUD.h"

#include "UI/Widget/AlmaUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAlmaHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAlmaHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialize, please fill out BP_AlmaCoreHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget CONTROLLER Class uninitialize, please fill out BP_AlmaCoreHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAlmaUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	
	// After making sure that widget controller is set/valid, broadcast attribute values (health, max health, etc.)
	// See more on OverlayWidgetController.h
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

