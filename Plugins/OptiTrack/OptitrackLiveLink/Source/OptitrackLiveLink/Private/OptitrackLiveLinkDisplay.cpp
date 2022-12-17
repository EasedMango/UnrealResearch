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

	mLineThicknessScale = 1.0f;
	mSkeletonColor = FColor( 0, 255, 0 );
	mRigidBodyColor = FColor( 0, 255, 0 );
	mLabeledMarkerColor = FColor( 255, 255, 255 );
	mUnlabeledMarkerColor = FColor( 255, 0, 0 );
}

AOptitrackLiveLinkDisplay::~AOptitrackLiveLinkDisplay()
{
	UnregisterForLiveLinkData();
	UnregisterForLiveLinkClient();
}

// Called when the game starts or when spawned
void AOptitrackLiveLinkDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void AOptitrackLiveLinkDisplay::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );
}

bool AOptitrackLiveLinkDisplay::ShouldTickIfViewportsOnly() const
{
	return true;
}

// Called every frame
void AOptitrackLiveLinkDisplay::Tick( float DeltaTime )
{
	if( RegisterForLiveLinkClient() )
	{
		if( mSubjectListChanged )
			UnregisterForLiveLinkData();

		if( LiveLinkSubjectCount() == 0 )
			RegisterForLiveLinkData();
	}

	Super::Tick(DeltaTime);
	Draw();
}

void AOptitrackLiveLinkDisplay::OnLiveLinkSourcesChanged()
{
	mLiveLinkValid = false;
}

void AOptitrackLiveLinkDisplay::OnLiveLinkSubjectsChanged()
{
	mSubjectListChanged = true;
}

void AOptitrackLiveLinkDisplay::OnSubjectStaticDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, 
	const FLiveLinkStaticDataStruct& InStaticData )
{
}

void AOptitrackLiveLinkDisplay::OnSubjectFrameDataAdded( FLiveLinkSubjectKey InSubjectKey, TSubclassOf<ULiveLinkRole> InSubjectRole, 
	const FLiveLinkFrameDataStruct& InFrameData )
{
	if( mDrawSkeletons )
	{
		if( mSkeletonData.Find( InSubjectKey ) )
		{
			if( const FLiveLinkAnimationFrameData* animData = InFrameData.Cast<FLiveLinkAnimationFrameData>() )
			{
				mSkeletonData[InSubjectKey] = animData->Transforms;
			}
		}
	}

	if( mDrawRigidBodies )
	{
		if( const FLiveLinkTransformFrameData* trData = InFrameData.Cast<FLiveLinkTransformFrameData>() )
		{
			mRigidBodyData.FindOrAdd( InSubjectKey ) = trData->Transform;
		}
	}

	if( mDrawLabeledMarkers )
	{
		if( mLabeledMarkerData.Find( InSubjectKey ) )
		{
			if( const FLiveLinkAnimationFrameData* animData = InFrameData.Cast<FLiveLinkAnimationFrameData>() )
			{
				mLabeledMarkerData[InSubjectKey] = animData->Transforms;
			}
		}
	}

	if( mDrawUnlabeledMarkers )
	{
		if( mUnlabeledMarkerData.Find( InSubjectKey ) )
		{
			if( const FLiveLinkAnimationFrameData* animData = InFrameData.Cast<FLiveLinkAnimationFrameData>() )
			{
				mUnlabeledMarkerData[InSubjectKey] = animData->Transforms;
			}
		}
	}
}

bool AOptitrackLiveLinkDisplay::RegisterForLiveLinkClient()
{
	if( mLiveLinkValid )
		return true;

	IModularFeatures& ModularFeatures = IModularFeatures::Get();
	if( !ModularFeatures.IsModularFeatureAvailable( ILiveLinkClient::ModularFeatureName ) )
		return false;

	ILiveLinkClient& LiveLinkClient = ModularFeatures.GetModularFeature<ILiveLinkClient>( ILiveLinkClient::ModularFeatureName );

	mSourcesChangedHandle = LiveLinkClient.OnLiveLinkSourcesChanged().Add( 
		FSimpleMulticastDelegate::FDelegate::CreateUObject( this, &AOptitrackLiveLinkDisplay::OnLiveLinkSourcesChanged ) );

	mSubjectsChangedHandle = LiveLinkClient.OnLiveLinkSubjectsChanged().Add(
		FSimpleMulticastDelegate::FDelegate::CreateUObject( this, &AOptitrackLiveLinkDisplay::OnLiveLinkSubjectsChanged ) );
	
	UnregisterForLiveLinkData();

	mLiveLinkValid = true;
	return true;
}

void AOptitrackLiveLinkDisplay::UnregisterForLiveLinkClient()
{
	if( !mLiveLinkValid )
		return;

	IModularFeatures& ModularFeatures = IModularFeatures::Get();
	if( !ModularFeatures.IsModularFeatureAvailable( ILiveLinkClient::ModularFeatureName ) )
		return;

	ILiveLinkClient& LiveLinkClient = ModularFeatures.GetModularFeature<ILiveLinkClient>( ILiveLinkClient::ModularFeatureName );

	if( mSourcesChangedHandle.IsValid() )
		LiveLinkClient.OnLiveLinkSourcesChanged().Remove( mSourcesChangedHandle );
	mSourcesChangedHandle.Reset();

	if( mSubjectsChangedHandle.IsValid() )
		LiveLinkClient.OnLiveLinkSubjectsChanged().Remove( mSubjectsChangedHandle );
	mSubjectsChangedHandle.Reset();

	mLiveLinkValid = false;
}

