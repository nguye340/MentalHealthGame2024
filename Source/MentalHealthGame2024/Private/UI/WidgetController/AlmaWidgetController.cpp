// Copyright Team SortaSoda MHGJ 2024


#include "UI/WidgetController/AlmaWidgetController.h"

void UAlmaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAlmaWidgetController::BroadcastInitialValues()
{
}

void UAlmaWidgetController::BindCallBacksToDependencies()
{
}
