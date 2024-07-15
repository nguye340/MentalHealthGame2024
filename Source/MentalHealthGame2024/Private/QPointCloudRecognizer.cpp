// Fill out your copyright notice in the Description page of Project Settings.
#include "QPointCloudRecognizer.h"
#include "QGeometry.h"
#include "QGesture.h"
#include "Math/UnrealMathUtility.h"
/*
bool UQPointCloudRecognizer::bUseEarlyAbandoning = true;
bool UQPointCloudRecognizer::bUseLowerBounding = true;

FString UQPointCloudRecognizer::Classify(const UQGesture* Candidate, const TArray<UQGesture*>& TemplateSet)
{
    float MinDistance = TNumericLimits<float>::Max();
    FString GestureClass = "";

    for (const UQGesture* Template : TemplateSet)
    {
        float Distance = GreedyCloudMatch(Candidate, Template, MinDistance);
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            GestureClass = Template->Name;
        }
    }
    return GestureClass;
}

float UQPointCloudRecognizer::GreedyCloudMatch(const UQGesture* Gesture1, const UQGesture* Gesture2, float MinSoFar)
{
    int32 NumPoints = Gesture1->Points.Num();
    float Eps = 0.5f;
    int32 Step = FMath::FloorToInt(FMath::Pow(NumPoints, 1.0f - Eps));

    if (bUseLowerBounding)
    {
        TArray<float> LB1 = ComputeLowerBound(Gesture1->Points, Gesture2->Points, Gesture2->LUT, Step);
        TArray<float> LB2 = ComputeLowerBound(Gesture2->Points, Gesture1->Points, Gesture1->LUT, Step);

        for (int32 i = 0, IndexLB = 0; i < NumPoints; i += Step, IndexLB++)
        {
            if (LB1[IndexLB] < MinSoFar)
                MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));

            if (LB2[IndexLB] < MinSoFar)
                MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    }
    else
    {
        for (int32 i = 0; i < NumPoints; i += Step)
        {
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    }
    return MinSoFar;
}

TArray<float> UQPointCloudRecognizer::ComputeLowerBound(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, const TArray<FNestedArray>& LUT, int32 Step)
{
    int32 NumPoints = Points1.Num();
    TArray<float> LB;
    LB.SetNum(NumPoints / Step + 1);
    TArray<float> SAT;
    SAT.SetNum(NumPoints);

    LB[0] = 0;
    int32 LUTScaleFactor = UQGesture::GetLUTScaleFactor();
    for (int32 i = 0; i < NumPoints; i++)
    {
        int32 Index = LUT[Points1[i].intY / LUTScaleFactor].InnerArray[Points1[i].intX / LUTScaleFactor];
        float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[Index]);
        SAT[i] = (i == 0) ? Distance : SAT[i - 1] + Distance;
        LB[0] += (NumPoints - i) * Distance;
    }

    for (int32 i = Step, IndexLB = 1; i < NumPoints; i += Step, IndexLB++)
    {
        LB[IndexLB] = LB[0] + i * SAT[NumPoints - 1] - NumPoints * SAT[i - 1];
    }
    return LB;
}

float UQPointCloudRecognizer::CloudDistance(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, int32 StartIndex, float MinSoFar)
{
    int32 NumPoints = Points1.Num();
    TArray<int32> IndexesNotMatched;
    IndexesNotMatched.SetNum(NumPoints);

    for (int32 j = 0; j < NumPoints; j++)
    {
        IndexesNotMatched[j] = j;
    }

    float Sum = 0;
    int32 i = StartIndex;
    int32 Weight = NumPoints;
    int32 IndexNotMatched = 0;

    do
    {
        int32 Index = -1;
        float MinDistance = TNumericLimits<float>::Max();
        for (int32 j = IndexNotMatched; j < NumPoints; j++)
        {
            float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[IndexesNotMatched[j]]);
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                Index = j;
            }
        }
        IndexesNotMatched[Index] = IndexesNotMatched[IndexNotMatched];
        Sum += (Weight--) * MinDistance;

        if (bUseEarlyAbandoning && Sum >= MinSoFar)
        {
            return Sum;
        }

        i = (i + 1) % NumPoints;
        IndexNotMatched++;
    } while (i != StartIndex);

    return Sum;
}
*/


bool UQPointCloudRecognizer::bUseEarlyAbandoning = true;
bool UQPointCloudRecognizer::bUseLowerBounding = true;

FString UQPointCloudRecognizer::Classify(const UQGesture* Candidate, const TArray<UQGesture*>& TemplateSet)
{
    float MinDistance = TNumericLimits<float>::Max();
    FString GestureClass = "";
    
    for (const UQGesture* Template : TemplateSet)
    {
        float Distance = GreedyCloudMatch(Candidate, Template, MinDistance);
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            GestureClass = Template->Name;
        }
    }
    return GestureClass;
}

