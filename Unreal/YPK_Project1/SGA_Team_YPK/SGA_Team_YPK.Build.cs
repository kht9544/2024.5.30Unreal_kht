// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SGA_Team_YPK : ModuleRules
{
	public SGA_Team_YPK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "NavigationSystem", "AIModule", "GameplayTasks", "Niagara", "MovieScene", "LevelSequence" });

		PrivateDependencyModuleNames.AddRange(new string[] {});

		PublicIncludePaths.AddRange(new string[] {
			"SGA_Team_YPK/AI",
			"SGA_Team_YPK/Player",
			"SGA_Team_YPK/Creature",
			"SGA_Team_YPK/Monster",
			"SGA_Team_YPK/Animation",
			"SGA_Team_YPK/Base",
			"SGA_Team_YPK/Component",
			"SGA_Team_YPK/Item",
			"SGA_Team_YPK/Manager",
			"SGA_Team_YPK/NPC",
			"SGA_Team_YPK/UI",
			"SGA_Team_YPK/VFX"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
