// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/Mode/StarfallGameMode.h"
#include "Game/StarfallGameInstance.h"
#include "Character/StarfallCharacter.h"
#include "Character/StarfallHeroController.h"
#include "UObject/ConstructorHelpers.h"

AStarfallGameMode::AStarfallGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AStarfallHeroController> PlayerControllerBPClass(TEXT("/Game/Characters/BP_StarfallHeroController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	//	PlayerControllerClass = AStarfallHeroController::StaticClass();
}



void AStarfallGameMode::UpdateScore()
{
	// Placeholder for score logic
	Score += 10; // Example score increment
}

void AStarfallGameMode::PrintScoreToScreen()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Score: %d"), Score));
	}
}