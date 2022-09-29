// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bip39UE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "bip39.h"

#define LOCTEXT_NAMESPACE "FBip39UEModule"

int FBip39UEModule::MnemonicToSeed(TArray<uint8>& OutSeed, const FString& Mnemonic, const FString& Password)
{
	OutSeed.SetNum(BIP39_SEED_LEN_512);
	size_t Written;
	return bip39_mnemonic_to_seed(TCHAR_TO_UTF8(*Mnemonic), Password.IsEmpty() ? nullptr : TCHAR_TO_UTF8(*Password), OutSeed.GetData(), BIP39_SEED_LEN_512, &Written);
}

void FBip39UEModule::StartupModule()
{
}

void FBip39UEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBip39UEModule, Bip39UE)
