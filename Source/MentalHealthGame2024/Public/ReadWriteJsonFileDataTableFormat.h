// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteJsonFileDataTableFormat.generated.h"

struct FUSpellStruct;

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UReadWriteJsonFileDataTableFormat : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public: 
	/**
	* Ed only - no package build
	* 
	* Read a series of struct based on a json file formatted like a data table
	* 
	* @param FilePath		The path of the source file
	* @param bOutSuccess	If the action was a success or not
	* @param OutInfoMessage	More info about the action's result
	* 
	* @return The structs
	*/
	UFUNCTION(BlueprintCallable, Category = "Read Write Data Table JSON")
	static TMap<FString, FUSpellStruct> ReadStructFromJsonFile_DataTableFormat(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	* Ed only - no package build
	*
	* Write a series of struct to a json file, will be formatted like a data table
	*
	* @param FilePath		The path of the source file
	* @param RowsToStruct	The structs to write in the json
	* @param bOutSuccess	If the action was a success or not
	* @param OutInfoMessage	More info about the action's result
	*
	* @return The structs
	*/
	UFUNCTION(BlueprintCallable, Category = "Read Write Data Table JSON")
	static void WriteStructToJsonFile_DataTableFormat(FString FilePath, TMap<FString, FUSpellStruct> RowsToStruct, bool& bOutSuccess, FString& OutInfoMessage);


};
