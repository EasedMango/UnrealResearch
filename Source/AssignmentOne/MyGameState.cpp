// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "AssignmentOneCharacter.h"
#include "MyGameState.h"
#include "PlayerHud.h"
#include "UObject/ConstructorHelpers.h"
#include "Target.h"
#include "TP_WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyGameState, TeamAScore);
	DOREPLIFETIME(AMyGameState, TeamBScore);
}

AMyGameState::AMyGameState(): 
                              TeamAScore(0),
                              TeamBScore(0)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), Targets);

	for (int i = 0; i < Targets.Num(); ++i)
	{
		ATarget* TempTarget = Cast<ATarget>(Targets[i]);
		//TempTarget->OnTargetHit.AddDynamic(this, &AMyGameState::AddScore);
	}
}

void AMyGameState::AddScore(bool TeamAScored) {
	if(TeamAScored)
		TeamAScore++;
	else
		TeamBScore++;
}
void AMyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat( CountdownTime));


}



