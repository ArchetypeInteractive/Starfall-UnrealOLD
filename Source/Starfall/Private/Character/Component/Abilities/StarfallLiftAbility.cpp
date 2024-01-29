// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Abilities/StarfallLiftAbility.h"
#include "Character/StarfallCharacter.h"

void UStarfallLiftAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (AStarfallCharacter* RefCharacter = Cast<AStarfallCharacter>(ActorInfo->AvatarActor.Get()))
    {
        //  RefCharacter->StartLift();
    }
}