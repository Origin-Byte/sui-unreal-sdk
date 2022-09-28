// Copyright Epic Games, Inc. All Rights Reserved.

#include "LibsodiumUE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "sodium.h"

#define LOCTEXT_NAMESPACE "FLibsodiumUEModule"

void FLibsodiumUEModule::StartupModule()
{
	sodium_init();
}

void FLibsodiumUEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLibsodiumUEModule, LibsodiumUE)
