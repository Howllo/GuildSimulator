// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GuildSimulator : ModuleRules
{
	public GuildSimulator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "UMG", "Slate", "SlateCore" });
	}
}
