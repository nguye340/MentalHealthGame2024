// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportBasicAssets.h"
#include "AssetImportTask.h" //UnrealEd (Editor Only)
#include "AssetToolsModule.h" // AssetTools (Editor Only)

UAssetImportTask* UImportBasicAssets::CreateImportTask(FString SourcePath, FString DestinationPath, UFactory* ExtraFactory, UObject* ExtraOptions, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Create task object
	UAssetImportTask* RetTask = NewObject<UAssetImportTask>();

	// Make sure the object was created properly
	if (RetTask == nullptr) 
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Import Task Failed - Was not able to create the import task object. That shouldn't really happen. - '%s'"), *SourcePath);
		return nullptr;
	}

	// Set path information
	RetTask->Filename = SourcePath;
	RetTask->DestinationPath = FPaths::GetPath(DestinationPath);
	RetTask->DestinationName = FPaths::GetCleanFilename(DestinationPath);

	// Set basic options
	RetTask->bSave = false;
	RetTask->bAutomated = true;
	RetTask->bAsync = false;
	RetTask->bReplaceExisting = true;
	RetTask->bReplaceExistingSettings = false;
	
	// Optional extra factory and options
	RetTask->Factory = ExtraFactory;
	RetTask->Options = ExtraOptions;

	// Return the task
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Create Import Task Succeeded - '%s'"), *SourcePath);
	return RetTask;

}

UObject* UImportBasicAssets::ProcessImportTask(UAssetImportTask* ImportTask, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Make sure the task is valid. We don't want to try to import something that's invalid
	if (ImportTask == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed - The task was invalid. Cannot process."));
		return nullptr;
	}

	// Get the AssetTools module
	FAssetToolsModule* AssetTools = FModuleManager::LoadModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetTools == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed - The AssetTools module is invalid. - '%s'"), *ImportTask->Filename);
		return nullptr;
	}

	// Import the asset
	AssetTools->Get().ImportAssetTasks({ ImportTask });

	// Check if anything was imported during the process
	if (ImportTask->GetObjects().Num() == 0) 
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed - Nothing was imported. Is your file valid? Is the asset type supported? - '%s'"), *ImportTask->Filename);
		return nullptr;
	}

	// Because some import tasks actually create multiple assets (e.g. SkeletalMesh), we manually get the right asset
	UObject* ImportedAsset = StaticLoadObject(UObject::StaticClass(), nullptr, *FPaths::Combine(ImportTask->DestinationPath, ImportTask->DestinationName));
	
	// Return the task
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Process Import Task Succeeded - '%s'"), *ImportTask->Filename);
	return ImportedAsset;
}

UObject* UImportBasicAssets::ImportAsset(FString SourcePath, FString DestinationPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Create the import task
	UAssetImportTask* Task = CreateImportTask(SourcePath, DestinationPath, nullptr, nullptr, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{	
		return nullptr;
	}

	// Import the asset
	UObject* RetAsset = ProcessImportTask(Task, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess) 
	{
		return nullptr;
	}

	// Return the imported asset
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Import Asset Succeeded - '%s'"), *DestinationPath);
	return RetAsset;
}