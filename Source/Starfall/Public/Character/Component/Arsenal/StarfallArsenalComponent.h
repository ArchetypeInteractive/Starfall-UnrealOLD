// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "Weapon/StarfallWeapon.h"
#include "StarfallArsenalComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWeapon, AStarfallWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReloadWeapon, AStarfallWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireWeapon, AStarfallWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipWeapon, AStarfallWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnequipWeapon, AStarfallWeapon*, Weapon);


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

    //  ----------------------------------------
    //  EVENT DELEGATES
    //  ----------------------------------------
    
    //  Delegate instance for broadcasting weapon switch events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSwitchWeapon OnSwitchWeapon;

    //  Delegate instance for broadcasting weapon reload events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnReloadWeapon OnReloadWeapon;

    //  Delegate instance for broadcasting weapon fire events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFireWeapon OnFireWeapon;
    
    //  Delegate instance for broadcasting weapon equip events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnEquipWeapon OnEquipWeapon;
    
    //  Delegate instance for broadcasting weapon unequip events
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUnequipWeapon OnUnequipWeapon;
    //  ----------------------------------------


    //  ----------------------------------------
    //  SLOT INDEX MANAGEMENT
    //  ----------------------------------------

    int32 SlotIndex_Active = 0;
    int32 SlotIndex_Previous = 0;
    int32 SlotIndex_Next = 0;
    //  ----------------------------------------
    









    //  ----------------------------------------
    //  WEAPON ACTIONS
    //  ----------------------------------------
    void FireWeapon();
    void ReloadWeapon();
    //  ----------------------------------------
    
    
    //  ----------------------------------------
    //  WEAPON MANAGEMENT
    //  ----------------------------------------

    void SwapActiveSlot(bool bIsLongPress);     //  if no long press, toggle between index 0 and 1. If long press,interject 2 in 0-1 toggle sequence.
    //  void SwapWeaponWithinSlot(int32 OldWeaponIndex, int32 NewWeaponIndex);

    //  ----------------------------------------
    //  HELPERS
    //  ----------------------------------------
    void SpawnWeaponFromSlot();
    void ScrapWeaponForParts();

    //  Upload weapon arrangement to Nakama
    void SaveWeaponsToNakama();
	void LoadWeaponsFromNakama();
    //  ----------------------------------------












    //  
    //  void SwitchActiveWeapon(int32 NewActiveSlotIndex);
    //  void SpawnWeapon();
    //  
    //  AStarfallWeapon* ActiveWeapon;
    //  TSubclassOf<AStarfallWeapon> ActiveWeaponClass;
    //  
    //  
    //  UFUNCTION(BlueprintCallable)
    //  AStarfallWeapon* GetActiveWeapon() const { return ActiveWeapon ? ActiveWeapon : nullptr; };
    //  
    //  
    //  // Additional methods as needed...
    //  // Define weapon slot structure
    //  
    //  //  Weapon slots
    //  //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  //  TArray<AStarfallWeapon*> PrimaryWeapons;
    //  //  
    //  //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  //  TArray<AStarfallWeapon*> SpecialWeapons;
    //  //  
    //  //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  //  TArray<AStarfallWeapon*> HeavyWeapons;
    //  
    //  
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    //  int32 ActiveWeaponSlotIndex;
    //  
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Slots")
    //  TArray<FWeaponSlot> WeaponSlots;
    //  
    //  
    //  
    //  TSubclassOf<AStarfallWeapon> EquippedPrimaryWeaponClass;

};
