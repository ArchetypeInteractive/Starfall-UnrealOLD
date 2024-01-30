// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/StarfallCharacter.h"
#include "Character/Component/Inventory/StarfallInventoryComponent.h"
#include "Character/Component/Radar/StarfallRadarComponent.h"
#include "Logging/LogMacros.h"
#include "EnhancedInputComponent.h"
#include "StarfallHeroCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//	DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS()
class STARFALL_API AStarfallHeroCharacter : public AStarfallCharacter
{
	GENERATED_BODY()


	/** Camera boom positioning the camera behind the character */
	//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStarfallInventoryComponent> Inventory;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Radar, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStarfallRadarComponent> Radar;



	


public:
	AStarfallHeroCharacter();



private:

	//	FInputActionBindingHandle LiftStartBindingHandle;
	//	FInputActionBindingHandle LiftStopBindingHandle;


protected:
	virtual void BeginPlay();
	//	APawn interface
	//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	//	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; };
	FORCEINLINE class UStarfallInventoryComponent* GetInventory() const { return Inventory; };
	FORCEINLINE class UStarfallRadarComponent* GetRadar() const { return Radar; };
};
