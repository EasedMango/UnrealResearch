// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "Kismet/GameplayStatics.h"

void APlayerHud::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	FVector2d xy;
	GetWorld()->GetGameViewport()->GetViewportSize(xy);
	const FString Time("Time: ");//+FString::FromInt(GameMode->GetCountdownTime()));
	const FString Score("Score: ");//+FString::FromInt(GameMode->GetScore()));
	// if(GameMode->GetScore()>=10)
	// {
	// 	DrawRect(FLinearColor(1, 0, 0, 1), xy.X / 5, xy.Y / 10,750,200);
	// 	DrawText(FString("You've Won"), FLinearColor(1, 1, 1, 1), xy.X / 5, xy.Y / 6,0,2);
	// 	DrawText( Time, FLinearColor(1, 1, 1, 1), xy.X / 5, xy.Y / 4,0,2);
	// 	DrawText(Score, FLinearColor(1, 1, 1, 1), xy.X / 5, xy.Y / 2,0,2);
	// 	return;
	// }
	
	DrawText( Time, FLinearColor(1, 1, 1, 1), xy.X / 10, xy.Y / 10,0,2);
	DrawText(Score, FLinearColor(1, 1, 1, 1), xy.X / 10, xy.Y / 20,0,2);


};
