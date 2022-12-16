// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "A1PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTONE_API UA1PlayerHud : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTimer(float time);

	void SetTargetPoints(int point);


};
