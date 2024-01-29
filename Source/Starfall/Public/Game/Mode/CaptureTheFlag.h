// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Mode/StarfallGameMode.h"
#include "CaptureTheFlag.generated.h"

/**
 * 
 */
UCLASS()
class STARFALL_API ACaptureTheFlag : public AStarfallGameMode
{
    GENERATED_BODY()

public:
    ACaptureTheFlag();

    virtual void BeginPlay() override;

protected:

};