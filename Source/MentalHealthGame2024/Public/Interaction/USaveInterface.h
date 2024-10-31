// Copyright Team SortaSoda MHGJ 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "USaveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUSaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MENTALHEALTHGAME2024_API IUSaveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ShouldLoadTransform();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LoadActor();
};
