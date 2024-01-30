// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


//  Consider this as well: https://github.com/Voidware-Prohibited/ALSXT


#include "CoreMinimal.h"
//	#include "ALS-Refactored/ALSCharacter.h"
//	#include "ALSCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/StarfallAbilitySystemComponent.h"
#include "StarfallCharacter.generated.h"







DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCrouchEvent);
//	DECLARE_DELEGATE(FOnLiftJumpActivated);

UCLASS(config=Game)
class AStarfallCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


	//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<UStarfallInventoryComponent> StarfallInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UStarfallAbilitySystemComponent* AbilitySystem;





public:
	AStarfallCharacter();
	
	

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void OnCrouchEvent();




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
	
	float WalkSpeed;
	float SprintSpeed;

	void Landed(const FHitResult& Hit);
	virtual void Sprint();
	virtual void StopSprinting();
	void StartCrouch();
	void StopCrouch();

	void UpdateSlide();
	void StopSlide();
protected:
	// To add mapping context
	virtual void BeginPlay();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsCrouching = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsSliding = false;
	bool bIsJumping = false;



	//	void Crouch(const FVector& CrouchInput);
	//	void CrouchStop();



private:
	FTimerHandle SlideTimerHandle;
	float SlideStartTime = 0.f;  // Time when sliding started
	const float SlideUpdateInterval = 0.05f;
	float MaxSlideDuration = 2.0f;  // Maximum duration of slide
	float MinSlideSpeed = 400.f;  // Minimum speed to maintain slide
};

