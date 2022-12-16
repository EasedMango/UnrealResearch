// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameState.h"
#include "GameFramework/HUD.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTONE_API APlayerHud : public AHUD
{
	GENERATED_BODY()
	UPROPERTY()
	AMyGameState* GameMode;
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;


private:
};
