// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "Weapon/StarfallWeapon.h"
#include "StarfallArsenalComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWeapon, AStarfallWeapon*, Weapon);
//  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReloadWeapon, AStarfallWeapon*, Weapon);
//  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireWeapon, AStarfallWeapon*, Weapon);
//  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipWeapon, AStarfallWeapon*, Weapon);
//  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnequipWeapon, AStarfallWeapon*, Weapon);


USTRUCT(BlueprintType)
struct FWeaponSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    TArray<AStarfallWeapon*> Weapons; 
};



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STARFALL_API UStarfallArsenalComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStarfallArsenalComponent();
    virtual void BeginPlay() override;

protected:
    // Define weapon slot structure

    //  Weapon slots
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  TArray<AStarfallWeapon*> PrimaryWeapons;
    //  
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  TArray<AStarfallWeapon*> SpecialWeapons;
    //  
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  TArray<AStarfallWeapon*> HeavyWeapons;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    int32 ActiveWeaponSlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    TArray<FWeaponSlot> WeaponSlots;








public:
    // Delegate instance for broadcasting weapon switch events
    UPROPERTY(BlueprintAssignable, Category = "Weapon")
    FOnSwitchWeapon OnSwitchWeapon;

    int32 ActiveSlotIndex = 0;
    int32 PreviousSlotIndex = 0;
    int32 NextSlotIndex = 0;

    void SwitchActiveWeapon(int32 NewActiveSlotIndex);
    void SpawnWeapon();
    AStarfallWeapon* ActiveWeapon;
    TSubclassOf<AStarfallWeapon> ActiveWeaponClass;
    
    
    UFUNCTION(BlueprintCallable)
    AStarfallWeapon* GetActiveWeapon() const { return ActiveWeapon ? ActiveWeapon : nullptr; };


    // Additional methods as needed...
};
