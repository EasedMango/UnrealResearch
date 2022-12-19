//======================================================================================================
// Copyright 2020, NaturalPoint Inc.
//====================================================================================================== 

#include "LiveLinkNatNetSource.h"
#include "LiveLinkNatNetModule.h"

#include <CommonFrameRates.h>
#include <ILiveLinkClient.h>
#include <LiveLinkTimecodeProvider.h>
#include <Engine/Engine.h>
#include <Engine/SystemTimeTimecodeProvider.h>
#include <Roles/LiveLinkAnimationRole.h>
#include <Roles/LiveLinkTransformRole.h>
#include <Roles/LiveLinkTransformTypes.h>

#include <thread>


#define LOCTEXT_NAMESPACE "LiveLinkNatNetSource"
#define ENABLE_SKELETON_STREAMING 1

const FString FLiveLinkNatNetSource::LiveLinkNatNetSourceName( "OptiTrack" );

FLiveLinkNatNetSource::FLiveLinkNatNetSource( const FOptitrackLiveLinkSettings& Settings )
	: NatNetSettings( Settings )
{
	SourceType = FText::FromString( LiveLinkNatNetSourceName );
	SourceMachineName = FText::FromString( NatNetSettings.ServerIpAddress );
	SourceStatus = LOCTEXT( "SourceStatus", "No Connection" );
}


FLiveLinkNatNetSource::~FLiveLinkNatNetSource()
{

}


void FLiveLinkNatNetSource::ReceiveClient( ILiveLinkClient* InClient, FGuid InSourceGuid )
{
	LLClient = InClient;
	LLSourceGuid = InSourceGuid;

	NNClient = IOptitrackLiveLinkPlugin::Get().CreateClient();

	if( NNClient == nullptr )
	{
		UE_LOG( LogOptitrackLiveLink, Error, TEXT( "IOptitrackLiveLinkPlugin::CreateClient failed" ) );
		return;
	}

	if( NatNetSettings.ConnectAutomatically )
	{
		// Initialize NatNet asynchronous discovery.
		bAsynchronousDiscoveryActiveFlag = true;
		NatNet_CreateAsyncServerDiscovery( &NatNetDiscoveryHandle, ServerDiscoveredCallback_Thunk, this );

		// Wait for NatNet server discovery for maximum of 2 sec
		int waitTime = 2000;
		while( !bClientConnected && waitTime > 0 )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
			waitTime -= 100;
		}
	}
	else
	{
		// connect normally
		const std::string strServerAddr( TCHAR_TO_ANSI( *NatNetSettings.ServerIpAddress ) );
		const std::string strClientAddr( TCHAR_TO_ANSI( *NatNetSettings.ClientIpAddress ) );
		sNatNetClientConnectParams connectParams;
		connectParams.serverAddress = strServerAddr.c_str();
		connectParams.localAddress = strClientAddr.c_str();
		connectParams.connectionType = ( NatNetSettings.ConnectionType == EOptitrackLiveLinkConnectionType::Unicast ) ? ConnectionType_Unicast : ConnectionType_Multicast;

		ConnectToNatNet( connectParams );
	}

	if( NNClient && bClientConnected )
	{
		SetBoneNamingConvention( EOptitrackLiveLinkBoneNamingConvention::FBX );
		SetSkeletonUseLocalCoordinates( true );

		GenerateDataDescriptions();

		// Handles the streamed data.
		NNClient->SetFrameReceivedCallback( &FLiveLinkNatNetSource::NatNetFrameReceivedCallback_Thunk, this );

		if( HelperThread.joinable() )
		{
			bExitHelperThread = true;
			HelperThread.join();
		}
		HelperThread = std::thread( &FLiveLinkNatNetSource::HelperThreadProc, this );

		bLLShuttingDown = false;
	}
	else
	{
		RequestSourceShutdown();
	}
}


bool FLiveLinkNatNetSource::RequestSourceShutdown()
{
	bLLShuttingDown = true;

	if( NatNetDiscoveryHandle != nullptr )
	{
		NatNet_FreeAsyncServerDiscovery( NatNetDiscoveryHandle );
		NatNetDiscoveryHandle = nullptr;
	}

	if( NNClient != nullptr )
	{
		bAsynchronousDiscoveryActiveFlag = false;
		NNClient->Disconnect();
		IOptitrackLiveLinkPlugin::Get().DestroyClient( NNClient );
		NNClient = nullptr;
	}

	if( HelperThread.joinable() )
	{
		bExitHelperThread = true;
		HelperThread.join();
	}

	ResetTimecodeProvider();

	SourceStatus = LOCTEXT( "SourceStatus", "Disconnected" );

	return true;
}

