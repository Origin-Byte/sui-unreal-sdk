#pragma once

#include "CoreMinimal.h"
#include "Types.h"

/**
 * 
 */
class SUIUNREALSDKCORE_API FSignatureHelper
{
public:
	static const TMap<SignatureScheme, uint8> SignatureSchemeToFlag;
	static const TMap<uint8, SignatureScheme> SignatureFlagToScheme;

	static void ToSerializedSignature(const FSignaturePubkeyPair& Pair, FSerializedSignature& OutSerializedSignature);
	static void FromSerializedSignature(const FSerializedSignature& SerializedSignature, FSignaturePubkeyPair& OutSignaturePubkeyPair);
};
