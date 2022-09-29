// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class LibsodiumUELibrary : ModuleRules
{
	public LibsodiumUELibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src", "libsodium", "include"));
		
		PublicDefinitions.Add("SODIUM_STATIC=1");
		PublicDefinitions.Add("SODIUM_EXPORT=");
		
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Release", "x64", "libsodium.lib"));
		}     
	}
}
