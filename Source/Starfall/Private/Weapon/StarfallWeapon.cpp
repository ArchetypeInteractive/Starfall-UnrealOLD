// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/StarfallWeapon.h"
#include "Kismet/GameplayStatics.h"
//  #include "AbilitySystemComponent.h"
//  #include "AbilitySystemInterface.h"

AStarfallWeapon::AStarfallWeapon()
{
    // Initialize default values
    Damage = 20.f; // Example default values
    Range = 1000.f;
    AmmoCapacity = 30;
    CurrentAmmo = AmmoCapacity;

    RateOfFire = 0.1f;


    //  AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}


void AStarfallWeapon::AimWeapon()
{
    //  aim down sights animation
    //  aiming sound
}


/*
void AStarfallWeapon::ShootWeapon()
{
    if (CurrentAmmo > 0)
    {
        // Implement firing logic, sound, and visual effects

        //  Muzzle flash,
        //  Firing sound,
        //  Ray trace to detect hit,
        //  Shell Ejection,
        //  Recoil animation (procedural?)
        //  Apply damage to hit actor

        --CurrentAmmo;
    }
    else
    {
        //  Play empty clip sound
        //  show indicator
    }
}
*/


void AStarfallWeapon::ShootWeapon()
{
    if (CurrentAmmo > 0 && !bIsReloading)
    {
        // Decrement ammo
        --CurrentAmmo;


        //  AbilitySystemComponent->AddLooseGameplayTag(FiringTag);


        // Apply procedural recoil or any firing effects
        // Spawn projectile or perform hitscan

        // Play firing sound
        if (FiringSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, FiringSound, GetActorLocation());
        }

        // Play muzzle flash
        if (MuzzleFlash)
        {
            UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetRootComponent());
        }

        // Implement rate of fire limitations
        // This could involve setting a timer that re-enables shooting after the rate of fire delay has passed
    }
    else if (CurrentAmmo <= 0)
    {
        ReloadWeapon(); // Auto-reload if out of ammo
    }
}




void AStarfallWeapon::StopShootWeapon()
{
    //  remove GameplayAbility.Weapon.Firing from tags
   //    AbilitySystemComponent->RemoveLooseGameplayTag(FiringTag);
}

void AStarfallWeapon::ReloadWeapon()
{
    //  Implement reload animation and sound
    //  Reload animation,
    //  Time this to the appropriate part of the animation:
    CurrentAmmo = AmmoCapacity;
    //  Play reload sound
    //  We want our player to be able to cancel the animation
    //  by firing, switching weapons or sprinting
}