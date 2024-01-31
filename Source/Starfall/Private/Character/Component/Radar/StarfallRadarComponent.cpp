// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Radar/StarfallRadarComponent.h"
#include "Character/StarfallHeroCharacter.h"
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

	AStarfallHeroCharacter* HeroCharacter = Cast<AStarfallHeroCharacter>(GetOwner());
	if (HeroCharacter)
	{
		// Create the capsule component for radar detection
		UCapsuleComponent* RadarCapsule = NewObject<UCapsuleComponent>(HeroCharacter, UCapsuleComponent::StaticClass());
		if (RadarCapsule)
		{
			RadarCapsule->AttachToComponent(HeroCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
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
	if (OtherActor && OtherActor->IsA(TargetActorClass) && !TrackedActors.Contains(OtherActor))
	{
		AStarfallEnemyCharacter* Enemy = Cast<AStarfallEnemyCharacter>(OtherActor);
		if (Enemy && !TrackedActors.Contains(Enemy))
		{
			TrackedActors.Add(Enemy);
			UE_LOG(LogTemp, Display, TEXT("Enemy within range, need to grab reference and add to TrackedActors"));
		}
	}
}

void UStarfallRadarComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(TargetActorClass))
	{
		AStarfallEnemyCharacter* EnemyActor = Cast<AStarfallEnemyCharacter>(OtherActor);
		TrackedActors.Remove(EnemyActor);
		UE_LOG(LogTemp, Display, TEXT("Removing enemy from TrackedActors, out of range"));
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
				//	RelativePosition = PlayerRotation.UnrotateVector(RelativePosition);
				
				RadarData.Add(FStarfallRadarData{ TrackedActor, RelativePosition });

				// Now RelativePosition holds the position of the tracked actor relative to the player
				// This can be used to update the radar UI
			}
		}
	}
}






// Called every frame
/*
void UStarfallRadarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/