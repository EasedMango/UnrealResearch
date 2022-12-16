// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssignmentOneGameMode.h"
#include "AssignmentOneCharacter.h"
#include "PlayerHud.h"
#include "UObject/ConstructorHelpers.h"
#include "Target.h"
#include "TP_WeaponComponent.h"

#include "Kismet/GameplayStatics.h"

void AAssignmentOneGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerControllerList.Add(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PLAYER HAS JOINED"));
}

AAssignmentOneGameMode::AAssignmentOneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = APlayerHud::StaticClass();
	Pause = true;
	CountdownTime = 15;
	Hits = 0;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), Targets);

	for (int i = 0; i < Targets.Num(); ++i)
	{
		ATarget* TempTarget = Cast<ATarget>(Targets[i]);
		TempTarget->OnTargetHit.AddDynamic(this, &AAssignmentOneGameMode::AAssignmentOneGameMode::TargetHit);
	}
	// TArray<AActor*> Targets;
	// GetCom
	// UGameplayStatics::Get(GetWorld(),UTP_WeaponComponent::StaticClass(),Targets);
	// for (int i =0; i < Targets.Num(); ++i)
	// {
	// 	auto* TempTarget = Cast<UTP_WeaponComponent>(Targets[i]);
	// 	TempTarget->OnWeaponPickup.AddDynamic(this,&AAssignmentOneGameMode::StartGame);
	// 	
	// }
}

//FString& L(float CountdownTime);

void AAssignmentOneGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat( CountdownTime));
	if (!Pause)
	{
		CountdownTime -= CountdownTime <= 0 ? CountdownHasFinished() : DeltaSeconds;
		if (Score >= 10)
		{
			Pause = true;
			if (APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld())); MyPlayer != nullptr)
			{
				MyPlayer->SetPause(Pause);
			}
		}
	}

}



void AAssignmentOneGameMode::TargetHit()
{
	++Score;
	if (Pause)
	{
		Pause = false;
	}
	AddTimeToCountdown(5.0f);
}

void AAssignmentOneGameMode::StartGame()
{
	Pause = false;
}


float AAssignmentOneGameMode::CountdownHasFinished()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Over"));
	Pause = true;
	return 0;
}

void AAssignmentOneGameMode::HitTime(const float& Time)
{
}
