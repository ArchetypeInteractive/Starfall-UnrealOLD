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


//	DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AStarfallCharacter

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


	//	Create a follow camera
	StarfallInventoryComponent = CreateDefaultSubobject<UStarfallInventoryComponent>(TEXT("Inventory Component"));
	//	StarfallInventoryComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AbilitySystem = CreateDefaultSubobject<UStarfallAbilitySystemComponent>(TEXT("Ability System Component"));
	//	LiftAbilityClass = StarfallLiftAbility::StaticClass();





}

void AStarfallCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	bIsLifting = false;
	LiftStrength = 100.0f; // Adjust this value as needed
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
		bIsLifting = false;
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

	bIsLifting = false;
	GetWorldTimerManager().ClearTimer(LiftTimerHandle);
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
		Super::Crouch();
		UE_LOG(LogTemp, Display, TEXT("Crouching"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("We gon' slide instead"));
	}
}


/*
void AStarfallCharacter::StartLiftJump()
{
		// Stop the timer if lifting is no longer active
		//GetWorldTimerManager().ClearTimer(LiftTimerHandle);
	
	if (!bIsLifting && !GetCharacterMovement()->IsMovingOnGround())
	{
		bIsLifting = true;
		GetWorldTimerManager().SetTimer(LiftTimerHandle, this, &AStarfallCharacter::ApplyLiftForce, 0.1f, true, 0.0f);
	}
}


void AStarfallCharacter::ApplyLiftForce()
{
	FVector CurrentVelocity = GetVelocity();
	FVector ForwardVelocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0); // Preserve only the horizontal components

	// Determine the forward force based on the current forward velocity
	float ForwardScale = 0.5f; // Adjust this value to your needs
	FVector ForwardForce = ForwardVelocity * ForwardScale;

	// Calculate the lift force
	FVector LiftForce = FVector(0, 0, LiftStrength);

	// Combine forward force and lift force
	FVector CombinedForce = LiftForce + ForwardForce;

	// Apply the combined force to the character's velocity
	GetCharacterMovement()->Velocity += CombinedForce;

	// Clamp the velocity to a maximum value
	float MaxSpeed = 1200.0f; // Set this to your desired maximum speed
	GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity.GetClampedToMaxSize(MaxSpeed);

	UE_LOG(LogTemp, Display, TEXT("Applying Lift Force: %s"), *CombinedForce.ToString());
}
*/