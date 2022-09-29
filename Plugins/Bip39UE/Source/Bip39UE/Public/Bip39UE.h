// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class BIP39UE_API FBip39UEModule : public IModuleInterface
{
public:
	int MnemonicToSeed(TArray<uint8>& OutSeed, const FString& Mnemonic, const FString& Password);
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FBip39UEModule& Get() {
		return FModuleManager::LoadModuleChecked<FBip39UEModule>("Bip39UE");
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("Bip39UE");
	}
};
