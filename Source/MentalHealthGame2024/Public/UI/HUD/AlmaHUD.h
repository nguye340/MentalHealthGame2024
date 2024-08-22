// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlmaHUD.generated.h"

class UOverlayWidgetController;
class UAlmaUserWidget;
class FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API AAlmaHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAlmaUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAlmaUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY()
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
