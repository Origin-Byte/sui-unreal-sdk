// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FLibsodiumUEModule : public IModuleInterface
{
public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FLibsodiumUEModule& Get() {
		return FModuleManager::LoadModuleChecked<FLibsodiumUEModule>("LibsodiumUE");
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("LibsodiumUE");
	}
};
