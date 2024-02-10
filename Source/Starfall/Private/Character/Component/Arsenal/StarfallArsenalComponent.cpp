// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Arsenal/StarfallArsenalComponent.h"
#include "Weapon/StarfallWeapon.h"
#include <Character/StarfallCharacter.h>


UStarfallArsenalComponent::UStarfallArsenalComponent()
{

    //  Set the initial active slot to the primary slot
    //  ActiveSlot = PrimarySlot;
}

void UStarfallArsenalComponent::BeginPlay()
{
    Super::BeginPlay();




    //  Our Arsenal Component is only relevant when 
    //  the player character is actually spawned in world.
    // 
    // 
	//  When this component is activated,
    //  -   Read player's inventory.WeaponSlots
    //  -   Spawn each weapon in slot[0] from the inventory
    //      -   slot[0] = PrimarySlot, socket = "ik_hand_gun"
    //      -   slot[1] = SpecialSlot, socket = "wa_back_gun"
    //      -   slot[2] = HeavySlot, socket = "wa_back_gun"

}




void UStarfallArsenalComponent::SwapActiveSlot(bool bIsLongPress)
{

    if (!bIsLongPress)
    {
        UE_LOG(LogTemp, Display, TEXT("Toggle between 0-1 weapons"));
    }
    else {
        UE_LOG(LogTemp, Display, TEXT("Switch to heavy weapon"));
    }
}




























































    //  AStarfallCharacter* Owner = Cast<AStarfallCharacter>(GetOwner());
    //  if (!Owner || !Owner->GetMesh()) { return; };






















    //  ActiveSlot = PrimarySlot;




    //  Example spawn info for initial weapons, assuming you have a way to define these (e.g., as properties, data assets, etc.)
    //  TSubclassOf<AStarfallWeapon> InitialPrimaryWeaponClass; // Set this based on your game's logic or data
    //  TSubclassOf<AStarfallWeapon> InitialSpecialWeaponClass;
    //  TSubclassOf<AStarfallWeapon> InitialHeavyWeaponClass;

    //  Spawn and attach the initial Primary weapon
    //  if (ActiveSlot.Weapons.Num() > 0)
    //  {
    //      UE_LOG(LogTemp, Display, TEXT("We have weapons in our arsenal, now we need to spawn them."));
    //      //  SpawnAndAttachWeapon(ActiveSlot.Weapons[0], "ik_hand_gun", PrimarySlot);
    //  }

    //  Spawn and attach the initial Special weapon
    //  SpawnAndAttachWeapon(InitialSpecialWeaponClass, "wa_back_gun", SpecialSlot);

    //  Spawn and attach the initial Heavy weapon
    //  SpawnAndAttachWeapon(InitialHeavyWeaponClass, "wa_back_gun", HeavySlot);

    //  Set the initial active weapon (if any)
    //  This is just an example; your game might start with the primary weapon active
    //  ActiveSlot = PrimarySlot;
    //  if (PrimarySlot.Weapons.Num() > 0)
    //  {
    //      PrimarySlot.Weapons[0]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ik_hand_gun"));
    //  }

/*
void UStarfallArsenalComponent::SwitchActiveWeapon(int32 NewActiveSlotIndex)
{
    //  PreviousSlotIndex = ActiveSlotIndex;
    //  
    //  // Determine the next slot index based on current and previous slots
    //  int32 PotentialNextSlotIndex = NewActiveSlotIndex; // This is the initially intended next slot index
    //  switch (NewActiveSlotIndex)
    //  {
    //  case 0:
    //      PotentialNextSlotIndex = 1;
    //      break;
    //  case 1:
    //      PotentialNextSlotIndex = 0;
    //      break;
    //  case 2:
    //      if (PreviousSlotIndex == 0) {
    //          PotentialNextSlotIndex = 1;
    //      }
    //      else if (PreviousSlotIndex == 1) {
    //          PotentialNextSlotIndex = 0;
    //      }
    //      break;
    //  }
    //  
    //  // Check if the intended next slot has weapons. If not, keep the current active slot.
    //  if (WeaponSlots.IsValidIndex(PotentialNextSlotIndex) && !WeaponSlots[PotentialNextSlotIndex].Weapons.IsEmpty())
    //  {
    //      // Valid slot with weapons found, proceed to switch
    //      ActiveSlotIndex = PotentialNextSlotIndex;
    //      AStarfallWeapon* NewActiveWeapon = WeaponSlots[ActiveSlotIndex].Weapons[0];
    //      if (NewActiveWeapon)
    //      {
    //          // If there's a valid weapon in the slot, broadcast the switch and update the active weapon
    //          OnSwitchWeapon.Broadcast(NewActiveWeapon);
    //      }
    //  }
    //  else
    //  {
    //      // No valid weapons in the next slot, optionally handle this case (e.g., log, error, or default action)
    //      UE_LOG(LogTemp, Warning, TEXT("No weapons in the next slot %d, skipping switch."), PotentialNextSlotIndex);
    //  }
    //  
    //  UE_LOG(LogTemp, Display, TEXT("Previous Slot Index: %d, New Active Slot Index: %d"), PreviousSlotIndex, ActiveSlotIndex);
    //  
    //  
    //  
    //  SpawnWeapon();

}






void UStarfallArsenalComponent::SpawnWeapon()
{
    if (!ActiveWeaponClass) return; // Ensure the Blueprint class is set

    AActor* Owner = GetOwner();
    if (!Owner) return; // Ensure there's an owner to attach to

    // Get the world from the owner
    UWorld* World = Owner->GetWorld();
    if (!World) return;

    // Define spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Spawn the weapon actor
    AStarfallWeapon* SpawnedWeapon = World->SpawnActor<AStarfallWeapon>(ActiveWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

    if (SpawnedWeapon)
    {
        // Attach the spawned weapon to the owner
        SpawnedWeapon->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

        // Optionally, configure the spawned weapon further, such as setting it as the active weapon
    }
}

*/
















