// Copyright Epic Games, Inc. All Rights Reserved.

#include "LibsodiumUE.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "sodium.h"

#define LOCTEXT_NAMESPACE "FLibsodiumUEModule"

int32 FLibsodiumUEModule::Ed25519KeyPairFromSeed(TArray<uint8>& PublicKey, TArray<uint8>& PrivateKey, const TArray<uint8>& Seed)
{
	PublicKey.SetNum(crypto_sign_ed25519_PUBLICKEYBYTES);
	PrivateKey.SetNum(crypto_sign_ed25519_SECRETKEYBYTES);

	// Don't modify original seed, but we only use 32 bytes
	TArray<uint8> TmpSeed = Seed;
	TmpSeed.SetNum(32);
	
	return crypto_sign_ed25519_seed_keypair(PublicKey.GetData(), PrivateKey.GetData(), TmpSeed.GetData());
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
