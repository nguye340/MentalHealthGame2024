// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellManager.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "QPointCloudRecognizer.h"
#include "QPoint.h"

USpellManager::USpellManager()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> SpellDataTableObject(TEXT("/Script/Engine.DataTable'/Game/SpellCastingMechanic/JSON/DT_Spells_Json.DT_Spells_Json'"));
    if (SpellDataTableObject.Succeeded())
    {
        SpellDataTable = SpellDataTableObject.Object;
        LoadSpellTemplates();
    }
}

void USpellManager::LoadSpellTemplates()
{
    
    if (SpellDataTable)
    {
        TArray<FName> RowNames = SpellDataTable->GetRowNames();
        for (const FName& Name : RowNames)
        {
            FUSpellStruct* Spell = SpellDataTable->FindRow<FUSpellStruct>(Name, TEXT(""));
            if (Spell)
            {
                SpellTemplates.Add(Name.ToString(), *Spell);
            }
        }
    }
}

UQGesture* USpellManager::CreateGesture(const TArray<FVector2D>& Vector2DPoints, FString GestureName, bool isPlayerRawInput)
{
    if (Vector2DPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateGesture: Vector2DPoints is empty"));
        return nullptr;
    }

    UQGesture* GestureInstance = NewObject<UQGesture>();
    if (!GestureInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateGesture: Failed to create UQGesture instance"));
        return nullptr;
    }

    UE_LOG(LogTemp, Warning, TEXT("CreateGesture: Creating gesture with '%i' points"), Vector2DPoints.Num());

    // Create template gesture points
    TArray<FQPoint> NewFQPoints = GestureInstance->Convert(Vector2DPoints, isPlayerRawInput);
    UE_LOG(LogTemp, Error, TEXT("CreateGesture: '%d' ============================="), NewFQPoints.Num());
   
    // Log each point in the NewFQPoints array
    for (int32 i = 0; i < NewFQPoints.Num(); i++)
    {
        const FQPoint& Point = NewFQPoints[i];
        //UE_LOG(LogTemp, Error, TEXT("CreateGesture: Point[%d] - X: %f, Y: %f"), i, Point.X, Point.Y);
    }


    GestureInstance->Initialize(NewFQPoints, GestureName);

    return GestureInstance;
}

FString USpellManager::SpellRecognizer(const TArray<FVector2D>& PlayerRawInPoints, TMap<FString, FUSpellStruct> SpellTemplates)
{
    UE_LOG(LogTemp, Warning, TEXT("SpellRecognizer: Starting spell recognition - Player add '%d'"), PlayerRawInPoints.Num());

    if (PlayerRawInPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("SpellRecognizer: PlayerRawInPoints is empty"));
        return FString("No Match");
    }

    TArray<UQGesture*> GestureTemplates;

    // Convert each spell struct in the TMap to a UQGesture instance
    for (const TPair<FString, FUSpellStruct>& SpellPair : SpellTemplates)
    {
        const FString& SpellName = SpellPair.Key;
        const FUSpellStruct& SpellStruct = SpellPair.Value;

        if (SpellStruct.GesturePoints.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("SpellRecognizer: Spell '%s' has no gesture points"), *SpellName);
            continue;
        }

        if (!ArePointsValid(SpellStruct.GesturePoints))
        {
            UE_LOG(LogTemp, Warning, TEXT("SpellRecognizer: Spell '%s' has invalid gesture points"), *SpellName);
            continue;
        }
        
        for (int32 i = 0; i < SpellStruct.GesturePoints.Num(); i++)
        {
            const FVector2D& Point = SpellStruct.GesturePoints[i];
            //UE_LOG(LogTemp, Log, TEXT("SpellRecognizer: Spell '%s' GesturePoint[%d] - X: %f, Y: %f"), *SpellName, i, Point.X, Point.Y);
        }

        // Create new gesture from template set
        UQGesture* NewGesture = CreateGesture(SpellStruct.GesturePoints, SpellName, false);
        if (NewGesture)
        {
            GestureTemplates.Add(NewGesture);
           // CheckGesturePoints(NewGesture, SpellName); // Check new gesture points here
        }
    }

    if (GestureTemplates.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("SpellRecognizer: No valid gestures found in SpellTemplates"));
        return FString("No Match");
    }

    // Create the player's gesture
    UQGesture* PlayerGesture = CreateGesture(PlayerRawInPoints, TEXT("PlayerGesture"), true);
    CheckGesturePoints(PlayerGesture, TEXT("PlayerGesture")); // Check new gesture points here

    if (!PlayerGesture)
    {
        UE_LOG(LogTemp, Error, TEXT("SpellRecognizer: Failed to create PlayerGesture"));
        return FString("No Match");
    }

    // Use your gesture recognizer to find the closest match
    FString RecognizedSpell = UQPointCloudRecognizer::Classify(PlayerGesture, GestureTemplates);

    UE_LOG(LogTemp, Log, TEXT("SpellRecognizer: Recognized Spell: %s"), *RecognizedSpell);

    return RecognizedSpell;
}