TSubclassOf<ULiveLinkSourceSettings> FLiveLinkNatNetSource::GetSettingsClass() const
{
	return UOptitrackLiveLinkSourceSettings::StaticClass();
}

void FLiveLinkNatNetSource::InitializeSettings( ULiveLinkSourceSettings* Settings )
{
	if( !Settings->IsA<UOptitrackLiveLinkSourceSettings>() )
		return;

	UOptitrackLiveLinkSourceSettings& OptitrackSettings = *Cast<UOptitrackLiveLinkSourceSettings>( Settings );

	{
		std::lock_guard<std::mutex> Lock( AssetMutex );
		if( LLAssets.Num() > 0 )
			OptitrackSettings.SubjectName = LLAssets[0].SubjectName;
	}

	SetSourceSettings( OptitrackSettings );
}

void FLiveLinkNatNetSource::OnSettingsChanged( ULiveLinkSourceSettings* Settings, const FPropertyChangedEvent& PropertyChangedEvent )
{
	if( PropertyChangedEvent.ChangeType != EPropertyChangeType::ValueSet )
		return;

	if( !Settings->IsA<UOptitrackLiveLinkSourceSettings>() )
		return;

	SetSourceSettings( *Cast<UOptitrackLiveLinkSourceSettings>( Settings ) );
}

void FLiveLinkNatNetSource::SetSourceSettings( UOptitrackLiveLinkSourceSettings& Settings )
{
	StreamDataOrigin = FTransform( Settings.Orientation, Settings.Location );
	StreamDataScale = Settings.Scale;

	if( Settings.TimecodeProvider )
		SetTimecodeProvider();
	else
		ResetTimecodeProvider();

	if( SetTimecodeProviderSubject( Settings.SubjectName ) )
	{
		// Regenerate descriptions to update the livelink timecode provider
		ClearDataDescriptions();
		GenerateDataDescriptions();
	}
}

bool FLiveLinkNatNetSource::ConnectToNatNet( const sNatNetClientConnectParams& connectParams )
{
	if( !NNClient )
	{
		return false;
	}

	// Connect to NatNet and throw an error if necessary. 
	const ErrorCode connectResult = NNClient->Connect( connectParams );
	if( connectResult != ErrorCode_OK )
	{
		UE_LOG( LogOptitrackLiveLink, Error, TEXT( "NatNetClient::Connect failed with return code %d" ), static_cast<int32>( connectResult ) );
		SourceStatus = LOCTEXT( "SourceStatus", "Connection Error" );
		RequestSourceShutdown();
		return false;
	}

	SourceStatus = LOCTEXT( "SourceStatus", "Initialized" );
	SourceMachineName = FText::FromString( NatNetSettings.ServerIpAddress );

	bClientConnected = true;

	return true;
}

void FLiveLinkNatNetSource::SetTimecodeProvider()
{
	ULiveLinkTimecodeProvider* livelinkTimeCodeProvider = Cast<ULiveLinkTimecodeProvider>( GEngine->GetTimecodeProvider() );

	// Already set as timecode provider
	if( livelinkTimeCodeProvider )
		return;

	livelinkTimeCodeProvider = NewObject<ULiveLinkTimecodeProvider>();
	GEngine->SetTimecodeProvider( livelinkTimeCodeProvider );
	TimecodeWaitBuffer = 0;
}

void FLiveLinkNatNetSource::ResetTimecodeProvider() const
{
	ULiveLinkTimecodeProvider* livelinkTimeCodeProvider = Cast<ULiveLinkTimecodeProvider>( GEngine->GetTimecodeProvider() );

	// Live link is not set as timecode provider
	if( !livelinkTimeCodeProvider )
		return;

	USystemTimeTimecodeProvider* systemTimeCodePrivider = NewObject<USystemTimeTimecodeProvider>();
	GEngine->SetTimecodeProvider( systemTimeCodePrivider );
}

