// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "net/UnrealNetwork.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"
/**
 * 
 */
UCLASS()
class ASSIGNMENTONE_API AMyGameState : public AGameState
{
public:
	AMyGameState();

private:
	GENERATED_BODY()


	float CountdownTime;
	
	// Replicated Specifier used to mark this variable to replicate
	UPROPERTY(Replicated)
	int32 TeamAScore;
	UPROPERTY(Replicated)
	int32 TeamBScore;
	
	// Function to increase the Score of a Team
	void AddScore(bool TeamAScored);
	virtual void Tick(float DeltaSeconds) override;

	inline float GetCountdownTime() const { return CountdownTime; }

	inline void SetCountdownTime(const float& Time) { CountdownTime = Time; }

	inline int32 GetScore(bool TeamA) const { return TeamA ? TeamAScore : TeamBScore; }

	void AddTimeToCountdown(const float& Time) { CountdownTime += abs(Time); };
	void SubtractTimeToCountdown(const float& Time) { CountdownTime -= abs(Time); }
};
