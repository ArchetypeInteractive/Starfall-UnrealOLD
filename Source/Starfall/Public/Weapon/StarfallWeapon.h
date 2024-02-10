// AWeapon.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Blueprint/UserWidget.h"
//  #include <AbilitySystemComponent.h>
#include "StarfallWeapon.generated.h"


UENUM(BlueprintType)
enum class EFiringType : uint8
{
    Single UMETA(DisplayName = "Single"),
    Burst UMETA(DisplayName = "Burst"),
    Auto UMETA(DisplayName = "Auto"),
    Charge UMETA(DisplayName = "Charge")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    AutoRifle UMETA(DisplayName = "Auto Rifle"),
    ScoutRifle UMETA(DisplayName = "Scout Rifle"),
    PulseRifle UMETA(DisplayName = "Pulse Rifle"),
    HandCannon UMETA(DisplayName = "Hand Cannon"),
    SubmachineGun UMETA(DisplayName = "Submachine Gun"),
    Sidearm UMETA(DisplayName = "Sidearm"),
    SniperRifle UMETA(DisplayName = "Sniper Rifle"),
    Shotgun UMETA(DisplayName = "Shotgun"),
    FusionRifle UMETA(DisplayName = "Fusion Rifle"),
    RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
    GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
    Sword UMETA(DisplayName = "Sword"),
    TraceRifle UMETA(DisplayName = "Trace Rifle"),
    LinearFusionRifle UMETA(DisplayName = "Linear Fusion Rifle"),
    Bow UMETA(DisplayName = "Bow")
};

UENUM(BlueprintType)
enum class EWeaponArchetype : uint8
{
    Precision UMETA(DisplayName = "Precision"),         // Focuses on accuracy and range.
    Aggressive UMETA(DisplayName = "Aggressive"),       // Focuses on high damage output at the cost of stability or rate of fire.
    Adaptive UMETA(DisplayName = "Adaptive"),           // Offers a balance between damage, stability, and rate of fire.
    RapidFire UMETA(DisplayName = "Rapid Fire"),        // Enhances rate of fire and reload speed at the cost of damage per shot.
    Lightweight UMETA(DisplayName = "Lightweight"),     // Offers mobility bonuses and faster handling.
    HighImpact UMETA(DisplayName = "High Impact"),      // Maximizes damage per shot at the cost of rate of fire and recoil control.
    // Additional archetypes as needed
};


USTRUCT(BlueprintType)
struct FReticle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reticle")
	UUserWidget* ReticleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reticle")
	UTexture2D* ReticleTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reticle")
	FLinearColor ReticleColor;
};


UCLASS()
class STARFALL_API AStarfallWeapon : public AActor //, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AStarfallWeapon();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EWeaponType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EFiringType FiringType;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EWeaponArchetype Archetype;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
    bool bIsReloading;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
    FReticle Reticle;

    // Common properties
    //  ----------------
    //  TO DO: CLAMP! (0.0f - 100.0f)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handling")
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handling")
    int32 AimAssist;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handling")
    int32 ReloadSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handling")
    float RateOfFire;





    // TAGS
    //  FGameplayTag FiringTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Weapon.Firing"));
    //  FGameplayTag AimingTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Weapon.Aiming"));
    //  FGameplayTag ReloadingTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Weapon.Reloading"));;


    //  AMMO ECONOMY
    //  ----------------
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoCapacity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    int32 CurrentAmmo;


    // Enums for element and weapon type to be defined

    // Effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effects")
    USoundBase* FiringSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effects")
    UParticleSystem* MuzzleFlash;

    // Weapon functionality
    virtual void AimWeapon();
    virtual void ShootWeapon();
    virtual void StopShootWeapon();
    virtual void ReloadWeapon();





protected:
    //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    //  UAbilitySystemComponent* AbilitySystemComponent;
};
