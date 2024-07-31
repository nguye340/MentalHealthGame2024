#include "DataTableCsvJsonParser.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "Engine/DataTable.h"
#include "UObject/UnrealType.h"

#include <Misc/OutputDeviceNull.h>

FString UDataTableCsvJsonParser::GetTableAsCSV(const UDataTable* DataTable)
{
    FString Result;
    if (!DataTable || !DataTable->GetRowStruct())
    {
        return TEXT("Missing DataTable or RowStruct!\n");
    }

    const UScriptStruct* RowStruct = DataTable->GetRowStruct();
    TArray<FName> RowNames = DataTable->GetRowNames();
    FOutputDeviceNull Ar;

    // Write header
    for (TFieldIterator<const FProperty> It(RowStruct); It; ++It)
    {
        const FProperty* Prop = *It;
        Result += Prop->GetName();
        Result += TEXT(",");
    }
    Result.RemoveFromEnd(TEXT(","));
    Result += TEXT("\n");

    // Write rows
    for (const FName& RowName : RowNames)
    {
        uint8* RowData = DataTable->FindRowUnchecked(RowName);
        RowStruct->ExportText(Result, RowData, RowData, nullptr, PPF_None, nullptr);
        Result += TEXT("\n");
    }

    return Result;
}

FString UDataTableCsvJsonParser::GetTableAsJSON(const UDataTable* DataTable)
{
    FString Result;
    if (!DataTable || !DataTable->GetRowStruct())
    {
        return TEXT("Missing DataTable or RowStruct!\n");
    }

    const UScriptStruct* RowStruct = DataTable->GetRowStruct();
    TArray<FName> RowNames = DataTable->GetRowNames();
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);

    Writer->WriteArrayStart();

    for (const FName& RowName : RowNames)
    {
        uint8* RowData = DataTable->FindRowUnchecked(RowName);
        if (RowData)
        {
            Writer->WriteObjectStart();
            Writer->WriteValue("Name", RowName.ToString());

            for (TFieldIterator<const FProperty> It(RowStruct); It; ++It)
            {
                const FProperty* Prop = *It;
                const void* Value = Prop->ContainerPtrToValuePtr<void>(RowData);

                // For Description in SpellStruct
                if (const FStrProperty* StrProp = CastField<const FStrProperty>(Prop))
                {
                    Writer->WriteValue(Prop->GetName(), StrProp->GetPropertyValue(Value));
                }
                // For SpellName in SpellStruct
                else if (const FNameProperty* NameProp = CastField<const FNameProperty>(Prop))
                {
                    Writer->WriteValue(Prop->GetName(), NameProp->GetPropertyValue(Value).ToString());
                }
                // For Image in SpellStruct
                else if (const FObjectProperty* ObjProp = CastField<const FObjectProperty>(Prop)) 
                {
                    if (ObjProp->PropertyClass == UTexture2D::StaticClass())
                    {
                        UTexture2D* Texture = Cast<UTexture2D>(ObjProp->GetPropertyValue(Value));
                        Writer->WriteValue(Prop->GetName(), Texture ? Texture->GetName() : FString("None"));
                    }
                }
                // For SpellID in SpellStruct
                else if (const FIntProperty* IntProp = CastField<const FIntProperty>(Prop))
                {
                    Writer->WriteValue(Prop->GetName(), IntProp->GetPropertyValue(Value));
                }
                // For Cost or Damage in SpellStruct
                else if (const FFloatProperty* FloatProp = CastField<const FFloatProperty>(Prop))
                {
                    Writer->WriteValue(Prop->GetName(), FloatProp->GetPropertyValue(Value));
                }
                // For if it's unlocked yet or not in SpellStruct
                else if (const FBoolProperty* BoolProp = CastField<const FBoolProperty>(Prop))
                {
                    Writer->WriteValue(Prop->GetName(), BoolProp->GetPropertyValue(Value));
                }
                // For the array of 2D vector points (GesturePoints)
                if (const FArrayProperty* ArrayProp = CastField<const FArrayProperty>(Prop))
                {
                    Writer->WriteArrayStart(Prop->GetName());
                    FScriptArrayHelper ArrayHelper(ArrayProp, Value);
                    for (int32 i = 0; i < ArrayHelper.Num(); ++i)
                    {
                        const uint8* ArrayValue = ArrayHelper.GetRawPtr(i);
                        if (const FStructProperty* StructProp = CastField<const FStructProperty>(ArrayProp->Inner))
                        {
                            if (StructProp && StructProp->Struct == TBaseStructure<FVector2D>::Get())
                            {
                                const FVector2D* Vector = reinterpret_cast<const FVector2D*>(ArrayValue);
                                if (Vector)
                                {
                                    // Format the FVector2D as "(X=...,Y=...)"
                                    FString VectorString = FString::Printf(TEXT("(X=%f,Y=%f)"), Vector->X, Vector->Y);
                                    Writer->WriteValue(VectorString);
                                }
                            }
                        }
                    }
                    Writer->WriteArrayEnd();
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Unhandled property type for property %s"), *Prop->GetName());
                }
                // Explicit Field Handling
          


                // Handle other property types as needed...
            }
            Writer->WriteObjectEnd();

/*
            // Explicitly serialize expected fields
            const FString* SpellName = RowStruct->FindPropertyByName(TEXT("SpellName")) ? RowStruct->FindPropertyByName(TEXT("SpellName"))->ContainerPtrToValuePtr<FString>(RowData) : nullptr;
            const FString* Image = RowStruct->FindPropertyByName(TEXT("Image")) ? RowStruct->FindPropertyByName(TEXT("Image"))->ContainerPtrToValuePtr<FString>(RowData) : nullptr;
            const int32* SpellID = RowStruct->FindPropertyByName(TEXT("SpellID")) ? RowStruct->FindPropertyByName(TEXT("SpellID"))->ContainerPtrToValuePtr<int32>(RowData) : nullptr;
            const int32* Damage = RowStruct->FindPropertyByName(TEXT("Damage")) ? RowStruct->FindPropertyByName(TEXT("Damage"))->ContainerPtrToValuePtr<int32>(RowData) : nullptr;
            const int32* Cost = RowStruct->FindPropertyByName(TEXT("Cost")) ? RowStruct->FindPropertyByName(TEXT("Cost"))->ContainerPtrToValuePtr<int32>(RowData) : nullptr;
            const int32* Cooldown = RowStruct->FindPropertyByName(TEXT("Cooldown")) ? RowStruct->FindPropertyByName(TEXT("Cooldown"))->ContainerPtrToValuePtr<int32>(RowData) : nullptr;
            const FString* Desc = RowStruct->FindPropertyByName(TEXT("Desc")) ? RowStruct->FindPropertyByName(TEXT("Desc"))->ContainerPtrToValuePtr<FString>(RowData) : nullptr;
            const bool* IsUnlocked = RowStruct->FindPropertyByName(TEXT("IsUnlocked")) ? RowStruct->FindPropertyByName(TEXT("IsUnlocked"))->ContainerPtrToValuePtr<bool>(RowData) : nullptr;
            const TArray<FString>* GesturePoints = RowStruct->FindPropertyByName(TEXT("GesturePoints")) ? RowStruct->FindPropertyByName(TEXT("GesturePoints"))->ContainerPtrToValuePtr<TArray<FString>>(RowData) : nullptr;
            
            // Write each property to the JSON writer
            if (SpellName)
                Writer->WriteValue("SpellName", *SpellName);
            else
                UE_LOG(LogTemp, Warning, TEXT("SpellName is missing for row %s"), *RowName.ToString());

            if (Image)
                Writer->WriteValue("Image", *Image);
            else
                UE_LOG(LogTemp, Warning, TEXT("Image is missing for row %s"), *RowName.ToString());

            if (SpellID)
                Writer->WriteValue("SpellID", *SpellID);
            if (Damage)
                Writer->WriteValue("Damage", *Damage);
            if (Cost)
                Writer->WriteValue("Cost", *Cost);
            if (Cooldown)
                Writer->WriteValue("Cooldown", *Cooldown);
            if (Desc)
                Writer->WriteValue("Desc", *Desc);
            if (IsUnlocked)
                Writer->WriteValue("IsUnlocked", *IsUnlocked);

            if (GesturePoints)
            {
                Writer->WriteArrayStart("GesturePoints");
                for (const FString& Point : *GesturePoints)
                {
                    Writer->WriteValue(Point);
                }
                Writer->WriteArrayEnd();
            }
            else
                UE_LOG(LogTemp, Warning, TEXT("GesturePoints is missing for row %s"), *RowName.ToString());

            Writer->WriteObjectEnd();*/

        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("RowData is null for row %s"), *RowName.ToString());
        }
    }

    Writer->WriteArrayEnd();
    Writer->Close();

    return Result;
}