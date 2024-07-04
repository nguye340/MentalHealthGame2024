// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MentalHealthGame2024 : ModuleRules
{
	public MentalHealthGame2024(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{	
				// Default Modules
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore",

				// New Modules
				"Json", // Add the Json module
                "JsonUtilities" // Add the JsonUtilities module
			});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
