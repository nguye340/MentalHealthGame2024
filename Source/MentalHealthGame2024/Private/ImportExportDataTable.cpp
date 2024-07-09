// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportExportDataTable.h"
#include "ReadWriteFile.h"
#include "ReadWriteJsonFile.h"
/*
#include "ImportBasicAssets.h"

#include "Factories/ReimportDataTableFactory.h" // UnrealEd (Editor Only)

UDataTable* UImportExportDataTable::ImportDataTableFromJsonOrCsv(FString SourcePath, FString DestinationPath, UScriptStruct* StructClass, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Create factory to import a Data Table
	UReimportDataTableFactory* DtFactory = NewObject<UReimportDataTableFactory>();
	DtFactory->AutomatedImportSettings.ImportType = ECSVImportType::ECSV_DataTable;
	DtFactory->AutomatedImportSettings.ImportRowStruct = StructClass;

	// Create import task
	UAssetImportTask* ImportTask = UImportBasicAssets::CreateImportTask(SourcePath, DestinationPath, DtFactory, nullptr, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	// Import asset
	UObject* ImportedAsset = UImportBasicAssets::ProcessImportTask(ImportTask, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}
	
	// Return imported asset
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Import Data Table Succeeded - '%s'"), *DestinationPath);
	return Cast<UDataTable>(ImportedAsset);
}
*/

void UImportExportDataTable::ExportDataTableToJsonOrCsv(FString FilePath, UDataTable* DataTable, bool& bOutSuccess, FString& OutInfoMessage) 
{
	// Check if DataTable is valid
	if (DataTable == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Export Data Table to Json Or Csv Failed - Data table is null ptr. FilePathL '%s'"), *FilePath);
		return;
	}

	// Convert table to string
	FString TableString;

	if (FilePath.Contains(".csv"))
	{
		TableString = DataTable->GetTableAsCSV();
	}
	else
	{
		TableString = DataTable->GetTableAsJSON();
	}

	// Write string to file
	UReadWriteFile::WriteStringToFile(FilePath, TableString, bOutSuccess, OutInfoMessage);

}