bool AOptitrackLiveLinkDisplay::RegisterForLiveLinkData()
{
	mStaticDataAddedHandles.Reset();
	mFrameDataAddedHandles.Reset();
	mBoneParents.Reset();
	mSkeletonData.Reset();
	mRigidBodyData.Reset();
	mLabeledMarkerData.Reset();
	mUnlabeledMarkerData.Reset();

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

				if( FLiveLinkSkeletonStaticData* skeletonData = staticData.Cast<FLiveLinkSkeletonStaticData>() )
				{
					if( key.SubjectName.ToString().Compare( "Markers_Unlabeled", ESearchCase::IgnoreCase ) == 0 )
					{
						// Unlabeled markers
						mUnlabeledMarkerData.FindOrAdd( key );
					}
					else if( key.SubjectName.ToString().StartsWith( "Markers_" ) )
					{
						// Labeled markers
						mLabeledMarkerData.FindOrAdd( key );
					}
					else
					{
						// Skeletons
						mSkeletonData.FindOrAdd( key );
						mBoneParents.FindOrAdd( key ) = skeletonData->BoneParents;
					}
				}
				else if( FLiveLinkTransformStaticData* transformData = staticData.Cast<FLiveLinkTransformStaticData>() )
				{
					// Rigid bodies
					mRigidBodyData.FindOrAdd( key );
				}
			}
		}
	}

	mSubjectListChanged = false;
	return !mFrameDataAddedHandles.IsEmpty();
}

void AOptitrackLiveLinkDisplay::UnregisterForLiveLinkData()
{
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
	mBoneParents.Reset();
	mSkeletonData.Reset();
	mRigidBodyData.Reset();
	mLabeledMarkerData.Reset();
	mUnlabeledMarkerData.Reset();
}

int AOptitrackLiveLinkDisplay::LiveLinkSubjectCount() const
{
	return mFrameDataAddedHandles.Num();
}

void AOptitrackLiveLinkDisplay::Draw()
{
	UWorld* world = GetWorld();

	if( mDrawSkeletons )
	{
		DrawSkeletons( world, mSkeletonData, mBoneParents, mSkeletonColor, mLineThicknessScale );
	}

	if( mDrawRigidBodies )
	{
		DrawRigidBodies( world, mRigidBodyData, mRigidBodyColor );
	}

	if( mDrawLabeledMarkers )
	{
		DrawMarkers( world, mLabeledMarkerData, mLabeledMarkerColor, 1 );
	}

	if( mDrawUnlabeledMarkers )
	{
		DrawMarkers( world, mUnlabeledMarkerData, mUnlabeledMarkerColor, 1 );
	}
}

void AOptitrackLiveLinkDisplay::DrawSkeletons( UWorld* world, const TMap<FLiveLinkSubjectKey, TArray<FTransform>>& skeletons, 
	const TMap<FLiveLinkSubjectKey, TArray<int32>>& parentBones, const FColor& color, float lineThickness ) const
{
	for( const auto& it : skeletons )
	{
		TArray<FTransform> transforms = it.Value;

		if( mBoneParents.Contains( it.Key ) )
		{
			const TArray<int32>& boneParents = mBoneParents[it.Key];
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
					DrawDebugLine( world, transforms[i].GetLocation(), transforms[parentIndex].GetLocation(), color, false, -1, 
						SDPG_MAX, lineThickness );
				}
			}
		}

		for( const FTransform& tr : transforms )
		{
			DrawDebugSphere( world, tr.GetLocation(), 2, 6, color, false, -1, SDPG_MAX, 0.2f );
			DrawDebugCoordinateSystem( world, tr.GetLocation(), tr.Rotator(), 5, false, -1, SDPG_MAX, 0.4f );
		}
	}
}

void AOptitrackLiveLinkDisplay::DrawRigidBodies( UWorld* world, const TMap<FLiveLinkSubjectKey, FTransform>& rigidBodies, const FColor& color ) const
{
	for( const auto& it : rigidBodies )
	{
		const FTransform& tr = it.Value;
		DrawDebugSphere( world, tr.GetLocation(), 2, 6, color, false, -1, SDPG_MAX, 0.2f );
		DrawDebugCoordinateSystem( world, tr.GetLocation(), tr.Rotator(), 5, false, -1, SDPG_MAX, 0.4f );
	}
}

void AOptitrackLiveLinkDisplay::DrawMarkers( UWorld* world, const TMap<FLiveLinkSubjectKey, TArray<FTransform>>& markers, const FColor& color, float size ) const
{
	for( const auto& it : markers )
	{
		for( const FTransform& tr : it.Value )
		{
			if( tr.GetLocation() != FVector::ZeroVector )
			{
				DrawDebugBox( world, tr.GetLocation(), FVector( size, size, size ), color, false, -1, SDPG_MAX );
			}
		}
	}
}
