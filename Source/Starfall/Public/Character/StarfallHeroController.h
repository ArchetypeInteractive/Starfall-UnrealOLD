// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "StarfallHeroController.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class STARFALL_API AStarfallHeroController : public APlayerController
{
	GENERATED_BODY()
	

	//	Camera system:
	//	First person camera, third person camera


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MenuInput, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MenuMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MenuInput, meta = (AllowPrivateAccess = "true"))
	UInputAction* DirectorAction;
























	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> GameplayMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	
	//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<UInputAction> LiftAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayInput, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	//	UEnhancedInputComponent* _EnhancedInputComponent;
	

	//	/** Camera boom positioning the camera behind the character */
	//	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	//	USpringArmComponent* CameraBoom;
		
	//	/** Follow camera */
	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	
	
	
	
//	/** Leave Activity Input Action */
	//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//	UInputAction* LeaveActivityAction;


public:
	AStarfallHeroController();


	//	MENU CONTEXT:		INPUT ACTIONS
	//	void LeaveActivity(const FInputActionValue& Value);
	//	
	//	
	//	
	//	GAMEPLAY CONTEXT:	INPUT ACTIONS
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Director();
	void StartJump(const FInputActionValue& Value);
	void StopJump();
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouch();
	void StartSprint();	// const FInputActionValue& Value);
	void StopSprint();
	//	void StartLiftJump(const FInputActionValue& Value);
	//	void Landed(const FHitResult& Hit);




	void SwitchContext(UInputMappingContext* MappingContext);


protected:
	virtual void BeginPlay();
	//	APawn interface
	virtual void SetupInputComponent();
};
