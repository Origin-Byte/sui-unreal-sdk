#include "Signature/Signer.h"

#include "LibsodiumUE.h"
#include "LibsodiumUETypes.h"
#include "Types.h"
#include "Signature/SignatureHelper.h"

FString FSigner::GetAddress(const FEd25519KeyPair& KeyPair)
{
	return KeyPair.PublicKeyAsSuiAddress;
}

void FSigner::SignMessage(const FEd25519KeyPair& KeyPair, const FString& Message, FSerializedSignature& OutSerializedSignature)
{
	TArray<uint8> MessageBytes;
	FBase64::Decode(Message, MessageBytes);
	SignData(KeyPair, MessageBytes, OutSerializedSignature);
}

void FSigner::SignData(const FEd25519KeyPair& KeyPair, const TArray<uint8>& Data, FSerializedSignature& OutSerializedSignature)
{
	TArray<uint8> Digest;
	FLibsodiumUEModule::Get().ComputeBlake2bHash(Data, Digest);
	TArray<uint8> Signature;
	FLibsodiumUEModule::Get().Sign(Signature, Digest, KeyPair.PrivateKey);

	FSignaturePubkeyPair SignaturePubkeyPair;
	SignaturePubkeyPair.Scheme = SignatureScheme::Ed25519; // only supported now
	SignaturePubkeyPair.Signature = Signature;
	SignaturePubkeyPair.PubKey = KeyPair.PublicKeyBase64;	
	
	FSignatureHelper::ToSerializedSignature(SignaturePubkeyPair, OutSerializedSignature);
}