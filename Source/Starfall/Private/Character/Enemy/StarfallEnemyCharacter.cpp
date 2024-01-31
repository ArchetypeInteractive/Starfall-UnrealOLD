// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/StarfallEnemyCharacter.h"

AStarfallEnemyCharacter::AStarfallEnemyCharacter()
{
	UE_LOG(LogTemp, Display, TEXT("Hello I'm a bad guy"))
}


void AStarfallEnemyCharacter::PickRandomTarget()
{
/*
    if (Radar->TrackedActors.Num() == 0)
    {
        return; // No actors to track
    }

    int32 RandomIndex = FMath::RandRange(0, TrackedActors.Num() - 1);
    AActor* TargetActor = TrackedActors[RandomIndex];

    if (TargetActor)
    {
        // Implement movement logic here. This could be direct movement, 
        // using AI Pathfinding, etc. depending on your game design.
        // Example: Move directly towards the target actor
        FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direction, MovementSpeed);
    }
*/
}