float UQPointCloudRecognizer::GreedyCloudMatch(const UQGesture* Gesture1, const UQGesture* Gesture2, float MinSoFar)
{
    int32 NumPoints = Gesture1->Points.Num();
    float Eps = 0.5f;
    int32 Step = FMath::FloorToInt(FMath::Pow(NumPoints, 1.0f - Eps));

   if (bUseLowerBounding)
    {
        //UE_LOG(LogTemp, Error, TEXT("ComputeLowerBound: MinSoFar: %f, Gesture1->Points[0].intX: %d"), MinSoFar, Gesture1->Points.intX);
        TArray<float> LB1 = ComputeLowerBound(Gesture1->Points, Gesture2->Points, Gesture2->LUT, Step);
        UE_LOG(LogTemp, Warning, TEXT("Gesture1->Points.Num(): %d - Gesture2->Points.Num(): %d"), Gesture1->Points.Num(), Gesture2->Points.Num());
        TArray<float> LB2 = ComputeLowerBound(Gesture2->Points, Gesture1->Points, Gesture1->LUT, Step);
  
        for (int32 i = 0, IndexLB = 0; i < NumPoints; i += Step, IndexLB++)
        { 
            if (IndexLB < LB1.Num() && LB1[IndexLB] < MinSoFar) {}
               MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));

            if (IndexLB < LB2.Num() && LB2[IndexLB] < MinSoFar)
                MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    } 
    else
    {
        for (int32 i = 0; i < NumPoints; i += Step)
        {
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    }
    return MinSoFar;
}

TArray<float> UQPointCloudRecognizer::ComputeLowerBound(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, const TArray<FNestedArray>& LUT, int32 Step)
{
    int32 NumPoints = Points1.Num();
    TArray<float> LB;
    LB.SetNum(NumPoints / Step + 1);
    TArray<float> SAT;
    SAT.SetNum(NumPoints);

    LB[0] = 0;
    int32 LUTScaleFactor = UQGesture::GetLUTScaleFactor();

    for (int32 i = 0; i < NumPoints; i++)
    {
        int32 LUTIndexY = Points1[i].intY / LUTScaleFactor;
        UE_LOG(LogTemp, Error, TEXT("ComputeLowerBound: Index: %d, Points1[i].intX: %d"), i, Points1[i].intX);
        UE_LOG(LogTemp, Error, TEXT("ComputeLowerBound: Index: %d, Points1[i].intY: %d"), i, Points1[i].intY);
        UE_LOG(LogTemp, Error, TEXT("LUTScaleFactor: %d"), LUTScaleFactor);


        int32 LUTIndexX = Points1[i].intX / LUTScaleFactor;

        if (LUTIndexY >= 0 && LUTIndexY < LUT.Num() && LUTIndexX >= 0 && LUTIndexX < LUT[LUTIndexY].InnerArray.Num())
        {
            int32 Index = LUT[LUTIndexY].InnerArray[LUTIndexX];
            if (Index >= 0 && Index < Points2.Num())
            {
                float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[Index]);
                SAT[i] = (i == 0) ? Distance : SAT[i - 1] + Distance;
                LB[0] += (NumPoints - i) * Distance;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ComputeLowerBound: Index out of range. Index: %d, Points2.Num(): %d"), Index, Points2.Num());
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ComputeLowerBound: LUT Index out of range. LUTIndexY: %d, LUTIndexX: %d"), LUTIndexY, LUTIndexX);
        }
    }

    for (int32 i = Step, IndexLB = 1; i < NumPoints; i += Step, IndexLB++)
    {
        LB[IndexLB] = LB[0] + i * SAT[NumPoints - 1] - NumPoints * SAT[i - 1];
    }
    return LB;
}

float UQPointCloudRecognizer::CloudDistance(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, int32 StartIndex, float MinSoFar)
{
    int32 NumPoints = Points1.Num();    // the two point clouds should have the same number of points by now
    UE_LOG(LogTemp, Warning, TEXT("NumPoints: %d---------------------------------------------"), NumPoints);
    TArray<int32> IndexesNotMatched;    // stores point indexes for points from the 2nd cloud that haven't been matched yet
    IndexesNotMatched.SetNum(NumPoints);

    for (int32 j = 0; j < NumPoints; j++)
    {
        IndexesNotMatched[j] = j;
    }

    float Sum = 0;                      // computes the sum of distances between matched points (i.e., the distance between the two clouds)
    int32 i = StartIndex;               // start matching with point startIndex from the 1st cloud
    int32 Weight = NumPoints;           // implements weights, decreasing from n to 1       
    int32 IndexNotMatched = 0;          // indexes the indexesNotMatched[..] array of points from the 2nd cloud that are not matched yet
    
    do
    {
        int32 Index = -1;
        float MinDistance = TNumericLimits<float>::Max();
        for (int32 j = IndexNotMatched; j < NumPoints; j++)
        {
            float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[IndexesNotMatched[j]]); // use the squared Euclidean distance
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                Index = j;
            }
        }
        IndexesNotMatched[Index] = IndexesNotMatched[IndexNotMatched];
        Sum += (Weight--) * MinDistance;

        if (bUseEarlyAbandoning && Sum >= MinSoFar)
        {
            return Sum;
        }
        UE_LOG(LogTemp, Error, TEXT("NumPoints: %d---------------------------------------------"),NumPoints);
        /*i = (i + 1) % NumPoints;*/ // advance to the next point in the 1st cloud
        IndexNotMatched++;
    } while (i != StartIndex);

    return Sum;
}
