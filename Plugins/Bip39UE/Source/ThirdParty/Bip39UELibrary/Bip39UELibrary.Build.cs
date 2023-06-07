// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class Bip39UELibrary : ModuleRules
{
	public Bip39UELibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Release", "x64", "bip39.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Release", "x64", "toolbox.lib"));
		}
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"LibsodiumUE"
			}
		);
	}
}
