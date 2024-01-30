// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Enemy/StarfallEnemyCharacter.h"
#include "StarfallRadarComponent.generated.h"




USTRUCT(BlueprintType)
struct FStarfallRadarData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    AActor* TrackedActor;

    UPROPERTY(BlueprintReadOnly)
    FVector RelativePosition;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STARFALL_API UStarfallRadarComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStarfallRadarComponent();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
    TSubclassOf<AActor> TargetActorClass;

    UPROPERTY(BlueprintReadOnly, Category = "Radar")
    TArray<FStarfallRadarData> RadarData;

    FVector GetTrackedActorLocation(AActor* TrackedActor);

    float Radius;
    float Height;

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle UpdateTimerHandle;
    float UpdateInterval = 0.5f;  // Update interval in seconds

    TArray<AStarfallEnemyCharacter*> TrackedActors;
    void UpdateTrackedActors();

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* EnemyActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* EnemyActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};