// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTableCsvJsonParser.generated.h"

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UDataTableCsvJsonParser : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()


public:
    UFUNCTION(BlueprintCallable, Category = "DataTable")
    static FString GetTableAsCSV(const UDataTable* DataTable);

    UFUNCTION(BlueprintCallable, Category = "DataTable")
    static FString GetTableAsJSON(const UDataTable* DataTable);
};
