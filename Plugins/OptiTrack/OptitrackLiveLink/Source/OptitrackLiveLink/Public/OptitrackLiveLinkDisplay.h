//======================================================================================================
// Copyright 2021, NaturalPoint Inc.
//====================================================================================================== 
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiveLinkTypes.h"
#include "ILiveLinkClient.h"
#include "OptitrackLiveLinkDisplay.generated.h"

struct FLiveLinkSubjectKey;
class ULiveLinkRole;

UCLASS()
class OPTITRACKLIVELINK_API AOptitrackLiveLinkDisplay : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AOptitrackLiveLinkDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	void OnSubjectStaticDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkStaticDataStruct& InStaticData );
	void OnSubjectFrameDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkFrameDataStruct& InFrameData );

protected:
	void Draw();

public:
	/** Display streamed data visuals */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack",  DisplayName = "Display Streamed Data" )
	bool mDrawData = true;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Line Thickness" )
	float mLineThincknessScale;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Color" )
	FColor mColor;

protected:
	TMap<FLiveLinkSubjectKey, FDelegateHandle> mStaticDataAddedHandles;
	TMap<FLiveLinkSubjectKey, FDelegateHandle> mFrameDataAddedHandles;
	TMap<FLiveLinkSubjectKey, TArray<int32>> mSubjectBoneParents;
	TMap<FLiveLinkSubjectKey, TArray<FTransform>> mSubjectTransforms;
};