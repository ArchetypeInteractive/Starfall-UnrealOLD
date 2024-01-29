// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


//  Consider this as well: https://github.com/Voidware-Prohibited/ALSXT


#include "CoreMinimal.h"
//	#include "ALS-Refactored/ALSCharacter.h"
//	#include "ALSCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Component/StarfallInventoryComponent.h"
#include "Component/StarfallAbilitySystemComponent.h"
#include "StarfallCharacter.generated.h"

//	DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DELEGATE(FOnLiftJumpActivated);

UCLASS(config=Game)
class AStarfallCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStarfallInventoryComponent> StarfallInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UStarfallAbilitySystemComponent* AbilitySystem;

public:
	AStarfallCharacter();
	
	/** Called for movement input */
	void Move(const FVector2D& MovementVector);

	/** Called for looking input */
	void Look(const FVector2D& LookInput);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float LookPitch = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float LookYaw = 0.f;

	void StartJump(const FVector& JumpInput);
	void StopJump();
	
	
	FOnLiftJumpActivated OnLiftJumpActivated;
	
	float WalkSpeed;
	float SprintSpeed;

	void Landed(const FHitResult& Hit);
	virtual void Sprint();
	virtual void StopSprinting();
	void StartCrouch();
	//	void StopCrouch();

	//	void StartLiftJump();	// Probably not needed
	//	void ApplyLiftForce();
	//	void StopLiftJump();

	/*
	void PerformLift();
	bool CanLift() const;
	UFUNCTION()
	void ActivateAbility(ECelestialAbilities Ability);
	TSubclassOf<UGameplayAbility> GetAbilityClass(ECelestialAbilities Ability) const;
	
	TSubclassOf<UGameplayAbility> LiftAbilityClass;
	*/

protected:
	// To add mapping context
	virtual void BeginPlay();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}






	//	void Crouch(const FVector& CrouchInput);
	//	void CrouchStop();


private:
	bool bIsLifting = false;
	float LiftStrength; // Adjust as needed
	float LiftDuration = 1.5f;   // Total duration of lift in seconds
	FTimerHandle LiftTimerHandle;
};

