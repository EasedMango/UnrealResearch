#include "OptitrackLiveLinkDisplay.h"
#include <Components/LineBatchComponent.h>
#include <LiveLinkTypes.h>
#include <Roles/LiveLinkAnimationTypes.h>
#include <Roles/LiveLinkTransformTypes.h>
#include <DrawDebugHelpers.h>

// Sets default values
AOptitrackLiveLinkDisplay::AOptitrackLiveLinkDisplay()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mLineThincknessScale = 1.0f;
	mColor = FColor::Green;
}

// Called when the game starts or when spawned
void AOptitrackLiveLinkDisplay::BeginPlay()
{
	Super::BeginPlay();

	mStaticDataAddedHandles.Reset();
	mFrameDataAddedHandles.Reset();
	mSubjectBoneParents.Reset();
	mSubjectTransforms.Reset();

	IModularFeatures& ModularFeatures = IModularFeatures::Get();
	if( ModularFeatures.IsModularFeatureAvailable( ILiveLinkClient::ModularFeatureName ) )
	{
		ILiveLinkClient& LiveLinkClient = ModularFeatures.GetModularFeature<ILiveLinkClient>( ILiveLinkClient::ModularFeatureName );

		TArray<FLiveLinkSubjectKey> subjectKeys = LiveLinkClient.GetSubjects( false, true );
		for( const FLiveLinkSubjectKey& key : subjectKeys )
		{
			FDelegateHandle staticDataAdded, frameDataAdded;
			TSubclassOf<ULiveLinkRole> role;
			FLiveLinkStaticDataStruct staticData;

			if( LiveLinkClient.RegisterForSubjectFrames( key.SubjectName, 
				FOnLiveLinkSubjectStaticDataAdded::FDelegate::CreateUObject( this, &AOptitrackLiveLinkDisplay::OnSubjectStaticDataAdded ),
				FOnLiveLinkSubjectFrameDataAdded::FDelegate::CreateUObject( this, &AOptitrackLiveLinkDisplay::OnSubjectFrameDataAdded ),
				staticDataAdded, frameDataAdded, role, &staticData ) )
			{
				mStaticDataAddedHandles.FindOrAdd( key ) = staticDataAdded;
				mFrameDataAddedHandles.FindOrAdd( key ) = frameDataAdded;
	
				if( FLiveLinkSkeletonStaticData* refSkeleton = staticData.Cast<FLiveLinkSkeletonStaticData>() )
				{
					mSubjectBoneParents.FindOrAdd( key ) = refSkeleton->BoneParents;
				}
			}
		}
	}
}

void AOptitrackLiveLinkDisplay::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );

	IModularFeatures& ModularFeatures = IModularFeatures::Get();
	if( ModularFeatures.IsModularFeatureAvailable( ILiveLinkClient::ModularFeatureName ) )
	{
		ILiveLinkClient& LiveLinkClient = ModularFeatures.GetModularFeature<ILiveLinkClient>( ILiveLinkClient::ModularFeatureName );
		
		TArray<FLiveLinkSubjectKey> subjectKeys = LiveLinkClient.GetSubjects( false, true );
		for( const FLiveLinkSubjectKey& key : subjectKeys )
		{
			if( mStaticDataAddedHandles.Find( key ) && mFrameDataAddedHandles.Find( key ) )
			{
				LiveLinkClient.UnregisterSubjectFramesHandle( key.SubjectName, mStaticDataAddedHandles[key], mFrameDataAddedHandles[key] );
			}
		}
	}

	mStaticDataAddedHandles.Reset();
	mFrameDataAddedHandles.Reset();
	mSubjectBoneParents.Reset();
	mSubjectTransforms.Reset();
}

// Called every frame
void AOptitrackLiveLinkDisplay::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	if( mDrawData )
	{
		Draw();
	}
}

void AOptitrackLiveLinkDisplay::OnSubjectStaticDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, 
	const FLiveLinkStaticDataStruct& InStaticData )
{
}

void AOptitrackLiveLinkDisplay::OnSubjectFrameDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, 
	const FLiveLinkFrameDataStruct& InFrameData )
{
	if( mDrawData )
	{
		if( const FLiveLinkAnimationFrameData* animData = InFrameData.Cast<FLiveLinkAnimationFrameData>() )
		{
			mSubjectTransforms.FindOrAdd( InSubjectKey ) = animData->Transforms;
		}
		else if( const FLiveLinkTransformFrameData* trData = InFrameData.Cast<FLiveLinkTransformFrameData>() )
		{
			TArray<FTransform> tr;
			tr.Add( trData->Transform );
			mSubjectTransforms.FindOrAdd( InSubjectKey ) = tr;
		}
	}
}

void AOptitrackLiveLinkDisplay::Draw()
{
	UWorld* world = GetWorld();
	for( const auto& it : mSubjectTransforms )
	{
		TArray<FTransform> transforms = it.Value;

		if( mSubjectBoneParents.Contains( it.Key ) )
		{
			const TArray<int32>& boneParents = mSubjectBoneParents[it.Key];
			for( int32 i = 0; i < boneParents.Num(); i++ )
			{
				int32 parentIndex = boneParents[i];
				if( i < transforms.Num() && parentIndex >= 0 && parentIndex < transforms.Num() )
				{
					transforms[i] *= transforms[parentIndex];
				}
			}
			
			for( int32 i = 0; i < boneParents.Num(); i++ )
			{
				int32 parentIndex = boneParents[i];
				if( i < transforms.Num() && parentIndex >= 0 && parentIndex < transforms.Num() )
				{
					DrawDebugLine( world, transforms[i].GetLocation(), transforms[parentIndex].GetLocation(), mColor, false, -1, 
						SDPG_MAX, 1 * mLineThincknessScale );
				}
			}
		}

		for( const FTransform& tr : transforms )
		{
			DrawDebugSphere( world, tr.GetLocation(), 2, 10, mColor, false, -1, SDPG_MAX, 0.2f * mLineThincknessScale );
			DrawDebugCoordinateSystem( world, tr.GetLocation(), tr.Rotator(), 5, false, -1, SDPG_MAX, 0.4f * mLineThincknessScale );
		}
	}
}
