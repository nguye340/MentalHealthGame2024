// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteJsonFile.generated.h"

class FJsonObject;
/**
 * 
 */
UCLASS()
class MENTALHEALTHGAME2024_API UReadWriteJsonFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	* Open a json file, read its content and dump it into a structure
	* 
	* @param JsonFilePath		The path of your json file
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information aout the action's result
	*
	* @return The structure content of your json file
*/	
	UFUNCTION(BlueprintCallable, Category = "Read Write Json")
	static FUSpellStruct ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	* Open a json file, read its content and dump it into a structure
	*
	* @param JsonFilePath		The path of your json file
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information aout the action's result
	*
	* @return The structure content of your json file
*/
	UFUNCTION(BlueprintCallable, Category = "Read Write Json")
	static void WriteStructToJsonFile(FString JsonFilePath, FUSpellStruct Struct, bool& bOutSuccess, FString& OutInfoMessage);

	/*
	* Open a json file, read its content and convert it to a JsonObject
	* 
	* @param JsonFilePath		The path of your json file:"C:/Temp/MyJson.json
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information aout the action's result
	* 
	* @return The JsonObject content of your json file
	*/
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
	/*
	* Open a json file, read its content and convert it to a JsonObject
	*
	* @param JsonFilePath		The path of your json file:"C:/Temp/MyJson.json
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information aout the action's result
	*
	* @return The JsonObject content of your json file
	*/
	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage);

};
