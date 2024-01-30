// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/StarfallCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Character/Component/Abilities/StarfallLiftAbility.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"





AStarfallCharacter::AStarfallCharacter()
{

	WalkSpeed = 420.f;		//	We will move this into our custom movement component
	SprintSpeed = 700.f;	//	We will move this into our custom movement component

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)








}

void AStarfallCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}






//	----------------------------------------------------------------------
//	Input
//	----------------------------------------------------------------------
//	These methods are to be called from the derived class! For instance,
//	Our StarfallHeroCharacter class calls these methods and pushes it's
//	EnhancedInputAction values to these members.

void AStarfallCharacter::Move(const FVector2D& MovementVector)
{
	// input is a Vector2D
	//	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

	}
}

void AStarfallCharacter::Look(const FVector2D& LookInput)
{
	//	input is a Vector2D
	//	FVector LookAxis = LookInput.
	
	if (Controller != nullptr)
	{

		//	CLAMP THE LOOK INPUT
		LookYaw = FMath::Clamp(LookYaw + LookInput.X, 0.f, 0.f);
		LookPitch = FMath::Clamp(LookPitch, -18.f, 18.f);

		//	LookYaw = FMath::Clamp(LookInput.X, -10.0f, 20.0f);
		//	LookPitch = FMath::Clamp(LookInput.Y, -18.0f, 18.0f);

		AddControllerYawInput(FMath::Clamp(LookInput.X, -10.f, 20.f));
		AddControllerPitchInput(FMath::Clamp(LookInput.Y, -18.f, 18.f));

		//	Align the character's mesh with the controller's yaw.
		//	FRotator NewRotation = GetMesh()->GetComponentRotation();
		//	NewRotation.Yaw = Controller->GetControlRotation().Yaw;
		//	GetMesh()->SetWorldRotation(NewRotation);
	}
}



void AStarfallCharacter::StartJump(const FVector& JumpInput)
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Super::Jump();
	}
	//	else if(!bIsLifting)
	//	{
	//		bIsLifting = true;
	//		//	this->StartLiftJump();
	//		OnLiftJumpActivated.ExecuteIfBound();
	//	}
}

void AStarfallCharacter::StopJump()
{
	Super::StopJumping();
	//	UE_LOG(LogTemp, Display, TEXT("Stopping jump"));

	//	GetWorldTimerManager().ClearTimer(LiftTimerHandle);
}

void AStarfallCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	// Your custom logic here
	this->StopJump();
	UE_LOG(LogTemp, Display, TEXT("Landed from jump / fall"));
}


void AStarfallCharacter::Sprint()
{

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	UE_LOG(LogTemp, Display, TEXT("Sprinting"));
}

void AStarfallCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	UE_LOG(LogTemp, Display, TEXT("Stop Sprinting"));
}


void AStarfallCharacter::StartCrouch()
{
	FVector Velocity = GetVelocity();
	float Speed = Velocity.Size();

	if (Speed <= WalkSpeed)
	{
		bIsCrouching = true;
		Super::Crouch();
		UE_LOG(LogTemp, Display, TEXT("Crouching"));
	}
	else if (Speed >= WalkSpeed) 
	{

		UE_LOG(LogTemp, Display, TEXT("Sliding"));
		/*
		bIsSliding = true;


		GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &AStarfallCharacter::UpdateSlide, SlideUpdateInterval, true);
		*/

		//	set character's state to sliding
		//	We need to get the direction of the character's movement
		//	ignore move input
		//  use three lerps connected to the sprint charge to determine the slide's speed
		//	lerp 1: 1.0f -> 0.5f
		//	lerp 2: 2.0f -> 1.25f
		//	lerp 3: 0.65f -> 5.0f
		//  these lerps are plugged into a "set play rate" node
		//  the play rates are plugged into a Timeline node
		//  Timeline:
		//    Length: 1:00
		//    Enable use last keyframe
		//	  Float curve named "SlideAlpha"
		//	  Float: (0.0, 1.0) -> (1.0, 0.0)
		//  After the timeline,
		//  add a new lerp to set the character's max walk speed targeting the character movement component
		//  lerp: A: WalkSpeed * 0.65f, B: WalkSpeed * output of third Lerp from timeline, alpha: slide out from timeline
		//  After setting max walk speed,
		//	Set Braking Friction Factor to Slide Out from Timeline - 1.0f
		//	Add movement input
		//    World Direction: Slide Direction
		//    Scale Value: Slide out from Timeline
		//    Force: true
	
		//  Going back to Timeline, Finished should set the character's state to crouching
	
	}
}

void AStarfallCharacter::StopCrouch()
{
	Super::UnCrouch();
	UE_LOG(LogTemp, Display, TEXT("Uncrouching"))
}


void AStarfallCharacter::UpdateSlide()
{
	float ElapsedTime = GetWorld()->GetTimeSeconds() - SlideStartTime;
	float SlideAlpha = ElapsedTime / MaxSlideDuration;

	SlideAlpha = FMath::Clamp(SlideAlpha, 0.0f, 1.0f);

	// Calculate Lerp values based on SlideAlpha
	float Lerp1 = FMath::Lerp(1.0f, 0.5f, SlideAlpha);
	float Lerp2 = FMath::Lerp(2.0f, 1.25f, SlideAlpha);
	float Lerp3 = FMath::Lerp(0.65f, 5.0f, SlideAlpha);

	// Adjust character movement based on lerps
	float NewSpeed = FMath::Lerp(WalkSpeed * 0.65f, WalkSpeed * Lerp3, SlideAlpha);
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	GetCharacterMovement()->BrakingFrictionFactor = SlideAlpha - 1.0f;

	// Add movement input
	FVector SlideDirection = GetVelocity().GetSafeNormal();
	AddMovementInput(SlideDirection, SlideAlpha, true);





	if (ElapsedTime > MaxSlideDuration)
	{
		StopSlide();  // End slide after maximum duration
		GetWorldTimerManager().ClearTimer(SlideTimerHandle);
	}

	if (GetVelocity().Size() < MinSlideSpeed)
	{
		StopSlide();  // End slide if speed drops below minimum
		GetWorldTimerManager().ClearTimer(SlideTimerHandle);
	}
}


void AStarfallCharacter::StopSlide()
{
	// Cleanup and end sliding

	UE_LOG(LogTemp, Display, TEXT("Ending slide"));

}