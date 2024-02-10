// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/StarfallWeapon.h"
#include "StarfallInventoryManager.generated.h"

/*
// Weapon details structure
USTRUCT(BlueprintType)
struct FWeaponDetails
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name; // Consider using ID instead for referencing DataTable

    // Add other weapon properties like damage, customization options, etc.
};

// Slot structure containing an array of weapons
USTRUCT(BlueprintType)
struct FInventoryWeaponSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FWeaponDetails> Weapons;
};
*/






USTRUCT(BlueprintType)
struct FInventoryWeapon
{
	GENERATED_BODY()
	FString Name;
	int32 ID;
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	FString Name;  // Consider using ID instead for referencing DataTable
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FInventoryLoot
{
	GENERATED_BODY()
	FString Name;  // Consider using ID instead for referencing DataTable
};


UCLASS()
class STARFALL_API UStarfallInventoryManager : public UObject
{
	GENERATED_BODY()
	
public:
    UStarfallInventoryManager();
	void Init();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FInventoryWeapon> PrimaryWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FInventoryWeapon> SpecialWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FInventoryWeapon> HeavyWeapons;

	//	ITEMS:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<FInventoryItem> Consumables;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<FInventoryItem> Crafting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<FInventoryLoot> Loot;





	void FetchInventoryFromServer();
	void PushInventoryToServer();

	void SerializeInventory();
	void DeserializeInventory();
};