bool USpellManager::ArePointsValid(const TArray<FVector2D>& Points)
{
    for (const FVector2D& Point : Points)
    {
        if (Point.X < 0 || Point.Y < 0)
        {
            UE_LOG(LogTemp, Error, TEXT("ArePointsValid: Invalid point found - X: %f, Y: %f"), Point.X, Point.Y);
            return false;
        }
    }
    return true;
}

void USpellManager::CheckGesturePoints(const UQGesture* Gesture, const FString& GestureName)
{
    if (Gesture == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("CheckGesturePoints: Gesture is null for '%s'"), *GestureName);
        return;
    }

    const TArray<FQPoint>& Points = Gesture->GetPoints();
    for (int32 i = 0; i < Points.Num(); i++)
    {
        const FQPoint& Point = Points[i];
        if (Point.intX < 0 || Point.intY < 0)
        {
            UE_LOG(LogTemp, Error, TEXT("CheckGesturePoints: Invalid point found at index %d for gesture '%s' - intX: %d, intY: %d"), i, *GestureName, Point.intX, Point.intY);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("CheckGesturePoints: Point at index %d for gesture '%s' is valid - intX: %d, intY: %d"), i, *GestureName, Point.intX, Point.intY);
        }
    }
}
/*
USpellManager::USpellManager() 
{
    static ConstructorHelpers::FObjectFinder<UDataTable> SpellDataTableObject(TEXT("/Script/Engine.DataTable'/Game/SpellCastingMechanic/JSON/DT_Spells_Json.DT_Spells_Json'"));
    if (SpellDataTableObject.Succeeded())
    {
        SpellDataTable = SpellDataTableObject.Object;
        LoadSpellTemplates();
    }
}

void USpellManager::LoadSpellTemplates()
{
    if (SpellDataTable)
    {
        TArray<FName> RowNames = SpellDataTable->GetRowNames();
        for (const FName& Name : RowNames)
        {
            FUSpellStruct* Spell = SpellDataTable->FindRow<FUSpellStruct>(Name, TEXT(""));
            if (Spell)
            {
                SpellTemplates.Add(Name.ToString(), *Spell);
            }
        }
    }
}

UQGesture* USpellManager::CreateGesture(const TArray<FVector2D>& Vector2DPoints, FString GestureName)
{
    UQGesture* GestureInstance = NewObject<UQGesture>();
    TArray<FQPoint> NewFQPoints = GestureInstance->Convert(Vector2DPoints);
    
    GestureInstance->Initialize(NewFQPoints, GestureName);

    return GestureInstance;
}

FString USpellManager::SpellRecognizer(const TArray<FVector2D>& PlayerRawInPoints, TMap<FString, FUSpellStruct> SpellTemplates)
{
    TArray<UQGesture*> GestureTemplates;

    // Convert each spell struct in the TMap to a UQGesture instance
    for (const TPair<FString, FUSpellStruct>& SpellPair : SpellTemplates)
    {
        const FString& SpellName = SpellPair.Key;
        const FUSpellStruct& SpellStruct = SpellPair.Value;

        UQGesture* NewGesture = CreateGesture(SpellStruct.GesturePoints, SpellName);
        if (NewGesture)
        {
            GestureTemplates.Add(NewGesture);
        }
    }

    // Create the player's gesture
    UQGesture* PlayerGesture = CreateGesture(PlayerRawInPoints, TEXT("PlayerGesture"));

    // Assuming you have a method to classify gestures
    FString RecognizedSpell = FString(TEXT("No Match"));

    if (PlayerGesture)
    {
        // Use your gesture recognizer to find the closest match
        RecognizedSpell = UQPointCloudRecognizer::Classify(PlayerGesture, GestureTemplates);
    }

    return RecognizedSpell;
}


/*
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
*/