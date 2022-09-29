// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bip39UE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "bip3x/bip39.h"
//#include "bip3x/Bip39Mnemonic.h"

#define LOCTEXT_NAMESPACE "FBip39UEModule"

int32 FBip39UEModule::MnemonicToSeed(TArray<uint8>& OutSeed, const FString& Mnemonic, const FString& Password)
{
	OutSeed.SetNum(BIP39_SEED_LEN_512);
	size_t Written;
	return bip39_mnemonic_to_seed(TCHAR_TO_UTF8(*Mnemonic), Password.IsEmpty() ? nullptr : TCHAR_TO_UTF8(*Password), OutSeed.GetData(), BIP39_SEED_LEN_512, &Written);
}

void FBip39UEModule::GenerateMnemonic(FString& OutMnemonic)
{
	// const auto [status, words, raw, len] = bip3x::Bip39Mnemonic::generate("en", 128);
	//
	// for(int i = 0; i < words.size(); i++)
	// {
	// 	auto Word = words[i];
	// 	OutMnemonic.Append(Word.c_str());
	//
	// 	if (i < words.size() - 1)
	// 	{
	// 		OutMnemonic.Append(TEXT(" "));
	// 	}
	// }
}

void FBip39UEModule::StartupModule()
{
}

void FBip39UEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBip39UEModule, Bip39UE)
