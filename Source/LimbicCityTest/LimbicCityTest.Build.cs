// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LimbicCityTest : ModuleRules
{
	public LimbicCityTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "UMG",
			"SlateCore",
			"Slate", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule",
			"Niagara", "EnhancedInput"
		});
	}
}