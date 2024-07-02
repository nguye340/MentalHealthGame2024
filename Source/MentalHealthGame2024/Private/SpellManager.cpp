// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellManager.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

/**/
USpellManager::USpellManager()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> SpellDataTableObject(TEXT("/Script/Engine.DataTable'/Game/SpellCastingMechanic/DT_Spells.DT_Spells'"));
    if (SpellDataTableObject.Succeeded())
    {
        SpellDataTable = SpellDataTableObject.Object;
        LoadSpells();
    }
}

USpellManager::~USpellManager()
{

}

void USpellManager::LoadSpells()
{
    if (SpellDataTable)
    {
        TArray<FName> RowNames = SpellDataTable->GetRowNames();
        for (const FName& Name : RowNames)
        {
            FUSpellStruct* Spell = SpellDataTable->FindRow<FUSpellStruct>(Name, TEXT(""));
            if (Spell)
            {
                Spells.Add(Name, *Spell);
            }
        }
    }
}

void USpellManager::AddPlayerGestureToFirstRow(const TArray<FVector2D>& NewGesturePoints)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HEYYYYYYYYYY Got in to add player gesture"));

    if (SpellDataTable)
    {
        TArray<FName> RowNames = SpellDataTable->GetRowNames();
        if (RowNames.Num() > 0)
        {
            FName FirstRowName = RowNames[0];
            FUSpellStruct* FirstRow = SpellDataTable->FindRow<FUSpellStruct>(FirstRowName, TEXT(""));
            if (FirstRow)
            {
                FirstRow->GesturePoints = NewGesturePoints;
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Updated Gesture Points for the first row"));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to find the first row in the data table"));
            }
        }
    }
}
