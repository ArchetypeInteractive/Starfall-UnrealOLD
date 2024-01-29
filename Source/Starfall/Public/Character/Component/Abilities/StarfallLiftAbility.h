// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "StarfallLiftAbility.generated.h"

/**
 * 
 */
UCLASS()
class STARFALL_API UStarfallLiftAbility : public UGameplayAbility
{
	GENERATED_BODY()


	// Override the ActivateAbility method to implement the lift logic
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
