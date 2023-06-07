// Copyright Epic Games, Inc. All Rights Reserved.

#include "LibsodiumUE.h"
#include "Modules/ModuleManager.h"
#include "sodium.h"
#include "Misc/Base64.h"

#define LOCTEXT_NAMESPACE "FLibsodiumUEModule"

int32 FLibsodiumUEModule::Ed25519KeyPairFromSeed(TArray<uint8>& OutPublicKey, TArray<uint8>& OutPrivateKey, const TArray<uint8>& Seed)
{
	OutPublicKey.SetNum(crypto_sign_ed25519_PUBLICKEYBYTES);
	OutPrivateKey.SetNum(crypto_sign_ed25519_SECRETKEYBYTES);

	// Don't modify original seed, but we only use 32 bytes
	TArray<uint8> TmpSeed = Seed;
	TmpSeed.SetNum(32);
	
	return crypto_sign_ed25519_seed_keypair(OutPublicKey.GetData(), OutPrivateKey.GetData(), TmpSeed.GetData());
}

int32 FLibsodiumUEModule::Ed25519KeyPairFromSeed(FEd25519KeyPair& OutKeyPair, const TArray<uint8>& Seed)
{
	int32 Result = Ed25519KeyPairFromSeed(OutKeyPair.PublicKey, OutKeyPair.PrivateKey, Seed);
	OutKeyPair.Seed = Seed;
	OutKeyPair.PublicKeyBase64 = FBase64::Encode(OutKeyPair.PublicKey);
	TArray<uint8> First32PrivateKeyBytes;
	for (int i = 0; i < 32; ++i)
	{
		First32PrivateKeyBytes.Add(OutKeyPair.PrivateKey[i]);
	}
	OutKeyPair.PrivateKeyBase64 = FBase64::Encode(First32PrivateKeyBytes);
	
	return Result;
}

int32 FLibsodiumUEModule::Sign(TArray<uint8>& OutSignature, const TArray<uint8>& Message, const TArray<uint8>& PrivateKey)
{
	uint64 SignatureLength;
	OutSignature.SetNum(64);
	return crypto_sign_ed25519_detached(OutSignature.GetData(), &SignatureLength, Message.GetData(), Message.Num(), PrivateKey.GetData());
}

void FLibsodiumUEModule::ComputeBlake2bHash(const TArray<uint8>& Data, TArray<uint8>& OutDigest)
{
	OutDigest.SetNum(crypto_generichash_blake2b_BYTES);

	// Initialize the state with the desired parameters.
	crypto_generichash_blake2b_state State;
	crypto_generichash_blake2b_init(&State, nullptr, 0, OutDigest.Num());

	// Update the state with the input data.
	crypto_generichash_blake2b_update(&State, Data.GetData(), Data.Num());

	// Get the hash.
	crypto_generichash_blake2b_final(&State, OutDigest.GetData(), OutDigest.Num());
}

void FLibsodiumUEModule::StartupModule()
{
	sodium_init();
}

void FLibsodiumUEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLibsodiumUEModule, LibsodiumUE)
