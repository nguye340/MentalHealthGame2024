// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImportExportDataTable.generated.h"

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UImportExportDataTable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Editor Only - Will not work in packaged build
	* 
	* Import a data table from a json or csv file
	* 
	* @param SourcePath			The path of the source file, for example "C:/Temp/MyJson.json"
	* @param DestinationPath	The path of the imported asset: "/Game/Folder/MyDataTable"
	* @param StructClass		The structure to use for this data table
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information about the action's result
	* 
	* @return The imported data table
	* 

	UFUNCTION(BlueprintCallable, Category = "Import Export Data Table")
	static UDataTable* ImportDataTableFromJsonOrCsv(FString SourcePath, FString DestinationPath, UScriptStruct* StructClass, bool& bOutSuccess, FString& OutInfoMessage);
	*/
	/**
	* Editor Only - Will not work in packaged build
	*
	* Import a data table from a json or csv file
	*
	* @param FilePath			The path of the output file, for example "C:/Temp/MyJson.json"
	* @param DataTable			The datatable to export
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information about the action's result

	UFUNCTION(BlueprintCallable, Category = "Import Export Data Table")
	static void ExportDataTableToJsonOrCsv(FString FilePath, UDataTable* DataTable, bool& bOutSuccess, FString& OutInfoMessage);
	*/
};
