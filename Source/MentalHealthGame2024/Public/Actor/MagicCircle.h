// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

UCLASS()
class MENTALHEALTHGAME2024_API AMagicCircle : public AActor
{
	GENERATED_BODY()
public:	
	AMagicCircle();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> MagicCircleDecal;
	
protected:
	virtual void BeginPlay() override;
};
