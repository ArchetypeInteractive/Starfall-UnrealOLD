// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "StarfallGameUserSettings.generated.h"



USTRUCT(BlueprintType)
struct FResolutionPrefs
{
    GENERATED_BODY()

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Resolution")
    int32 Width;

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Resolution")
    int32 Height;

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Resolution")
    bool bIsFullscreen;

};


USTRUCT(BlueprintType)
struct FLookPrefs
{
    GENERATED_BODY()

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Look")
    FVector2D Sensitivity;

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Look")
    FVector2D Deadzone;

};

USTRUCT(BlueprintType)
struct FUserPrefs
{
    GENERATED_BODY()

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FLookPrefs Look;

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FResolutionPrefs Resolution;

};




UCLASS()
class STARFALL_API UStarfallGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()


public:
    UStarfallGameUserSettings();

    UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Look")
    FUserPrefs Settings;






    UPROPERTY(config)
    float LookSensitivityX;

    UPROPERTY(config)
    float LookSensitivityY;

    virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

    void SetLookSensitivity(FVector2D NewSensitivity);
    FVector2D GetLookSensitivity() const { return Settings.Look.Sensitivity; };

    void LoadSettings();
};
