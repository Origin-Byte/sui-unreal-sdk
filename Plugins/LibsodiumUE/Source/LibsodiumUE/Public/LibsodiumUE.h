// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class LIBSODIUMUE_API FLibsodiumUEModule : public IModuleInterface
{
public:
	int32 Ed25519KeyPairFromSeed(TArray<uint8>& PublicKey, TArray<uint8>& PrivateKey, const TArray<uint8>& Seed);
	
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