bool FLiveLinkNatNetSource::SetTimecodeProviderSubject( const FName& subjectName )
{
	// LiveLink is not set as the timecode provider
	ULiveLinkTimecodeProvider* livelinkTimeCodeProvider = Cast<ULiveLinkTimecodeProvider>( GEngine->GetTimecodeProvider() );
	if( livelinkTimeCodeProvider == nullptr )
		return false;

	FProperty* prop = livelinkTimeCodeProvider->GetClass()->FindPropertyByName( "SubjectKey" );
	FLiveLinkSubjectKey* subjectKey = prop->ContainerPtrToValuePtr<FLiveLinkSubjectKey>( livelinkTimeCodeProvider );
	if( subjectKey == nullptr )
		return false;

	FGuid sourceGuid;
	// Find the asset by name
	{
		std::lock_guard<std::mutex> Lock( AssetMutex );
		for( const FLiveLinkSubjectKey& key : LLAssets )
		{
			if( key.SubjectName == subjectName )
			{
				sourceGuid = key.Source;
				break;
			}
		}
	}

	// Already set as subject
	if( subjectKey->Source == sourceGuid && subjectKey->SubjectName == subjectName )
		return false;

	subjectKey->Source = sourceGuid;
	subjectKey->SubjectName = subjectName;

	return true;
}

void FLiveLinkNatNetSource::GenerateDataDescriptions()
{
	if( !NNClient )
	{
		return;
	}

	const ErrorCode getDataDescsResult = NNClient->GetDataDescriptionList( &NNDataDescs );
	if( !ensureMsgf( getDataDescsResult == ErrorCode_OK && NNDataDescs != nullptr, TEXT( "NatNetClient::GetDataDescriptionList failed with return code %d" ), getDataDescsResult ) )
	{
		SourceStatus = LOCTEXT( "SourceStatus", "Error - Data Descriptions" );
		RequestSourceShutdown();
		return;
	}

	// Get Asset Data Descriptions
	for( int iDesc = 0; iDesc < NNDataDescs->nDataDescriptions; ++iDesc )
	{
		const sDataDescription& dataDesc = NNDataDescs->arrDataDescriptions[iDesc];

#if ENABLE_SKELETON_STREAMING
		//// =================
		//// Skeletons
		//// =================
		if( dataDesc.type == Descriptor_Skeleton )
		{
			const sSkeletonDescription& skelDesc = *dataDesc.Data.SkeletonDescription;

			// Cache mapping from NatNet ID to FName
			const FString skelNameString( skelDesc.szName );
			const FName skelName = FName( *skelNameString );
			NNSkelIdToSubjectName.FindOrAdd( skelDesc.skeletonID ) = skelName;

			// Figure out the Bone Structure
			TArray<FName> boneNames;
			boneNames.Reserve(skelDesc.nRigidBodies + 1);

			TArray<int32> boneParents;
			boneParents.Reserve(skelDesc.nRigidBodies + 1);

			boneNames.Emplace( "Root" );
			boneParents.Emplace( -1 );

			for( int i = 0; i < skelDesc.nRigidBodies; ++i )
			{
				const sRigidBodyDescription& boneDesc = skelDesc.RigidBodies[i];

				FString boneName( boneDesc.szName );

				if( boneName.StartsWith( skelNameString ) )
					boneName = boneName.RightChop( skelNameString.Len() + 1 );

				boneNames.Emplace( *boneName );
				
				// Root bone as the default parent
				int parentIndex = 0;
				if( boneDesc.parentID > 0 )
				{
					for( int p = 0; p < skelDesc.nRigidBodies; p++ )
					{
						if( skelDesc.RigidBodies[p].ID == boneDesc.parentID )
						{
							// +1 for having Root bone
							parentIndex = p + 1;
							break;
						}
					}
				}
				boneParents.Emplace( parentIndex );
			}

			// Build reference skeleton for subject(s)
			FLiveLinkStaticDataStruct subDataStruct = FLiveLinkStaticDataStruct(FLiveLinkSkeletonStaticData::StaticStruct());
			FLiveLinkSkeletonStaticData& refSkeleton = *subDataStruct.Cast<FLiveLinkSkeletonStaticData>();
			refSkeleton.SetBoneNames(boneNames);
			refSkeleton.SetBoneParents(boneParents);

			// Populate skeleton hierarchy to LiveLink
			LLClient->PushSubjectStaticData_AnyThread({ LLSourceGuid, skelName }, ULiveLinkAnimationRole::StaticClass(), MoveTemp(subDataStruct));

			std::lock_guard<std::mutex> Lock( AssetMutex );
			LLAssets.Add({ LLSourceGuid, skelName });
		}
#endif

		// =================
		// Rigid Bodies
		// =================
		if( dataDesc.type == Descriptor_RigidBody )
		{
			const sRigidBodyDescription& rbDesc = *dataDesc.Data.RigidBodyDescription;

			// Cache mapping from NatNet ID to FName
			FName rbName( *FString( rbDesc.szName ) );
			NNRigidBodyIdToSubjectName.FindOrAdd( rbDesc.ID ) = rbName;

			// For transform role
			FLiveLinkStaticDataStruct rigidBodyStaticData = FLiveLinkStaticDataStruct( FLiveLinkTransformStaticData::StaticStruct() );
			LLClient->PushSubjectStaticData_AnyThread( { LLSourceGuid, rbName }, ULiveLinkTransformRole::StaticClass(), MoveTemp( rigidBodyStaticData ) );

			std::lock_guard<std::mutex> Lock( AssetMutex );
			LLAssets.Add( { LLSourceGuid, rbName } );
		}

		SourceStatus = LOCTEXT( "SourceStatus", "Data Descriptions Received" );
	}
}

