// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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



struct FRadarSection
{
    int32 ActorCount = 0;
    // Add other properties as needed (e.g., visibility status)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrackedActorsUpdated);

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

    //  FVector GetTrackedActorLocation(AActor* TrackedActor);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Capsule")
    float Radius;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
    float Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
    float Sections = 6;








    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
    TArray<FName> TrackedTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackedActors")
    TArray<AActor*> TrackedActors;

    UPROPERTY(BlueprintAssignable, Category = "Radar")
    FOnTrackedActorsUpdated OnTrackedActorsUpdated;

protected:
    virtual void BeginPlay() override;

private:
    
    //  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackedActors")
    FTimerHandle UpdateTimerHandle;

    float UpdateInterval = 0.1f;  // Update interval in seconds


    UFUNCTION(BlueprintCallable)
    void UpdateTrackedActors();

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* EnemyActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    UFUNCTION()
    void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* EnemyActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};