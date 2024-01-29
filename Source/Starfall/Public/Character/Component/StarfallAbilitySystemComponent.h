// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "StarfallAbilitySystemComponent.generated.h"




UENUM(BlueprintType)
enum class ECelestialAbilities : uint8
{
    None UMETA(DisplayName = "None"),
    Lift UMETA(DisplayName = "Lift"),
    Grenade UMETA(DisplayName = "Grenade")
};




UCLASS()
class STARFALL_API UStarfallAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

    //  Hello


protected:


};