void FLiveLinkNatNetSource::ClearDataDescriptions()
{
	std::lock_guard<std::mutex> Lock( AssetMutex );

	// Clears all asset descriptions from LiveLink
	for( const FLiveLinkSubjectKey& subject : LLAssets )
	{
		if( bLLShuttingDown )
			break;
		LLClient->RemoveSubject_AnyThread( subject );
	}
	LLAssets.Empty();
}


bool compareFloat( float x, float y, float epsilon = 0.01f )
{
	if( fabs( x - y ) < epsilon )
	{
		return true;
	}
	return false;
}

FFrameRate FLiveLinkNatNetSource::GetComplexTimecodeRate()
{
	// Fractional rates (NTSC) require a special check.
	if( compareFloat( NNTimecodeRate, 23.97 ) )
	{
		return FCommonFrameRates::NTSC_24();
	}
	else if( compareFloat( NNTimecodeRate, 29.97 ) )
	{
		return FCommonFrameRates::NTSC_30();
	}
	else if( compareFloat( NNTimecodeRate, 59.94 ) )
	{
		return FCommonFrameRates::NTSC_60();
	}
	else
	{
		return FFrameRate( NNTimecodeRate, 1 );
	}
}

FVector VectorSwitchHandedness( const FVector& position )
{
	return FVector( -position.X, position.Y, position.Z );
}

FQuat QuatSwitchHandedness( const FQuat& quat )
{
	return FQuat( -quat.X, quat.Y, quat.Z, -quat.W );
}

FVector VectorZUpXForward( const FVector& position )
{
	return FVector( position.Z, position.X, position.Y );
}

FQuat QuatZUpXForward( const FQuat& quat )
{
	FQuat quatZupXForward( -0.5f, -0.5f, -0.5f, -0.5f );
	return quatZupXForward * quat * quatZupXForward.Inverse();
}

