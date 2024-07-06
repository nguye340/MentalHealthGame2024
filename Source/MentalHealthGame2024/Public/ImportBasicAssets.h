// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImportBasicAssets.generated.h"

/**
 * 
 */
class UAssetImportTask;
class UFactory;

UCLASS()
class MENTALHEALTHGAME2024_API UImportBasicAssets : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Editor Only - Will not work in packaged build.
	* 
	* Create an import task that you can then process to import any kind of assets
	* 
	* @param SourcePath			The path of the source file: "C:/Temp/MyTexture.png"
	* @param DestinationPath	The Path of the imported asset: "/Game/Folder/MyTexture"
	* @param ExtraOptions		Optional. Some asset types require a special factory to import them
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information about the action's result 
	* 
	* @return The import task
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "Import Basic Assets")
	static UAssetImportTask* CreateImportTask(FString SourcePath, FString DestinationPath, UFactory* ExtraFactory, UObject* ExtraOptions, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	* Editor Only - Will not work in packaged build.
	*
	* Process the import task to import the assets
	*
	* @param ImportTask			The task you want to process
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information about the action's result
	*
	* @return The imported task
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "Import Basic Assets")
	static UObject* ProcessImportTask(UAssetImportTask* ImportTask, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	* Editor Only - Will not work in packaged build.
	*
	* Create and Process the import task 
	* 
	* @param ImportTask			The task you want to process
	* @param bOutSuccess		If the action was a success or not
	* @param OutInfoMessage		More information about the action's result
	*
	* @return The imported task
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "Import Basic Assets")
	static UObject* ImportAsset(FString SourcePath, FString DestinationPath, bool& bOutSuccess, FString& OutInfoMessage);
	
};
