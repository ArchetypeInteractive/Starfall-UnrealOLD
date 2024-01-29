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
			//	Subsystem->AddMappingContext(MenuMappingContext, 0);

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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::Look);
	


		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopJump);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopCrouch);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AStarfallHeroController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AStarfallHeroController::StopSprint);
	}





	//		//	EnhancedInputComponent->BindAction(DirectorAction, ETriggerEvent::Triggered, this, &AStarfallHeroController::Director);
	//	
	//	
	//		//	...
	//	
	//	
	//		//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AStarfallHeroCharacter::StartLiftJump);
	//	
	//		//	EnhancedInputComponent->BindAction(LiftAction, ETriggerEvent::Triggered, this, &AStarfallHeroCharacter::StartLiftJump);
	//		//	EnhancedInputComponent->BindAction(LiftAction, ETriggerEvent::Completed, this, &AStarfallHeroCharacter::StopJump);
	//	
	//		//	EnhancedInputComponent->BindAction(LeaveActivityAction, ETriggerEvent::Triggered, this, &AStarfallHeroCharacter::LeaveActivity);
	//	}
	//	else
	//	{
	//		//	UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	//	}
}
/*
*/








void AStarfallHeroController::SwitchContext(UInputMappingContext* InputMappingContext)
{
	UE_LOG(LogTemp, Display, TEXT("Switching context"))
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
		HeroPawn->UnCrouch();
	}

}


void AStarfallHeroController::StartJump(const FInputActionValue& Value)
{

	FVector Input = Value.Get<FVector>();

	if (AStarfallHeroCharacter* HeroPawn = Cast<AStarfallHeroCharacter>(GetPawn()))
	{
		HeroPawn->Jump();
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