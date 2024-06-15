#pragma once

#include "CoreMinimal.h"
#include "QPoint.generated.h"

UCLASS(BlueprintType)
class YOURPROJECT_API UQPoint : public UObject
{
    GENERATED_BODY()

public:
    // Point coordinates
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPoint")
        float X;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPoint")
        float Y;

    // Stroke index
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPoint")
        int32 StrokeID;

    // Integer coordinates for LUT indexing
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPoint")
        int32 IntX;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPoint")
        int32 IntY;

    // Constructor
    UFUNCTION(BlueprintCallable, Category = "QPoint")
        void Initialize(float InX, float InY, int32 InStrokeID);

    // Default constructor
    UQPoint();
};
