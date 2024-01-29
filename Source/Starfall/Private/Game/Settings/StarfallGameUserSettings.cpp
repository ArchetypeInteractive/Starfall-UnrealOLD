// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Settings/StarfallGameUserSettings.h"

UStarfallGameUserSettings::UStarfallGameUserSettings()
{

}


void UStarfallGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
    //  Super::ApplySettings(bCheckForCommandLineOverrides);

    //  Apply your custom settings here
    //  For example, you can broadcast a delegate or event that your input handling system listens to

    //  Example: Broadcast a delegate/event
    //  OnSensitivityChanged.Broadcast(LookSensitivityX, LookSensitivityY);
}

void UStarfallGameUserSettings::SetLookSensitivity(FVector2D NewSensitivity)
{
    Settings.Look.Sensitivity = NewSensitivity;
    SaveSettings();
}



void UStarfallGameUserSettings::LoadSettings()
{
    UE_LOG(LogTemp, Display, TEXT("LOADING USER SETTINGS"));
    LoadConfig();

    this->ApplySettings(false);
}