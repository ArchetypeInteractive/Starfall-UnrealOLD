// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/StarfallGameInstance.h"
#include <NakamaClient.h>
#include <NakamaRealtimeClient.h>

void UStarfallGameInstance::Init()
{
	Super::Init();

	//	Default Client Parameters
	FString ServerKey = TEXT("defaultkey");
	FString Host = TEXT("127.0.0.1");
	int32 Port = 7350;
	bool bUseSSL = false;
	bool bEnableDebug = true;

	// Setup Default Client
	NakamaClient = UNakamaClient::CreateDefaultClient(ServerKey, Host, Port, bUseSSL, bEnableDebug);
}

void UStarfallGameInstance::AuthenticatePlayer()
{
	// Implement authentication logic here
	// Example: NakamaClient->AuthenticateDevice(DeviceId, Username, ...);
	// On successful authentication, set bIsAuthenticated to true

	//	Authentication Parameters
	FString Email = TEXT("debug@mail.com");
	FString Password = TEXT("verysecretpassword");
	FString Username = TEXT("exo");
	TMap<FString, FString> Variables;


	AuthenticationSuccessDelegate.AddDynamic(this, &UStarfallGameInstance::OnAuthenticationSuccess);
	AuthenticationErrorDelegate.AddDynamic(this, &UStarfallGameInstance::OnAuthenticationError);

	NakamaClient->AuthenticateEmail(Email, Password, Username, true, Variables, AuthenticationSuccessDelegate, AuthenticationErrorDelegate);
}


// Example methods in UStarfallGameInstance
void UStarfallGameInstance::OnAuthenticationSuccess(UNakamaSession* Session)
{
	// Handle successful authentication
	NakamaSession = Session;
	bIsAuthenticated = true;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Authenticated As %s"), *Session->SessionData.Username));

	// This is our realtime client (socket) ready to use
	NakamaRtClient = NakamaClient->SetupRealtimeClient();

	// Setup Delegates of same type and bind them to local functions
	ConnectionSuccessDelegate.AddDynamic(this, &UStarfallGameInstance::OnRealtimeClientConnectSuccess);
	ConnectionErrorDelegate.AddDynamic(this, &UStarfallGameInstance::OnRealtimeClientConnectError);


	// Remember to Connect
	bool bCreateStatus = true;
	NakamaRtClient->Connect(NakamaSession, bCreateStatus, ConnectionSuccessDelegate, ConnectionErrorDelegate);
}

void UStarfallGameInstance::OnAuthenticationError(const FNakamaError& Error)
{
	// Handle authentication error
	bIsAuthenticated = false;
}

void UStarfallGameInstance::OnRealtimeClientConnectSuccess()
{
	UE_LOG(LogTemp, Log, TEXT("Connected to realtime client"));
}
void UStarfallGameInstance::OnRealtimeClientConnectError(const FNakamaRtError& ErrorData)
{
	// Handle the real-time client connection error
}




void UStarfallGameInstance::WriteCharacterData(const FCharacterData& CharacterData)
{
	FString Json;
	FJsonObjectConverter::UStructToJsonObjectString(CharacterData, Json);

	FNakamaStoreObjectWrite WriteObject;
	WriteObject.Collection = "CharacterData";
	WriteObject.Key = "Characters";
	WriteObject.PermissionWrite = ENakamaStoragePermissionWrite::OWNER_WRITE;
	WriteObject.PermissionRead = ENakamaStoragePermissionRead::OWNER_READ;
	WriteObject.Value = Json;

	TArray<FNakamaStoreObjectWrite> StorageObjectsData = { WriteObject };

	WriteStorageObjectsSuccessDelegate.AddDynamic(this, &UStarfallGameInstance::OnWriteStorageObjectsSuccess);
	WriteStorageObjectsErrorDelegate.AddDynamic(this, &UStarfallGameInstance::OnWriteStorageObjectsError);


	NakamaClient->WriteStorageObjects(NakamaSession, StorageObjectsData, WriteStorageObjectsSuccessDelegate, WriteStorageObjectsErrorDelegate);
}

/* Delegate handlers */

void UStarfallGameInstance::OnWriteStorageObjectsSuccess(const FNakamaStoreObjectAcks& StorageObjectAcks)
{
	UE_LOG(LogTemp, Log, TEXT("Success writing storage object"));
}

void UStarfallGameInstance::OnWriteStorageObjectsError(const FNakamaError& Error)
{
	UE_LOG(LogTemp, Error, TEXT("Error writing storage object: %s"), *Error.Message);
}


void UStarfallGameInstance::LoadUserSettings()
{
	UserSettings = Cast<UStarfallGameUserSettings>(UGameUserSettings::GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->LoadSettings();
		//	return UserSettings;
	}
}