// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bip39UE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "bip3x/bip39.h"
#include "bip3x/Bip39Mnemonic.h"
#include "bip3x/HDKeyEncoder.h"
#include "bip3x/utils.h"

#define LOCTEXT_NAMESPACE "FBip39UEModule"

int32 FBip39UEModule::MnemonicToSeed(TArray<uint8>& OutSeed, const FString& Mnemonic, const FString& Password)
{
	OutSeed.SetNum(BIP39_SEED_LEN_512);
	size_t Written;
	return bip39_mnemonic_to_seed(TCHAR_TO_UTF8(*Mnemonic), Password.IsEmpty() ? nullptr : TCHAR_TO_UTF8(*Password), OutSeed.GetData(), BIP39_SEED_LEN_512, &Written);
}

// Derive Ed25519 keypair from mnemonics and path.
// Based on: [SLIP-0010](https://github.com/satoshilabs/slips/blob/master/slip-0010.md)
// If path is none, it will default to m/44'/784'/0'/0'/0', otherwise the path must
// be compliant to SLIP-0010 in form m/44'/784'/{account_index}'/{change_index}'/{address_index}'.
void FBip39UEModule::DeriveKeyFromMnemonic(TArray<uint8>& PrivateKeyBytes,  const FString& Mnemonic, const FString& DerivationPath)
{
	TArray<uint8> Seed;
	MnemonicToSeed(Seed, Mnemonic, TEXT(""));

	TArray<uint8> IR;

	GetMasterKeyFromSeed(PrivateKeyBytes, IR, Seed);

	TArray<uint32> Indexes;
	GetDerivationPathIndexes(Indexes, DerivationPath);
	
	const uint32 HardenedIndexOffset = 0x80000000;

	for(const auto Index : Indexes)
	{
		const auto HardenedIndex = HardenedIndexOffset | Index;
		DerivePrivateChildKey(PrivateKeyBytes, IR,  HardenedIndex);		
	}
}

void FBip39UEModule::HmacSha512(TArray<uint8>& OutIL, TArray<uint8>& OutIR, const TArray<uint8>& InKey, const TArray<uint8>& InData)
{
	TArray<uint8> I;
	I.SetNum(64);
	hmac_sha512(InKey.GetData(), InKey.Num(), InData.GetData(), InData.Num(), I.GetData());
	OutIL.Empty();
	OutIR.Empty();
	OutIL.Append(&I[0], 32);
	OutIR.Append(&I[32], 32);
}

void FBip39UEModule::GetMasterKeyFromSeed(TArray<uint8>& OutIL, TArray<uint8>& OutIR, const TArray<uint8>& InSeed)
{
	TArray<uint8> CurveBytes;
	FStringToByteArray(CurveBytes, TEXT("ed25519 seed"));
	HmacSha512(OutIL, OutIR, CurveBytes, InSeed);	
}

void FBip39UEModule::FStringToByteArray(TArray<uint8>& OutResult, const FString& InString)
{
	for( int i = 0; i < InString.Len(); i++)
	{
		const uint8* character = (uint8*)TCHAR_TO_UTF8(*InString.Mid(i,1));
		OutResult.Add( *character );
	}
}

void FBip39UEModule::UInt32ToBigEndianByteArray(TArray<uint8>& OutResult, uint32 InValue)
{
	OutResult.Add((InValue >> 24) & 0xff);
	OutResult.Add((InValue >> 16) & 0xff);
	OutResult.Add((InValue >> 8) & 0xff);
	OutResult.Add((InValue & 0xff));
}

void FBip39UEModule::GetDerivationPathIndexes(TArray<uint32>& OutIndexes, const FString& DerivationPath)
{
	TArray<FString> PathSegments;
	DerivationPath.ParseIntoArray(PathSegments, TEXT("/"));
	auto FilteredPathSegments = PathSegments.FilterByPredicate([](const FString& Segment) { return Segment.Len() > 1; });
	for(const auto& Segment : FilteredPathSegments)
	{
		uint32 Index = FCString::Strtoi(*Segment, nullptr, 10);
		OutIndexes.Add(Index);
	}
}

void FBip39UEModule::DerivePrivateChildKey(TArray<uint8>& IL, TArray<uint8>& IR, uint32 Index)
{
	TArray<uint8> Buffer;
	Buffer.Add(0);
	Buffer.Append(IL);
	UInt32ToBigEndianByteArray(Buffer, Index);

	HmacSha512(IL, IR, IR, Buffer);
}

void FBip39UEModule::GenerateMnemonic(FString& OutMnemonic)
{
	const auto [status, words, raw, len] = bip3x::Bip39Mnemonic::generate("en", BIP39_ENTROPY_LEN_128);

	for(int i = 0; i < words.size(); i++)
	{
		auto Word = words[i];
		OutMnemonic.Append(UTF8_TO_TCHAR(Word.c_str()));

		if (i < words.size() - 1)
		{
			OutMnemonic.Append(TEXT(" "));
		}
	}
}

void FBip39UEModule::PublicKeyBytesToSuiAddress(FString& OutSuiAddress, const TArray<uint8>& PublicKeyBytes)
{
	TArray<uint8> TmpBytes;
	TmpBytes.Add(0x00);
	TmpBytes.Append(PublicKeyBytes);
	TArray<uint8> Digest;
	Digest.SetNum(64);
	sha3_256(TmpBytes.GetData(), TmpBytes.Num(), Digest.GetData());
	OutSuiAddress = FString(TEXT("0x"));
	OutSuiAddress.Append(BytesToHex(Digest.GetData(), Digest.Num()).Left(40));
	OutSuiAddress.ToLowerInline();
}

void FBip39UEModule::StartupModule()
{
}

void FBip39UEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBip39UEModule, Bip39UE)
