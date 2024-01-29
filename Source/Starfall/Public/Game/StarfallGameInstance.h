// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/Delegate.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "NakamaUnreal.h"
#include "NakamaClient.h"
#include "NakamaSession.h"
#include "NakamaRealtimeClient.h"
#include "Game/Settings/StarfallGameUserSettings.h"
#include "StarfallGameInstance.generated.h"

/**
 * 
 */





USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

	// Add character-specific properties here
	// For example:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Name;

	// ... other properties like Level, Class, etc.
};

USTRUCT(BlueprintType)
struct FCharactersData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	TArray<FCharacterData> Characters;
};


UCLASS()
class STARFALL_API UStarfallGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init() override;

	UPROPERTY()
	UNakamaClient* NakamaClient;

	UPROPERTY()
	UNakamaSession* NakamaSession;

	UPROPERTY()
	UNakamaRealtimeClient* NakamaRtClient;




	UPROPERTY()
	UNakamaRealtimeClient* NakamaRealtimeClient;

	UFUNCTION(BlueprintCallable)
	void AuthenticatePlayer();

	UFUNCTION(BlueprintCallable)
	void OnAuthenticationSuccess(UNakamaSession* Session);
	UFUNCTION(BlueprintCallable)
	void OnAuthenticationError(const FNakamaError& Error);

	UFUNCTION(BlueprintCallable)
	void OnRealtimeClientConnectSuccess();
	UFUNCTION(BlueprintCallable)
	void OnRealtimeClientConnectError(const FNakamaRtError& ErrorData);

	// Event dispatched when authentication completes
	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	FOnError AuthenticationErrorDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Authentication")
	FOnAuthUpdate AuthenticationSuccessDelegate;








	UFUNCTION(BlueprintCallable, Category = "Character")
	void WriteCharacterData(const FCharacterData& CharacterData);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnWriteStorageObjectsSuccess(const FNakamaStoreObjectAcks& StorageObjectAcks);
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnWriteStorageObjectsError(const FNakamaError& Error);

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnStorageObjectAcks WriteStorageObjectsSuccessDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnError WriteStorageObjectsErrorDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnRealtimeClientConnected ConnectionSuccessDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnRealtimeClientConnectionError ConnectionErrorDelegate;




	UFUNCTION(BlueprintCallable)
	UNakamaClient* GetNakamaClient() const { return NakamaClient; }

	UFUNCTION(BlueprintCallable)
	UNakamaSession* GetNakamaSession() const { return NakamaSession; }


	UFUNCTION(BlueprintCallable)
	UNakamaRealtimeClient* GetNakamaRtClient() const { return NakamaRtClient; }



	UFUNCTION(BlueprintCallable)
	void LoadUserSettings();

	UPROPERTY()
	UStarfallGameUserSettings* UserSettings;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Auth")
	bool bIsAuthenticated;
};