/*
void UStarfallArsenalComponent::EquipWeaponToSlot(AStarfallWeapon* Weapon, const FString& SlotName)
{

    //  AActor* Owner = GetOwner();
    //  if (!Owner) return;
    //  
    //  // Assuming Owner is of a character class that has an ability system component
    //  UAbilitySystemComponent* ASC = Cast<IAbilitySystemInterface>(Owner)->GetAbilitySystemComponent();
    //  if (!ASC) return;

    // Example of granting a fire ability when a weapon is equipped
    //  FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(
    //      FGameplayAbilitySpec(Weapon->GetFireAbilityClass(), 1, INDEX_NONE, Owner)
    //  );

    // Store the handle if needed for later removal or reference
    //  CurrentWeaponFireAbilityHandle = Handle;

    // Similar logic can be applied to grant reload, aim, or any other weapon-specific abilities
}

void UStarfallArsenalComponent::SwapActiveSlot(const FString& SlotName)
{
    //  if (SlotName == "Primary")
    //  {
	//  	ActiveSlot = PrimarySlot;
    //      ActiveWeapon = PrimarySlot.Weapons[0];
	//  }
    //  else if (SlotName == "Special")
    //  {
	//  	ActiveSlot = SpecialSlot;
    //      ActiveWeapon = SpecialSlot.Weapons[0];
	//  }
    //  else if (SlotName == "Heavy")
    //  {
	//  	ActiveSlot = HeavySlot;
    //      ActiveWeapon = HeavySlot.Weapons[0];
	//  }
}


void UStarfallArsenalComponent::SwapWeaponWithinSlot(const FString& SlotName, int32 NewWeaponIndex)
{
    //  FWeaponSlot TargetSlot = nullptr;

    // Detach the currently equipped weapon in the active slot, if any
    //  if (AStarfallWeapon* CurrentlyEquippedWeapon = ActiveWeapon)
    //  {
    //      CurrentlyEquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    //      // Attach it to the stowing socket based on its slot
    //      FString StowSocket = (ActiveSlot == &PrimarySlot) ? "wa_hip_gun" : "wa_back_gun";
    //      CurrentlyEquippedWeapon->AttachToComponent(GetOwner()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(*StowSocket));
    //  }

    //  Attach the new weapon to the 'ik_hand_gun' socket
    //  AStarfallWeapon* NewWeapon = TargetSlot->Weapons[NewWeaponIndex];
    //  NewWeapon->AttachToComponent(CharacterMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ik_hand_gun"));
    //  
    //  // Update the internal state to reflect the new equipped weapon
    //  TargetSlot->Weapons.Swap(0, NewWeaponIndex);
}




void UStarfallArsenalComponent::SpawnAndAttachWeapon(TSubclassOf<AStarfallWeapon> WeaponClass, const FString& SocketName, FWeaponSlot& Slot)
{
    if (!WeaponClass || !GetOwner()) return;
    
    AStarfallWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AStarfallWeapon>(WeaponClass);
    if (!SpawnedWeapon) return;
    
    SpawnedWeapon->AttachToComponent(Cast<AStarfallCharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(*SocketName));
    
    //  Add the weapon to the specified slot
    //  Slot.Weapons.Add(SpawnedWeapon);
}
*/




/*
void UStarfallArsenalComponent::SwitchWeapon(FString Slot)
{
    // Logic to switch between equipped weapons
}

void UStarfallArsenalComponent::FireCurrentWeapon()
{
    if (ActiveWeapon)
    {
        ActiveWeapon->ShootWeapon();
    }
}

void UStarfallArsenalComponent::ReloadCurrentWeapon()
{
    if (ActiveWeapon)
    {
        ActiveWeapon->Reload();
    }
}
*/



// Implement vault interaction functions as needed
