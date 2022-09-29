// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LibsodiumUETypes.h"
#include "Modules/ModuleManager.h"

class LIBSODIUMUE_API FLibsodiumUEModule : public IModuleInterface
{
public:
	int32 Ed25519KeyPairFromSeed(TArray<uint8>& OutPublicKey, TArray<uint8>& OutPrivateKey, const TArray<uint8>& Seed);
	int32 Ed25519KeyPairFromSeed(FEd25519KeyPair& OutKeyPair, const TArray<uint8>& Seed);
	int32 Sign(TArray<uint8>& OutSignature, const TArray<uint8>& Message, const TArray<uint8>& PrivateKey);
	
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
