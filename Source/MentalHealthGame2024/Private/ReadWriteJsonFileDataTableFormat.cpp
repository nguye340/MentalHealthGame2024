// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteJsonFileDataTableFormat.h"
#include "ReadWriteFile.h"
#include "ReadWriteJsonFile.h"
#include "ImportExportDataTable.h"

#include "Engine/DataTable.h" // Engine

TMap<FString, FUSpellStruct> UReadWriteJsonFileDataTableFormat::ReadStructFromJsonFile_DataTableFormat(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Read File
	FString JsonString = UReadWriteFile::ReadStringFromFile(FilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return TMap<FString, FUSpellStruct>();
	}

	// Create data table and tell it which struct it's using
	UDataTable* Table = NewObject<UDataTable>();
	Table->RowStruct = FUSpellStruct::StaticStruct();

	// Populate data table 
	Table->CreateTableFromJSONString(JsonString);

	// Retrieve the rows
	TArray<FName> RowNames = Table->GetRowNames();

	// Populate the return map
	TMap<FString, FUSpellStruct> RowsToStruct;

	for (FName RowName : RowNames)
	{
		FUSpellStruct* Row = Table->FindRow<FUSpellStruct>(RowName, nullptr);

		if (Row != nullptr)
		{
			RowsToStruct.Add(RowName.ToString(), *Row);
		}
	}

	// Return the rows
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Data Table Json Succeeded - '%s'"), *FilePath);
	return RowsToStruct;
}


void UReadWriteJsonFileDataTableFormat::WriteStructToJsonFile_DataTableFormat(FString FilePath, TMap<FString, FUSpellStruct> RowsToStruct, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Convert all rows to string
	TArray<FString> RowNames;
	RowsToStruct.GetKeys(RowNames);

	// Create data table and tell it which struct it's using
	UDataTable* Table = NewObject<UDataTable>();
	Table->RowStruct = FUSpellStruct::StaticStruct();

	// Add all rows to the data table
	for (FString RowName : RowNames)
	{
		Table->AddRow(FName(RowName), RowsToStruct[RowName]);
	}

	// Export to File
	UImportExportDataTable::ExportDataTableToJsonOrCsv(FilePath, Table, bOutSuccess, OutInfoMessage);


}
