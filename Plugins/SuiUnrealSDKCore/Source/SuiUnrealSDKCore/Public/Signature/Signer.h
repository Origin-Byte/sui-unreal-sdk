#pragma once

#include "CoreMinimal.h"
#include "LibsodiumUETypes.h"
#include "Types.h"

/**
 * 
 */
class SUIUNREALSDKCORE_API FSigner
{
public:
	static FString GetAddress(const FEd25519KeyPair& KeyPair);
	static void SignMessage(const FEd25519KeyPair& KeyPair, const FString& Message, FSerializedSignature& OutSerializedSignature);
	static void SignData(const FEd25519KeyPair& KeyPair, const TArray<uint8>& Data, FSerializedSignature& OutSerializedSignature);
};