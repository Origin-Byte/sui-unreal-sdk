#pragma once

#include "CoreMinimal.h"
#include "LibsodiumUETypes.generated.h"

USTRUCT(BlueprintType)
struct LIBSODIUMUE_API FEd25519KeyPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Sui")
	TArray<uint8> PrivateKey;

	UPROPERTY(BlueprintReadOnly, Category = "Sui")
	TArray<uint8> PublicKey;

	UPROPERTY(BlueprintReadOnly, Category = "Sui")
	FString PrivateKeyBase64;

	UPROPERTY(BlueprintReadOnly, Category = "Sui")
	FString PublicKeyBase64;

	// The seed which the keypair was derived from
	UPROPERTY(BlueprintReadOnly, Category = "Sui")
	TArray<uint8> Seed;
};