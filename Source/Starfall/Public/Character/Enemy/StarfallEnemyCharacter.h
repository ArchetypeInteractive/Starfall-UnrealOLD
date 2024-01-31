// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/StarfallCharacter.h"
#include "StarfallEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STARFALL_API AStarfallEnemyCharacter : public AStarfallCharacter
{
	GENERATED_BODY()
	

public:
	AStarfallEnemyCharacter();

	void PickRandomTarget();
	//	void MoveToTarget();
	//	void AttackTarget();
};
