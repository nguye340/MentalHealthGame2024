// Copyright Team SortaSoda MHGJ 2024


#include "UI/Widget/AlmaUserWidget.h"

void UAlmaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}


