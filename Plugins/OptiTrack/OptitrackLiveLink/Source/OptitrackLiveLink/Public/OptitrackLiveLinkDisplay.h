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

	virtual ~AOptitrackLiveLinkDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:
	/** If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly	 */
	bool ShouldTickIfViewportsOnly() const override;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	void OnLiveLinkSourcesChanged();
	void OnLiveLinkSubjectsChanged();
	void OnSubjectStaticDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkStaticDataStruct& InStaticData );
	void OnSubjectFrameDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> SubjectRole, const FLiveLinkFrameDataStruct& InFrameData );

protected:
	bool RegisterForLiveLinkClient();
	void UnregisterForLiveLinkClient();
	bool RegisterForLiveLinkData();
	void UnregisterForLiveLinkData();

	int LiveLinkSubjectCount() const;

	void Draw();
	void DrawSkeletons( UWorld* world, const TMap<FLiveLinkSubjectKey, TArray<FTransform>>& skeletons, 
		const TMap<FLiveLinkSubjectKey, TArray<int32>>& parentBones, const FColor& color, float lineThickness ) const;
	void DrawRigidBodies( UWorld* world, const TMap<FLiveLinkSubjectKey, FTransform>& rigidBodies, const FColor& color ) const;
	void DrawMarkers( UWorld* world, const TMap<FLiveLinkSubjectKey, TArray<FTransform>>& markers, const FColor& color, 
		float size ) const;

public:
	/** Display streamed skeleton data visuals */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack",  DisplayName = "Display Skeleton Data" )
	bool mDrawSkeletons = true;

	/** Skeleton color */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Skeleton Color" )
	FColor mSkeletonColor;

	/** Line thickness */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Line Thickness" )
	float mLineThicknessScale;

	/** Display streamed rigid body data visuals */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack",  DisplayName = "Display Rigid Body Data" )
	bool mDrawRigidBodies = true;

	/** Rigid body color */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Rigid Body Color" )
	FColor mRigidBodyColor;

	/** Display streamed labeled marker data visuals */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack",  DisplayName = "Display Labeled Marker Data" )
	bool mDrawLabeledMarkers = true;

	/** Labeled marker color */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Labeled Marker Color" )
	FColor mLabeledMarkerColor;

	/** Display streamed unlabeled marker data visuals */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack",  DisplayName = "Display Unlabeled Marker Data" )
	bool mDrawUnlabeledMarkers = true;

	/** Unlabeled marker color */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Optitrack", DisplayName = "Unlabeled Marker Color" )
	FColor mUnlabeledMarkerColor;

protected:
	bool mLiveLinkValid = false;
	FDelegateHandle mSourcesChangedHandle;

	bool mSubjectListChanged = false;
	FDelegateHandle mSubjectsChangedHandle;

	TMap<FLiveLinkSubjectKey, FDelegateHandle> mStaticDataAddedHandles;
	TMap<FLiveLinkSubjectKey, FDelegateHandle> mFrameDataAddedHandles;
	TMap<FLiveLinkSubjectKey, TArray<int32>> mBoneParents;
	TMap<FLiveLinkSubjectKey, TArray<FTransform>> mSkeletonData;
	TMap<FLiveLinkSubjectKey, FTransform> mRigidBodyData;
	TMap<FLiveLinkSubjectKey, TArray<FTransform>> mLabeledMarkerData;
	TMap<FLiveLinkSubjectKey, TArray<FTransform>> mUnlabeledMarkerData;
};