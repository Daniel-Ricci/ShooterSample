// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterSample : ModuleRules
{
	public ShooterSample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ShooterSample",
			"ShooterSample/Variant_Platforming",
			"ShooterSample/Variant_Platforming/Animation",
			"ShooterSample/Variant_Combat",
			"ShooterSample/Variant_Combat/AI",
			"ShooterSample/Variant_Combat/Animation",
			"ShooterSample/Variant_Combat/Gameplay",
			"ShooterSample/Variant_Combat/Interfaces",
			"ShooterSample/Variant_Combat/UI",
			"ShooterSample/Variant_SideScrolling",
			"ShooterSample/Variant_SideScrolling/AI",
			"ShooterSample/Variant_SideScrolling/Gameplay",
			"ShooterSample/Variant_SideScrolling/Interfaces",
			"ShooterSample/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
