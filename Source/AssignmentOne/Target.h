// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetHit);

UCLASS()
class ASSIGNMENTONE_API ATarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget();

	void OnTargetScore(int AddScore);

	
	UPROPERTY(BlueprintAssignable)
	FTargetHit OnTargetHit;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	//void VisualMesh->OnComponentBeginOverlap();
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float FloatAmplitudeSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
		float RotationSpeed = 20.0f;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
