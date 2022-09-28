// Copyright Epic Games, Inc. All Rights Reserved.

#include "LibsodiumUE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FLibsodiumUEModule"

void FLibsodiumUEModule::StartupModule()
{
}

void FLibsodiumUEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLibsodiumUEModule, LibsodiumUE)
