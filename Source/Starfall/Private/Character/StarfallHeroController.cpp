// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/StarfallHeroController.h"

#include "Character/StarfallHeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"



AStarfallHeroController::AStarfallHeroController()
{
}


void AStarfallHeroController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(GameplayMappingContext, 0);
			InputSubsystem->AddMappingContext(MenuMappingContext, 1);

			UE_LOG(LogTemp, Log, TEXT("Subsystem retrieved successfully."));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve Enhanced Input Local Player Subsystem."));
		}
	}
}






void AStarfallHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//	Set up action bindings
	//	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		EnhancedInputComponent->BindAction(MenuContinueAction, ETriggerEvent::Started, this, &AStarfallHeroController::StartMenuContinue);
		//	EnhancedInputComponent->BindAction(MenuContinueAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopMenuContinue);








		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::Look);
	


		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AStarfallHeroController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopJump);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AStarfallHeroController::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopCrouch);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AStarfallHeroController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopSprint);
	

		EnhancedInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this, &AStarfallHeroController::AimWeapon);
		EnhancedInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopAimWeapon);


		//	This can be a continuous action or a single press action
		EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::FireWeapon);
		//	EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &AStarfallHeroController::FireWeapon);
		EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopFireWeapon);

		//	EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::SwitchWeapon);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Started, this, &AStarfallHeroController::SwitchWeapon);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopSwitchWeapon);

	}
}








void AStarfallHeroController::SwitchContext(UInputMappingContext* InputMappingContext)
{
	UE_LOG(LogTemp, Display, TEXT("Switching context"))
}




void AStarfallHeroController::StartMenuContinue()
{
	UE_LOG(LogTemp, Display, TEXT("Menu Continue"));
}

void AStarfallHeroController::Director()
{
	UE_LOG(LogTemp, Display, TEXT("Director"));
}







void AStarfallHeroController::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		const float DeadZone = 0.1f;
		if (Input.Size() > DeadZone)
		{
			HeroPawn->Move(Input);
		}
	}
}

void AStarfallHeroController::StartSprint() //const FInputActionValue& Value)
{
	//	FVector Input = Value.Get<FVector>();

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->Sprint();
	}
}

void AStarfallHeroController::StopSprint()
{
	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->StopSprinting();
	}
}

void AStarfallHeroController::Look(const FInputActionValue& Value)
{
	
	bool bIsLookInverted = false;

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		FVector2D Input = Value.Get<FVector2D>();
		
		const float DeadZone = 0.1f;
		

		if (Input.Size() > DeadZone)
		{
			if (!bIsLookInverted) {
				Input.Y *= -1;

				HeroPawn->Look(Input);
			}
			else {
				//	By default, vertical input (Y-Axis) is inverted. We will not change this
				Input.X *= -1;	//	Invert horizontal input (X-Axis)
			}
		}
	}
}


void AStarfallHeroController::StartCrouch(const FInputActionValue& Value)
{
	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->StartCrouch();
	}
}

void AStarfallHeroController::StopCrouch()
{
	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->StopCrouch();
	}

}


void AStarfallHeroController::StartJump(const FInputActionValue& Value)
{

	FVector Input = Value.Get<FVector>();

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->StartJump(Input);
		//	UE_LOG(LogTemp, Display, TEXT("Jumping"));
	}
}


void AStarfallHeroController::StopJump()
{
	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->StopJump();
	}
}



void AStarfallHeroController::AimWeapon(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Aiming"));
}

void AStarfallHeroController::StopAimWeapon()
{
	UE_LOG(LogTemp, Display, TEXT("Stop aiming"));
}


void AStarfallHeroController::FireWeapon(const FInputActionValue& Value)
{
	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		if (HeroPawn->Arsenal)
		{
			//	if (HeroPawn->Arsenal->ActiveWeapon)
			//	{
			//		HeroPawn->Arsenal->ActiveWeapon->ShootWeapon();
			//	}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No arsenal component found."));
		}
	}
}

void AStarfallHeroController::StopFireWeapon()
{
	UE_LOG(LogTemp, Display, TEXT("Stop firing"));
}
	





//	Our switch weapon members should not know about the logic within Arsenal Component,
//	instead, we should just determine if we are tapping or holding the input
//	and pass the result to arsenal component to handle the logic


void AStarfallHeroController::SwitchWeapon(const FInputActionValue& Value)
{
	bIsSwitchWeaponInputHeld = false;	//	reset the flag
	//	UE_LOG(LogTemp, Display, TEXT("Switching weapon"));

	GetWorld()->GetTimerManager().SetTimer(HoldTimerHandle, this, &AStarfallHeroController::OnWeaponSwitchHoldDetected, HoldThreshold, false);
}


void AStarfallHeroController::StopSwitchWeapon()
{
	if (!bIsSwitchWeaponInputHeld)
	{
		if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
		{
			//	if (HeroPawn->Arsenal)
			//	{
			//		HeroPawn->Arsenal->SwitchActiveWeapon(
			//			HeroPawn->Arsenal->NextSlotIndex
			//		);
			//	}
			//	else {
			//		UE_LOG(LogTemp, Warning, TEXT("No arsenal component found."));
			//	}
		}
	}
	GetWorld()->GetTimerManager().ClearTimer(HoldTimerHandle);
}

void AStarfallHeroController::OnWeaponSwitchHoldDetected()
{
	bIsSwitchWeaponInputHeld = true;

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		//	if (HeroPawn->Arsenal)
		//	{
		//		HeroPawn->Arsenal->SwitchActiveWeapon(2);
		//	}
		//	else {
		//		UE_LOG(LogTemp, Warning, TEXT("No arsenal component found."));
		//	}
	}
}



/*



void AStarfallHeroCharacter::StartJump(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();

	Super::StartJump(Input);
}

void AStarfallHeroCharacter::StopJump()
{
	Super::StopJump();
	Super::OnLiftJumpActivated.Unbind();
}

void AStarfallHeroCharacter::Landed(const FHitResult& Hit)
{
	//	We will extrapolate this to a variable the entire class can see/edit once we get this member working

	Super::Landed(Hit);

	//	_EnhancedInputComponent->RemoveActionBindingForHandle();	//	 myActionBinding.GetHandle());
}

void AStarfallHeroCharacter::StartLiftJump(const FInputActionValue& Value)
{
	//	FVector Input = Value.Get<FVector>();
	//	Super::StartLiftJump(Input);


	Super::StartLiftJump();
	Super::OnLiftJumpActivated.BindUObject(this, &AStarfallCharacter::ApplyLiftForce);

	//	UE_LOG(LogTemp, Display, TEXT("Lift jumping now boys"));
}
*/