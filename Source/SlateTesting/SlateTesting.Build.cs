// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlateTesting : ModuleRules
{
	public SlateTesting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { 
		"Engine",
        				"CoreUObject",
        				"Projects",
        				"UnrealEd",
        				"InputCore",
        				"SlateCore",
        				"Slate",
        				"EditorStyle",
        				"EditorWidgets",
        				"ToolMenus",
        				"ToolWidgets",
        				"AssetTools",
        				"GameplayTags",
        
        				"WorkspaceMenuStructure",
        				"DetailCustomizations",
        				"PropertyEditor",
        
        				"BlueprintGraph",
        				"Kismet",
        				"KismetCompiler",
        				"KismetWidgets",
        
        				"GraphEditor",
        				"ContentBrowser",
        
        				"ApplicationCore",
        				"AppFramework",
        				"MainFrame"
		 });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
