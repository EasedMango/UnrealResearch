// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AssignmentOne : ModuleRules
{
	public AssignmentOne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","OnlineSubsystem","OnlineSubsystemNull" });
		
		PrivateDependencyModuleNames.AddRange(new string[] {"OnlineSubsystem","OnlineSubsystemNull"});
	}
}
