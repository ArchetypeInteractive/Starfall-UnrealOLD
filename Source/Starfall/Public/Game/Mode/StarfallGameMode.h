// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarfallGameMode.generated.h"


UCLASS(minimalapi)
class AStarfallGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStarfallGameMode();

    // The score variable
    int32 Score;

    // Function to update the score - this is just a placeholder for now
    void UpdateScore();

    // Function to print the score to the screen
    void PrintScoreToScreen();
};



