// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UWorld;
class AOptitrackClientOrigin;
struct FTimecode;
enum class EOptitrackTimestampType : uint8;
struct FOptitrackMarkerState;
struct FOptitrackRigidBodyState;
struct FOptitrackSkeletonDefinition;
struct FOptitrackSkeletonState;
#ifdef OPTITRACKNATNET_OptitrackClientOrigin_generated_h
#error "OptitrackClientOrigin.generated.h already included, missing '#pragma once' in OptitrackClientOrigin.h"
#endif
#define OPTITRACKNATNET_OptitrackClientOrigin_generated_h

#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_45_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOptitrackRigidBodyState_Statics; \
	OPTITRACKNATNET_API static class UScriptStruct* StaticStruct();


template<> OPTITRACKNATNET_API UScriptStruct* StaticStruct<struct FOptitrackRigidBodyState>();

#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_71_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOptitrackMarkerState_Statics; \
	OPTITRACKNATNET_API static class UScriptStruct* StaticStruct();


template<> OPTITRACKNATNET_API UScriptStruct* StaticStruct<struct FOptitrackMarkerState>();

#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_97_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOptitrackCamera_Statics; \
	OPTITRACKNATNET_API static class UScriptStruct* StaticStruct();


template<> OPTITRACKNATNET_API UScriptStruct* StaticStruct<struct FOptitrackCamera>();

#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_SPARSE_DATA
#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execShutdownClient); \
	DECLARE_FUNCTION(execGetDataDescription); \
	DECLARE_FUNCTION(execInitializeClient); \
	DECLARE_FUNCTION(execIsClientConnected); \
	DECLARE_FUNCTION(execIsClientInitialized); \
	DECLARE_FUNCTION(execFindHmdClientOrigin); \
	DECLARE_FUNCTION(execFindDefaultClientOrigin); \
	DECLARE_FUNCTION(execGetLatestTimecode); \
	DECLARE_FUNCTION(execGetTimestampType); \
	DECLARE_FUNCTION(execGetLatestMarkerStateUntransformed); \
	DECLARE_FUNCTION(execGetLatestRigidBodyStateUntransformed); \
	DECLARE_FUNCTION(execFindSkeletonDefinition); \
	DECLARE_FUNCTION(execGetLatestSkeletonStateByName); \
	DECLARE_FUNCTION(execGetLatestSkeletonState); \
	DECLARE_FUNCTION(execGetLatestMarkerState); \
	DECLARE_FUNCTION(execGetLatestRigidBodyState);


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execShutdownClient); \
	DECLARE_FUNCTION(execGetDataDescription); \
	DECLARE_FUNCTION(execInitializeClient); \
	DECLARE_FUNCTION(execIsClientConnected); \
	DECLARE_FUNCTION(execIsClientInitialized); \
	DECLARE_FUNCTION(execFindHmdClientOrigin); \
	DECLARE_FUNCTION(execFindDefaultClientOrigin); \
	DECLARE_FUNCTION(execGetLatestTimecode); \
	DECLARE_FUNCTION(execGetTimestampType); \
	DECLARE_FUNCTION(execGetLatestMarkerStateUntransformed); \
	DECLARE_FUNCTION(execGetLatestRigidBodyStateUntransformed); \
	DECLARE_FUNCTION(execFindSkeletonDefinition); \
	DECLARE_FUNCTION(execGetLatestSkeletonStateByName); \
	DECLARE_FUNCTION(execGetLatestSkeletonState); \
	DECLARE_FUNCTION(execGetLatestMarkerState); \
	DECLARE_FUNCTION(execGetLatestRigidBodyState);


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAOptitrackClientOrigin(); \
	friend struct Z_Construct_UClass_AOptitrackClientOrigin_Statics; \
public: \
	DECLARE_CLASS(AOptitrackClientOrigin, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/OptitrackNatnet"), NO_API) \
	DECLARE_SERIALIZER(AOptitrackClientOrigin)


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_INCLASS \
private: \
	static void StaticRegisterNativesAOptitrackClientOrigin(); \
	friend struct Z_Construct_UClass_AOptitrackClientOrigin_Statics; \
public: \
	DECLARE_CLASS(AOptitrackClientOrigin, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/OptitrackNatnet"), NO_API) \
	DECLARE_SERIALIZER(AOptitrackClientOrigin)


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AOptitrackClientOrigin(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AOptitrackClientOrigin) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOptitrackClientOrigin); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOptitrackClientOrigin); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AOptitrackClientOrigin(AOptitrackClientOrigin&&); \
	NO_API AOptitrackClientOrigin(const AOptitrackClientOrigin&); \
public:


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AOptitrackClientOrigin(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AOptitrackClientOrigin(AOptitrackClientOrigin&&); \
	NO_API AOptitrackClientOrigin(const AOptitrackClientOrigin&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOptitrackClientOrigin); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOptitrackClientOrigin); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AOptitrackClientOrigin)


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_129_PROLOG
#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_SPARSE_DATA \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_RPC_WRAPPERS \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_INCLASS \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_SPARSE_DATA \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_INCLASS_NO_PURE_DECLS \
	FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h_132_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class OptitrackClientOrigin."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> OPTITRACKNATNET_API UClass* StaticClass<class AOptitrackClientOrigin>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_HostProject_Plugins_OptitrackNatnet_Source_OptitrackNatnet_Classes_OptitrackClientOrigin_h


#define FOREACH_ENUM_EOPTITRACKTIMESTAMPTYPE(op) \
	op(EOptitrackTimestampType::Unknown) \
	op(EOptitrackTimestampType::LocalArrivalTime) \
	op(EOptitrackTimestampType::ServerAggregationTime) \
	op(EOptitrackTimestampType::ServerExposureTime) 

enum class EOptitrackTimestampType : uint8;
template<> OPTITRACKNATNET_API UEnum* StaticEnum<EOptitrackTimestampType>();

#define FOREACH_ENUM_EOPTITRACKCLIENTCONNECTIONTYPE(op) \
	op(EOptitrackClientConnectionType::Multicast) \
	op(EOptitrackClientConnectionType::Unicast) 

enum class EOptitrackClientConnectionType : uint8;
template<> OPTITRACKNATNET_API UEnum* StaticEnum<EOptitrackClientConnectionType>();

#define FOREACH_ENUM_EOPTITRACKFORWARDAXISTYPE(op) \
	op(EOptitrackForwardAxisType::Z_Positive) \
	op(EOptitrackForwardAxisType::X_Positive) 

enum class EOptitrackForwardAxisType : uint8;
template<> OPTITRACKNATNET_API UEnum* StaticEnum<EOptitrackForwardAxisType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
