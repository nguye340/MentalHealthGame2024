#pragma once

#include "CoreMinimal.h"
#include "QPoint.h"
#include "QPointCloud.generated.h"

UCLASS(BlueprintType)
class MENTALHEALTHGAMEJAM2024_API UQPointCloud : public UObject
{
	GENERATED_BODY()

public:
	// Default constructor
	UQPointCloud();

	// Parameterized constructor
	UFUNCTION(BlueprintCallable, Category = "QPointCloud")
		void Initialize(FString Name, const TArray<UQPoint*>& Points);

	// Properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPointCloud")
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPointCloud")
		TArray<UQPoint*> Points;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPointCloud")
		TArray<int32> LUT; // Lookup table

private:
	// Utility functions to manipulate points
	TArray<UQPoint*> Resample(const TArray<UQPoint*>& InputPoints, int32 NumPoints);
	TArray<UQPoint*> Scale(const TArray<UQPoint*>& InputPoints);
	TArray<UQPoint*> TranslateTo(const TArray<UQPoint*>& InputPoints, const FVector& Origin);
	TArray<UQPoint*> MakeIntCoords(const TArray<UQPoint*>& InputPoints);
	TArray<int32> ComputeLUT(const TArray<UQPoint*>& InputPoints);

	// Constants
	static const int32 NumPoints = 64;
	static const FVector Origin;
};
