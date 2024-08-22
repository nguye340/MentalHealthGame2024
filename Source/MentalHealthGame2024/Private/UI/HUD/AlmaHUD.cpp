// Copyright Team SortaSoda MHGJ 2024


#include "UI/HUD/AlmaHUD.h"

#include "UI/Widget/AlmaUserWidget.h"
#include "UI/WidgetController/OverlayWidget"

UOverlayWidgetController* AAlmaHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)\
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, )
	}
	return OverlayWidgetController;
}

void AAlmaHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