void FLiveLinkNatNetSource::NatNetFrameReceivedCallback( sFrameOfMocapData* NewFrame )
{
	if( bLLShuttingDown )
	{
		return;
	}

	SourceStatus = LOCTEXT( "SourceStatus", "Connected" );

	// NOTE: Calling NatNet functions from this thread might fail in unicast mode. 
	//       Instead, call it from HelperThread.

	// =================
	// Time and Timecode
	// =================

	//FLiveLinkWorldTime LLWorldTime = FLiveLinkWorldTime(NewFrame->fTimestamp);
	FLiveLinkWorldTime LLWorldTime = FLiveLinkWorldTime( FPlatformTime::Seconds() );
	FQualifiedFrameTime LLSceneTime;

	// Get and Translate NatNet Timecode to Unreal Timecode.
	int hour, minute, second, frame, subframe;
	NatNet_DecodeTimecode( NewFrame->Timecode, NewFrame->TimecodeSubframe, &hour, &minute, &second, &frame, &subframe );
	FTimecode UETimecode( hour, minute, second, frame, false );


	// TODO: If change loaded take, then possibly re-sample the TimecodeWaitBuffer.


	// Timecode rate isn't a property in NatNet.
	// Figure out the frame rate and timecode rate in the first 199 frames, 
	// then start setting timecode values. 
	if( TimecodeWaitBuffer > 100 )
	{
		//Use frame rate with sub-frames
		LLSceneTime.Rate = GetComplexTimecodeRate();
		LLSceneTime.Time = FFrameTime(
			UETimecode.ToFrameNumber( LLSceneTime.Rate ),
			(float)subframe / (float)( TimecodeMaxSubFrame + 1 )
		);
	}
	else if( TimecodeWaitBuffer == 100 )
	{
		// Auto-set the timecode rate one time when connecting. 
		++TimecodeWaitBuffer;
		ULiveLinkSourceSettings* autoSetTimecode = LLClient->GetSourceSettings( LLSourceGuid );
		autoSetTimecode->BufferSettings.SourceTimecodeFrameRate = GetComplexTimecodeRate();
	}
	else // < 100 frames
	{
		// Wait 100 frames to figure out what the motion capture and timecode rates are. 
		if( NNFrameRate >= 0 )
		{
			++TimecodeWaitBuffer;
		}

		// Calculate the max number of sub-frames
		if( subframe > TimecodeMaxSubFrame )
		{
			TimecodeMaxSubFrame = subframe;
		}

		if( TimecodeMaxSubFrame > 0 && NNFrameRate > 0 )
		{	
			// Figure out the timecode rate from the frame rate and subframe information. 
			NNTimecodeRate = NNFrameRate / (float)( TimecodeMaxSubFrame + 1 );
		}
	}

	const float kCoordScalingFactor = 100.0f;
//	const FVector boneScale = FVector( 1.0, 1.0, 1.0 );

#if ENABLE_SKELETON_STREAMING
	//// =================
	//// Skeletons
	//// =================
	for ( int iSkel = 0; iSkel < NewFrame->nSkeletons; ++iSkel )
	{
		const sSkeletonData& skelData = NewFrame->Skeletons[iSkel];

		const FName* skelName = NNSkelIdToSubjectName.Find( skelData.skeletonID );
		if (skelName == nullptr) {
			continue;
		}

		FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkAnimationFrameData::StaticStruct());

		FLiveLinkAnimationFrameData& animFrame = *frameDataStruct.Cast<FLiveLinkAnimationFrameData>();
		TArray<FTransform>& transforms = animFrame.Transforms;
		transforms.SetNumZeroed( skelData.nRigidBodies + 1 );

		// Decompose the hip transform, extracting a synthetic root bone
		// containing just the XY plane translation and yaw rotation.
		FTransform trRoot, trHip;
		{
			const sRigidBodyData& hipData = skelData.RigidBodyData[0];
			
			FVector hipPos( hipData.x, hipData.y, hipData.z );
			hipPos *= kCoordScalingFactor;
			hipPos = VectorSwitchHandedness( hipPos );
			hipPos = VectorZUpXForward( hipPos );

			FQuat hipRot( hipData.qx, hipData.qy, hipData.qz, hipData.qw );
			hipRot = QuatSwitchHandedness( hipRot );
			hipRot = QuatZUpXForward( hipRot );

			// Apply LiveLink offset/rotation/scaling
			FTransform hipTr = FTransform( hipRot, hipPos * StreamDataScale ) * StreamDataOrigin;
			float streamOriginHeight = StreamDataOrigin.GetLocation().Z;
			hipPos = hipTr.GetLocation();
			hipRot = hipTr.GetRotation();

			FQuat hipYaw, hipTilt;
			hipRot.ToSwingTwist( FVector::UpVector, hipTilt, hipYaw );

			trRoot.SetTranslation( FVector( hipPos.X, hipPos.Y, streamOriginHeight ) );
			trRoot.SetRotation( hipYaw );

			trHip.SetTranslation( FVector( 0, 0, hipPos.Z - streamOriginHeight ) );
			trHip.SetRotation( hipYaw.Inverse() * hipRot );
		}
		transforms[0] = trRoot;
		transforms[1] = trHip;

		// Skip the hips [0], which we handled specially above.
		for ( int rbIndex = 1; rbIndex < skelData.nRigidBodies; ++rbIndex )
		{
			const sRigidBodyData& rbData = skelData.RigidBodyData[rbIndex];

			FVector pos( rbData.x, rbData.y, rbData.z );
			pos *= kCoordScalingFactor;
			pos = VectorSwitchHandedness( pos );
			pos = VectorZUpXForward( pos );

			FQuat rot( rbData.qx, rbData.qy, rbData.qz, rbData.qw );
			rot = QuatSwitchHandedness( rot );
			rot = QuatZUpXForward( rot );

			transforms[rbIndex + 1] = FTransform( rot, pos );//, boneScale);
		}

		// Set the world time and timecode 
		//animFrame.WorldTime = LLWorldTime;
		//animFrame.MetaData.SceneTime = LLSceneTime;

		// Set the world time and timecode 
		animFrame.WorldTime = LLWorldTime;
		animFrame.ArrivalTime.WorldTime = LLWorldTime.GetSourceTime();

		if (LLSceneTime.Rate.IsValid())
		{
			animFrame.MetaData.SceneTime = LLSceneTime;
			animFrame.ArrivalTime.SceneTime = LLSceneTime;
		}

		LLClient->PushSubjectFrameData_AnyThread({ LLSourceGuid, *skelName }, MoveTemp( frameDataStruct ));
		//UE_LOG(LogOptitrackLiveLink, Log, TEXT("Adding Data for skeleton %d"), *skelName->ToString());
	}
