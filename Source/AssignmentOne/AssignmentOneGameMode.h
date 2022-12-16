// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AssignmentOneGameMode.generated.h"

UCLASS(minimalapi)
class AAssignmentOneGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	float CountdownTime;
	int32 Score;

public:
	/* Header file of our GameMode Child Class inside of the Class declaration */
	// List of PlayerControllers
	TArray<class APlayerController*> PlayerControllerList;
	// Overriding the PostLogin function
	virtual void PostLogin(APlayerController* NewPlayer) override;
	AAssignmentOneGameMode();
	bool Pause;
	int Hits;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void TargetHit();

	void StartGame();
	inline float GetCountdownTime() const { return CountdownTime; }

	inline void SetCountdownTime(const float& Time) { CountdownTime = Time; }

	inline int32 GetScore() const { return Score; }

	void AddTimeToCountdown(const float& Time) { CountdownTime += abs(Time); };
	void SubtractTimeToCountdown(const float& Time) { CountdownTime -= abs(Time); };
	float CountdownHasFinished();
	//virtual void Initialize();
	void HitTime(const float& Time);
};
