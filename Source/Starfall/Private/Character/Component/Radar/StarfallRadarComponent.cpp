// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Radar/StarfallRadarComponent.h"
#include "CoreMinimal.h"
#include "Character/StarfallCharacter.h"
#include "Components/CapsuleComponent.h"

//	Sets default values for this component's properties
UStarfallRadarComponent::UStarfallRadarComponent()
{
	//	Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	//	off to improve performance if you don't need them.
	//	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UStarfallRadarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &UStarfallRadarComponent::UpdateTrackedActors, UpdateInterval, true);

	AStarfallCharacter* Character = Cast<AStarfallCharacter>(GetOwner());
	if (Character)
	{
		// Create the capsule component for radar detection
		UCapsuleComponent* RadarCapsule = NewObject<UCapsuleComponent>(Character, UCapsuleComponent::StaticClass());
		if (RadarCapsule)
		{
			RadarCapsule->AttachToComponent(Character->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			RadarCapsule->SetCapsuleSize(Radius, Height);
			RadarCapsule->SetCollisionProfileName(TEXT("Radar"));

			// debugging:
			RadarCapsule->bHiddenInGame = false;
			// Other radar capsule configurations
	
			RadarCapsule->RegisterComponent(); // Don't forget to register the component

			RadarCapsule->OnComponentBeginOverlap.AddDynamic(this, &UStarfallRadarComponent::HandleBeginOverlap);
			RadarCapsule->OnComponentEndOverlap.AddDynamic(this, &UStarfallRadarComponent::HandleEndOverlap);
		}
	}

	
}

void UStarfallRadarComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !TrackedActors.Contains(OtherActor))
	{
		for (const FName& Tag : TrackedTags)
		{
			if (OtherActor->ActorHasTag(Tag))
			{
				TrackedActors.Add(OtherActor);
				UE_LOG(LogTemp, Display, TEXT("Actor within range, added to TrackedActors"));
				break; // Exit the loop once a matching tag is found
			}
		}
	}
}

void UStarfallRadarComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Same tag check as in BeginOverlap
	if (OtherActor)
	{
		TrackedActors.Remove(OtherActor);
		UE_LOG(LogTemp, Display, TEXT("Actor out of range, removed from TrackedActors"));
	}
}

void UStarfallRadarComponent::UpdateTrackedActors()
{
	RadarData.Empty();

	AActor* OwnerActor = GetOwner();
	if (OwnerActor && TrackedActors.Num() > 0)
	{
		FVector PlayerLocation = OwnerActor->GetActorLocation();
		FRotator PlayerRotation = OwnerActor->GetActorRotation();

		for (AActor* TrackedActor : TrackedActors)
		{
			if (TrackedActor)
			{
				FVector RelativePosition = TrackedActor->GetActorLocation() - PlayerLocation;

				UE_LOG(LogTemp, Display, TEXT("Enemy Detected"));
				
				//	Adjust based on player's rotation if the radar is orientation-sensitive
				RelativePosition = PlayerRotation.UnrotateVector(RelativePosition);
				
				RadarData.Add(FStarfallRadarData{ TrackedActor, RelativePosition });
				OnTrackedActorsUpdated.Broadcast();

				UE_LOG(LogTemp, Display, TEXT("TrackedActor Relative Position: %s"), *RelativePosition.ToString());
				
				// Now RelativePosition holds the position of the tracked actor relative to the player
				// This can be used to update the radar UI
			}
		}
	}
}