#endif

	// =================
	// Rigid Bodies
	// =================
	for( int rbIndex = 0; rbIndex < NewFrame->nRigidBodies; rbIndex++ )
	{
		const sRigidBodyData& rbData = NewFrame->RigidBodies[rbIndex];
		if( !NNRigidBodyIdToSubjectName.Contains( rbData.ID ) )
			continue;

		const FName& rbName = NNRigidBodyIdToSubjectName[rbData.ID];

		FVector rbPosition( rbData.z, -rbData.x, rbData.y );
		rbPosition *= kCoordScalingFactor;
		FQuat rbRotation( rbData.qz, -rbData.qx, rbData.qy, -rbData.qw );

		// For transform role
		FLiveLinkFrameDataStruct transformFrameDataStruct( FLiveLinkTransformFrameData::StaticStruct() );
		FLiveLinkTransformFrameData& transformFrame = *transformFrameDataStruct.Cast<FLiveLinkTransformFrameData>();
		transformFrame.Transform = FTransform( rbRotation, rbPosition * StreamDataScale ) * StreamDataOrigin;

		// Set the world time and timecode 
		transformFrame.WorldTime = LLWorldTime;
		transformFrame.ArrivalTime.WorldTime = LLWorldTime.GetSourceTime();

		if( LLSceneTime.Rate.IsValid() )
		{
			transformFrame.MetaData.SceneTime = LLSceneTime;
			transformFrame.ArrivalTime.SceneTime = LLSceneTime;
		}

		LLClient->PushSubjectFrameData_AnyThread( { LLSourceGuid, rbName }, MoveTemp( transformFrameDataStruct ) );
		//UE_LOG(LogOptitrackLiveLink, Log, TEXT("Adding Data for rigid body %d"), *rbName->ToString());
	}

	// Reset data dec if data descriptions have changed
	if( ( NewFrame->params & 0x02 ) != 0 )
	{
		bRefreshDataDescriptions = true;
	}
	// Complicated logic for checking if the Live/Edit mode has changed.
	else if( NewFrame->iFrame % 300 == 0 )
	{
		bDetectLiveEditModeChange = true;
	}

	if( NNFrameRate < 0 )
	{
		bUpdateFrameRate = true;
	}
}

// static
void NATNET_CALLCONV FLiveLinkNatNetSource::NatNetFrameReceivedCallback_Thunk( sFrameOfMocapData* NewFrame, void* pContext )
{
	FLiveLinkNatNetSource* This = reinterpret_cast<FLiveLinkNatNetSource*>( pContext );
	if( ensure( This ) )
	{
		This->NatNetFrameReceivedCallback( NewFrame );
	}
}

// static
void NATNET_CALLCONV FLiveLinkNatNetSource::ServerDiscoveredCallback_Thunk( const sNatNetDiscoveredServer* pDiscoveredServer, void* pUserContext )
{
	FLiveLinkNatNetSource* This = reinterpret_cast<FLiveLinkNatNetSource*>( pUserContext );

	if( ensure( This ) )
	{
		This->ServerDiscoveredCallback( pDiscoveredServer );
	}
}


