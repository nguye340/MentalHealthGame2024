// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"

/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Open a text file and read its content
	*
	* @param FilePath				The path of your file
	* @param bOutSucess				If the action was a success or not
	* @param OutInfoMessage			More information about the action's result
	* 
	* @return The string content of your file
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "Read Write File")
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	* Create a text file with your content
	*
	* @param FilePath				The path of your file
	* @param String					The string to want to write in the file
	* @param bOutSucess				If the action was a success or not
	* @param OutInfoMessage			More information about the action's result
	*
	* @return The string content of your file
	*/
	UFUNCTION(BlueprintCallable, Category = "Read Write File")
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);

};
