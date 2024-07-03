// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteJsonFile.h"
#include "ReadWriteFile.h"

#include "Serialization/JsonSerializer.h" // Json
#include "JsonObjectConverter.h" // Json Utilities

FUSpellStruct UReadWriteJsonFile::ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage) 
{
	// Try to read generic json object from file
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return FUSpellStruct();
	}

	FUSpellStruct RetSpellStruct;

	// Try to convert generic json object to the desired structure (Spell Struct). Output goes in RetSpellStruct
	if (!FJsonObjectConverter::JsonObjectToUStruct<FUSpellStruct>(JsonObject.ToSharedRef(), &RetSpellStruct))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read Struct Json Failed - Was not able to convert the json object to your desired structure. Is it the right format / struct? - '%s'"), *JsonFilePath);
		return FUSpellStruct();
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Struct Json Succeeded - '%s'"), *JsonFilePath);
	return RetSpellStruct;
}

void UReadWriteJsonFile::WriteStructToJsonFile(FString JsonFilePath, FUSpellStruct Struct, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to convert struct to generic json object
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Struct);
	if (JsonObject == nullptr) 
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write Struct Json Failed - Was not able to convert the struct to a json object. This shouldn't really happen."));
		return;
	}

	// Try to write json to file 
	WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}

TSharedPtr<FJsonObject> UReadWriteJsonFile::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{ 
	// Try to read file
	FString JsonString = UReadWriteFile::ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;

	// Try to convert string to json object. Output goes in RetJsonObject
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject)) 
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read Json Failed - Was not able to deserialized the json string. Is it the right format - '%s'"), *JsonString);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read String From Json Succeeded - '%s'"), *JsonFilePath);
	return RetJsonObject;
}

void UReadWriteJsonFile::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString;

	// Try to convert json object to string. Output goes in JsonString
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write Json Failed - Was not able to serialize the json to string. Is the JsonObject valid?"));
		return;
	}

	// Try to write json string to file 
	UReadWriteFile::WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return;
	}


	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write to Json Succeeded - '%s'"), *JsonFilePath);

}