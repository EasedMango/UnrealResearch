// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OptitrackLiveLink/Public/OptitrackLiveLinkDisplay.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOptitrackLiveLinkDisplay() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	OPTITRACKLIVELINK_API UClass* Z_Construct_UClass_AOptitrackLiveLinkDisplay();
	OPTITRACKLIVELINK_API UClass* Z_Construct_UClass_AOptitrackLiveLinkDisplay_NoRegister();
	UPackage* Z_Construct_UPackage__Script_OptitrackLiveLink();
// End Cross Module References
	void AOptitrackLiveLinkDisplay::StaticRegisterNativesAOptitrackLiveLinkDisplay()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AOptitrackLiveLinkDisplay);
	UClass* Z_Construct_UClass_AOptitrackLiveLinkDisplay_NoRegister()
	{
		return AOptitrackLiveLinkDisplay::StaticClass();
	}
	struct Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mDrawSkeletons_MetaData[];
#endif
		static void NewProp_mDrawSkeletons_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_mDrawSkeletons;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mSkeletonColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_mSkeletonColor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mLineThicknessScale_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_mLineThicknessScale;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mDrawRigidBodies_MetaData[];
#endif
		static void NewProp_mDrawRigidBodies_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_mDrawRigidBodies;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mRigidBodyColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_mRigidBodyColor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mDrawLabeledMarkers_MetaData[];
#endif
		static void NewProp_mDrawLabeledMarkers_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_mDrawLabeledMarkers;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mLabeledMarkerColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_mLabeledMarkerColor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mDrawUnlabeledMarkers_MetaData[];
#endif
		static void NewProp_mDrawUnlabeledMarkers_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_mDrawUnlabeledMarkers;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mUnlabeledMarkerColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_mUnlabeledMarkerColor;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_OptitrackLiveLink,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "OptitrackLiveLinkDisplay.h" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Display streamed skeleton data visuals */" },
		{ "DisplayName", "Display Skeleton Data" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Display streamed skeleton data visuals" },
	};
#endif
	void Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons_SetBit(void* Obj)
	{
		((AOptitrackLiveLinkDisplay*)Obj)->mDrawSkeletons = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons = { "mDrawSkeletons", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AOptitrackLiveLinkDisplay), &Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons_SetBit, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mSkeletonColor_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Skeleton color */" },
		{ "DisplayName", "Skeleton Color" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Skeleton color" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mSkeletonColor = { "mSkeletonColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AOptitrackLiveLinkDisplay, mSkeletonColor), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mSkeletonColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mSkeletonColor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLineThicknessScale_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Line thickness */" },
		{ "DisplayName", "Line Thickness" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Line thickness" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLineThicknessScale = { "mLineThicknessScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AOptitrackLiveLinkDisplay, mLineThicknessScale), METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLineThicknessScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLineThicknessScale_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Display streamed rigid body data visuals */" },
		{ "DisplayName", "Display Rigid Body Data" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Display streamed rigid body data visuals" },
	};
#endif
	void Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies_SetBit(void* Obj)
	{
		((AOptitrackLiveLinkDisplay*)Obj)->mDrawRigidBodies = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies = { "mDrawRigidBodies", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AOptitrackLiveLinkDisplay), &Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies_SetBit, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mRigidBodyColor_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Rigid body color */" },
		{ "DisplayName", "Rigid Body Color" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Rigid body color" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mRigidBodyColor = { "mRigidBodyColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AOptitrackLiveLinkDisplay, mRigidBodyColor), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mRigidBodyColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mRigidBodyColor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Display streamed labeled marker data visuals */" },
		{ "DisplayName", "Display Labeled Marker Data" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Display streamed labeled marker data visuals" },
	};
#endif
	void Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers_SetBit(void* Obj)
	{
		((AOptitrackLiveLinkDisplay*)Obj)->mDrawLabeledMarkers = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers = { "mDrawLabeledMarkers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AOptitrackLiveLinkDisplay), &Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers_SetBit, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLabeledMarkerColor_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Labeled marker color */" },
		{ "DisplayName", "Labeled Marker Color" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Labeled marker color" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLabeledMarkerColor = { "mLabeledMarkerColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AOptitrackLiveLinkDisplay, mLabeledMarkerColor), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLabeledMarkerColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLabeledMarkerColor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Display streamed unlabeled marker data visuals */" },
		{ "DisplayName", "Display Unlabeled Marker Data" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Display streamed unlabeled marker data visuals" },
	};
#endif
	void Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers_SetBit(void* Obj)
	{
		((AOptitrackLiveLinkDisplay*)Obj)->mDrawUnlabeledMarkers = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers = { "mDrawUnlabeledMarkers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AOptitrackLiveLinkDisplay), &Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers_SetBit, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mUnlabeledMarkerColor_MetaData[] = {
		{ "Category", "Optitrack" },
		{ "Comment", "/** Unlabeled marker color */" },
		{ "DisplayName", "Unlabeled Marker Color" },
		{ "ModuleRelativePath", "Public/OptitrackLiveLinkDisplay.h" },
		{ "ToolTip", "Unlabeled marker color" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mUnlabeledMarkerColor = { "mUnlabeledMarkerColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AOptitrackLiveLinkDisplay, mUnlabeledMarkerColor), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mUnlabeledMarkerColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mUnlabeledMarkerColor_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawSkeletons,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mSkeletonColor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLineThicknessScale,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawRigidBodies,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mRigidBodyColor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawLabeledMarkers,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mLabeledMarkerColor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mDrawUnlabeledMarkers,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::NewProp_mUnlabeledMarkerColor,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AOptitrackLiveLinkDisplay>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::ClassParams = {
		&AOptitrackLiveLinkDisplay::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AOptitrackLiveLinkDisplay()
	{
		if (!Z_Registration_Info_UClass_AOptitrackLiveLinkDisplay.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AOptitrackLiveLinkDisplay.OuterSingleton, Z_Construct_UClass_AOptitrackLiveLinkDisplay_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AOptitrackLiveLinkDisplay.OuterSingleton;
	}
	template<> OPTITRACKLIVELINK_API UClass* StaticClass<AOptitrackLiveLinkDisplay>()
	{
		return AOptitrackLiveLinkDisplay::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AOptitrackLiveLinkDisplay);
	struct Z_CompiledInDeferFile_FID_UE_plugin_OptitrackLiveLink_HostProject_Plugins_OptitrackLiveLink_Source_OptitrackLiveLink_Public_OptitrackLiveLinkDisplay_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE_plugin_OptitrackLiveLink_HostProject_Plugins_OptitrackLiveLink_Source_OptitrackLiveLink_Public_OptitrackLiveLinkDisplay_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AOptitrackLiveLinkDisplay, AOptitrackLiveLinkDisplay::StaticClass, TEXT("AOptitrackLiveLinkDisplay"), &Z_Registration_Info_UClass_AOptitrackLiveLinkDisplay, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AOptitrackLiveLinkDisplay), 2928368253U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE_plugin_OptitrackLiveLink_HostProject_Plugins_OptitrackLiveLink_Source_OptitrackLiveLink_Public_OptitrackLiveLinkDisplay_h_791309251(TEXT("/Script/OptitrackLiveLink"),
		Z_CompiledInDeferFile_FID_UE_plugin_OptitrackLiveLink_HostProject_Plugins_OptitrackLiveLink_Source_OptitrackLiveLink_Public_OptitrackLiveLinkDisplay_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE_plugin_OptitrackLiveLink_HostProject_Plugins_OptitrackLiveLink_Source_OptitrackLiveLink_Public_OptitrackLiveLinkDisplay_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