void FLiveLinkNatNetSource::ServerDiscoveredCallback( const sNatNetDiscoveredServer* pDiscoveredServer )
{
	if( bClientConnected )
	{
		// already connected...
		return;
	}

	// server discovered, unpack connection info
	if( NatNetSettings.ServerIpAddress != "127.0.0.1" && NatNetSettings.ServerIpAddress != pDiscoveredServer->serverAddress )
	{
		// newly found server does not match specified server address config, don't connect
		return;
	}

	if( NatNetSettings.ClientIpAddress != "127.0.0.1" && NatNetSettings.ClientIpAddress != pDiscoveredServer->localAddress )
	{
		// newly found server does not match specified local address config, don't connect
		return;
	}

	UE_LOG( LogOptitrackLiveLink, Log, TEXT( "Motive server discovered, connecting...\n" ) );

	// Initialize NatNet for discovered server
	sNatNetClientConnectParams connectParams;
	connectParams.connectionType = pDiscoveredServer->serverDescription.ConnectionMulticast ? ConnectionType_Multicast : ConnectionType_Unicast;
	connectParams.serverAddress = pDiscoveredServer->serverAddress;
	connectParams.localAddress = pDiscoveredServer->localAddress;

	if( ConnectToNatNet( connectParams ) )
	{
		// Update NatNetSettings
		NatNetSettings.ServerIpAddress = ANSI_TO_TCHAR( connectParams.serverAddress );
		NatNetSettings.ClientIpAddress = ANSI_TO_TCHAR( connectParams.localAddress );
		if( connectParams.connectionType == ConnectionType_Multicast )
		{
			NatNetSettings.ConnectionType = EOptitrackLiveLinkConnectionType::Multicast;
		}
		else
		{
			NatNetSettings.ConnectionType = EOptitrackLiveLinkConnectionType::Unicast;
		}
		SourceMachineName = FText::FromString( NatNetSettings.ServerIpAddress );
		SourceStatus = LOCTEXT( "SourceStatus", "Initialized" );
	}

	bAsynchronousDiscoveryActiveFlag = false;
}

