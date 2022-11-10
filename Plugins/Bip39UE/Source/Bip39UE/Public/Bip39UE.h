// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class BIP39UE_API FBip39UEModule : public IModuleInterface
{
public:
	int32 MnemonicToSeed(TArray<uint8>& OutSeed, const FString& Mnemonic, const FString& Password);
	void GenerateMnemonic(FString& OutMnemonic);
	void DeriveKeyFromMnemonic(TArray<uint8>& PrivateKeyBytes, const FString& Mnemonic, const FString& DerivationPath = TEXT("m/44'/784'/0'/0'/0'"));
    void PublicKeyBytesToSuiAddress(FString& OutSuiAddress, const TArray<uint8>& PublicKeyBytes);

	static void FStringToByteArray(TArray<uint8>& OutResult, const FString& InString);
	static void UInt32ToBigEndianByteArray(TArray<uint8>& OutResult, uint32 InValue);
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FBip39UEModule& Get() {
		return FModuleManager::LoadModuleChecked<FBip39UEModule>("Bip39UE");
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("Bip39UE");
	}

private:
	void HmacSha512(TArray<uint8>& OutIL, TArray<uint8>& OutIR, const TArray<uint8>& InKey, const TArray<uint8>& InData);
	void GetMasterKeyFromSeed(TArray<uint8>& OutIL, TArray<uint8>& OutIR, const TArray<uint8>& InSeed);
	void GetDerivationPathIndexes(TArray<uint32>& OutIndexes, const FString& DerivationPath);
	void DerivePrivateChildKey(TArray<uint8>& IL, TArray<uint8>& IR, uint32 Index);
};
