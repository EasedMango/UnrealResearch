// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

UNetworkGameInstance::UNetworkGameInstance()
{
}
void Print(const FString& message){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, message); }
void UNetworkGameInstance::Init()
{
	Super::Init();
	Print("Init started");
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		Print("Subsystem");
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			Print("SessionInterface");
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this, &UNetworkGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
				this, &UNetworkGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(
				this, &UNetworkGameInstance::OnJoinSessionComplete);
		}
	}
}

void UNetworkGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	Print("OnCreateSessionComplete");
	if (Succeeded)
	{
		Print("Succeeded");
		GetWorld()->ServerTravel("/Game/OptitrackTestMap?listen");
	}
}

void UNetworkGameInstance::OnFindSessionComplete(bool Succeeded)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnFindSessionComplete"));
	if (Succeeded)
	{
		Print("Succeeded");
		if(TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults; SearchResults.Num())
		{
			SessionInterface->JoinSession(0,FName("Network Test Session"),SearchResults[0]);
		}
	}
}

void UNetworkGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnJoinSessionComplete"));
	if(APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		FString JoinAddress = "";
		Print("PlayerController");
		SessionInterface->GetResolvedConnectString(SessionName,JoinAddress);
		if(JoinAddress !="")
		{
			PController->ClientTravel(JoinAddress,ETravelType::TRAVEL_Absolute);
			Print("JoinAddress");
		}
	}
	
}

void UNetworkGameInstance::CreateServer()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CreateServer"));
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
	FOnlineSessionSettings SessionSettings;

	SessionSettings.bAllowJoinInProgress = true;

	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionInterface->CreateSession(0, FName("Network Test Session"), SessionSettings);
}

void UNetworkGameInstance::JoinServer()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JoinServer"));
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery=true;

	SessionSearch->MaxSearchResults = 1000;

	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE",true,EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());

	
}