void FLiveLinkNatNetSource::HelperThreadProc()
{
	bExitHelperThread = false;

	// Handle tasks that require calling NatNet functions in this thread

	while( !bExitHelperThread )
	{
		if( bRefreshDataDescriptions )
		{
			bRefreshDataDescriptions = false;

			ClearDataDescriptions();
			GenerateDataDescriptions();
			bAssetListChanged = true;
		}

		if( bUpdateFrameRate )
		{
			bUpdateFrameRate = false;

			float FrameRate = GetFrameRate();
			if( FrameRate >= 0 )
			{
				NNFrameRate = FrameRate;
			}
		}

		if( bDetectLiveEditModeChange )
		{
			bDetectLiveEditModeChange = false;

			int Mode = GetLiveEditMode();
			if( Mode >= 0 )
			{
				bool bLive = Mode == 0 || Mode == 1;

				if( bLive != bMotiveLiveMode )
				{
					bMotiveLiveMode = bLive;

					// Live/Edit mode changed, update data descriptions
					ClearDataDescriptions();
					GenerateDataDescriptions();
					bAssetListChanged = true;
				}
			}
		}

		if( bAssetListChanged )
		{
			bAssetListChanged = false;

			ULiveLinkSourceSettings* settings = LLClient ? LLClient->GetSourceSettings( LLSourceGuid ) : nullptr;
			if( settings && settings->IsA<UOptitrackLiveLinkSourceSettings>() )
			{
				UOptitrackLiveLinkSourceSettings& OptitrackSettings = *Cast<UOptitrackLiveLinkSourceSettings>( settings );

				FName SubjectName;
				{
					std::lock_guard<std::mutex> Lock( AssetMutex );
					if( LLAssets.Num() > 0 )
						SubjectName = LLAssets[0].SubjectName;

					for( const FLiveLinkSubjectKey& key : LLAssets )
					{
						if( key.SubjectName == OptitrackSettings.SubjectName )
						{
							SubjectName = key.SubjectName;
							break;
						}
					}
				}
				OptitrackSettings.SubjectName = SubjectName;

				if( OptitrackSettings.TimecodeProvider && SetTimecodeProviderSubject( SubjectName ) )
				{
					// Regenerate descriptions to update the Live Link timecode provider
					ClearDataDescriptions();
					GenerateDataDescriptions();
				}
			}
		}

		if( bDetectDisconnect )
		{
			if( NNClient == nullptr && bAsynchronousDiscoveryActiveFlag == false )
			{
				// shouldn't happen, but just in case
				UE_LOG( LogOptitrackLiveLink, Log, TEXT( "AOptitrackClientOrigin: NatNet attempting server discovery." ) );
				bTriggerReconnectFlag = true;
			}

			if( NatNetSettings.ConnectAutomatically && NatNetTimestampEpoch != 0 && bAsynchronousDiscoveryActiveFlag == false )
			{
				const double secondsSinceLastTimestamp =
					NNClient->SecondsSinceHostTimestamp( NatNetLastRecievedTimestamp );

				if( NNClient != nullptr && secondsSinceLastTimestamp > 1.0 )
				{
					// valid timestamp and not actively seeking motive server, receive frame hasn't been called in a second
					// ping Motive to see if it's still there
					float LocalFrameRate = GetFrameRate();

					if( !compareFloat( -1.0, LocalFrameRate ) )
					{
						bTriggerReconnectFlag = true;
					}
				}
			}
		}

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
}

void FLiveLinkNatNetSource::NatNetToLiveLinkTimeCode( int Rate, int Hours, int Minutes, int Seconds, int Frames, FQualifiedFrameTime& LLTimeCode )
{
	LLTimeCode.Rate = FFrameRate( Rate, 1 );
	FTimecode UnrealTimecode( Hours, Minutes, Seconds, Frames, false );

	LLTimeCode.Time = FFrameTime( UnrealTimecode.ToFrameNumber( LLTimeCode.Rate ) );
}


bool FLiveLinkNatNetSource::SetBoneNamingConvention( EOptitrackLiveLinkBoneNamingConvention BoneNamingConvention )
{
	std::string CmdStr = "SetProperty,,Bone Naming Convention,";

	switch( BoneNamingConvention )
	{
    case EOptitrackLiveLinkBoneNamingConvention::Motive:
        CmdStr += "0";
        break;
	case EOptitrackLiveLinkBoneNamingConvention::FBX:
		CmdStr += "1";
		break;
    case EOptitrackLiveLinkBoneNamingConvention::BVH:
        CmdStr += "2";
        break;
	default:
		// Error
		break;
	}

	if( NNClient != nullptr )
	{
		// Set the bone naming convention
		void* Response;
		int ResponseBytes = 0;
		const int ReturnVal = NNClient->SendMessageAndWait( CmdStr.c_str(), &Response, &ResponseBytes );
		if( ReturnVal == ErrorCode_OK )
		{
			return true;
		}
		else
		{
			UE_LOG( LogOptitrackLiveLink, Error, TEXT( "Unable to set Motive bone naming convention. Check Motive streaming settings." ) );
			return false;
		}
	}

	return false;
}

bool FLiveLinkNatNetSource::SetSkeletonUseLocalCoordinates( bool LocalCoordinates )
{
	if( NNClient != nullptr )
	{
		std::string CmdStr = "SetProperty,,Skeleton Coordinates,";
		CmdStr += LocalCoordinates ? "true" : "false";

		void* Response;
		int ResponseBytes = 0;
		const int ReturnVal = NNClient->SendMessageAndWait( CmdStr.c_str(), &Response, &ResponseBytes );
		if( ReturnVal == ErrorCode_OK )
		{
			return true;
		}
		else
		{
			UE_LOG( LogOptitrackLiveLink, Error, TEXT( "Unable to set skeleton coordinates. Check Motive streaming settings." ) );
			return false;
		}
	}

	return false;
}


// NatNet response: int32_t value representing the current mode. (0 = Live, 1 = Recording, 2 = Edit-Playing Back, 3 = Edit-Paused)
// Returns -1 if query was unsuccessful.
int FLiveLinkNatNetSource::GetLiveEditMode()
{
	if( NNClient != nullptr )
	{
		void* Result;
		int ResponseBytes = 0;
		const int ReturnVal = NNClient->SendMessageAndWait( "CurrentMode", &Result, &ResponseBytes );
		if( ReturnVal == ErrorCode_OK )
		{
			return *( (int*)Result );
		}
		else
		{
			UE_LOG( LogOptitrackLiveLink, Log, TEXT( "Motive mode not found." ) );
		}
	}

	return -1;
}


float FLiveLinkNatNetSource::GetFrameRate()
{
	if( NNClient != nullptr )
	{
		void* Result;
		int ResponseBytes = 0;
		const int ReturnVal = NNClient->SendMessageAndWait( "FrameRate", &Result, &ResponseBytes );
		if( ReturnVal == ErrorCode_OK )
		{
			return *( (float*)Result );
		}
		else
		{
			UE_LOG( LogOptitrackLiveLink, Log, TEXT( "Error getting the frame rate." ) );
		}
	}
	return -1.0;
}


#undef LOCTEXT_NAMESPACE
