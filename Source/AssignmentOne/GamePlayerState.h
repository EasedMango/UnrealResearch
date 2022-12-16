// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTONE_API AGamePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	//true = A and false = B
	bool Team;
};
