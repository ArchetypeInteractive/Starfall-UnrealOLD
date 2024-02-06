// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/StarfallHeroCharacter.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


//	DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AStarfallHeroCharacter::AStarfallHeroCharacter()
{
	// rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;	//  Lets us look up and down
	bUseControllerRotationRoll = false;



	//	Create a camera boom (pulls in towards the player if there is a collision)
	//	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//	CameraBoom->SetupAttachment(RootComponent);
	//	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//	Create a follow camera
	//	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//	FirstPersonCamera->SetupAttachment(GetMesh(), "head");
	//	FirstPersonCamera->SetRelativeLocation(FVector(7.0f, 24.0f, 0.0f));
	//	FirstPersonCamera->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
	//	FirstPersonCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
	//	Create a follow camera


	Arsenal = CreateDefaultSubobject<UStarfallArsenalComponent>(TEXT("Arsenal"));


	//	StarfallInventoryComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//	AbilitySystem = CreateDefaultSubobject<UStarfallAbilitySystemComponent>(TEXT("Ability System Component"));
	//	LiftAbilityClass = StarfallLiftAbility::StaticClass();
}

void AStarfallHeroCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Character is alive and well"));


	//	Add Input Mapping Context
	//	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//	{
	//		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//		{
	//			Subsystem->AddMappingContext(GameplayMappingContext, 0);
	//			Subsystem->AddMappingContext(MenuMappingContext, 0);
	//		}
	//	}
}