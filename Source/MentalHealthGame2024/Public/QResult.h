#pragma once

#include "CoreMinimal.h"
#include "QResult.generated.h"

UCLASS(BlueprintType)
class MENTALHEALTHGAMEJAM2024_API UQResult : public UObject
{
	GENERATED_BODY()

public:
	// Default constructor
	UQResult();

	// Parameterized constructor
	UFUNCTION(BlueprintCallable, Category = "QResult")
		void Initialize(const FString& Name, float Score, float Time);

	// Properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QResult")
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QResult")
		float Score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QResult")
		float Time;
};
