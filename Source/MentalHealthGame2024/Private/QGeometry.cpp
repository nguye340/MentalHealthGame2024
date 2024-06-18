// Fill out your copyright notice in the Description page of Project Settings.


#include "QGeometry.h"
#include "QPoint.h"

float UQGeometry::SqrEuclideanDistance(const FQPoint& A, const FQPoint& B)
{
    return (A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y);
}

float UQGeometry::EuclideanDistance(const FQPoint& A, const FQPoint& B)
{
    return FMath::Sqrt(SqrEuclideanDistance(A, B));
}