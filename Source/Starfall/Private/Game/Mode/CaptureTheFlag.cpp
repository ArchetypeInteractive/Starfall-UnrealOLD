// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Mode/CaptureTheFlag.h"
#include "Engine/Engine.h"

ACaptureTheFlag::ACaptureTheFlag()
{

    // Initialize score
    Score = 0;
}

void ACaptureTheFlag::BeginPlay()
{
    Super::BeginPlay();

    // Update score (for testing)
    Super::UpdateScore();

    // Print score to screen
    Super::PrintScoreToScreen();
}
