#include "Signature/SignatureHelper.h"
#include "Types.h"

const TMap<SignatureScheme, uint8> FSignatureHelper::SignatureSchemeToFlag = {
	{ SignatureScheme::Ed25519, 0x00 },
	{ SignatureScheme::Secp256k1, 0x01 }
};

const TMap<uint8, SignatureScheme> FSignatureHelper::SignatureFlagToScheme = {
	{ 0x00, SignatureScheme::Ed25519 },
	{ 0x01, SignatureScheme::Secp256k1 }
};

void FSignatureHelper::ToSerializedSignature(const FSignaturePubkeyPair& Pair, FSerializedSignature& OutSerializedSignature)
{
	TArray<uint8> List;
	List.Add(SignatureSchemeToFlag[Pair.Scheme]);
	List.Append(Pair.Signature);

	// Decode the Base64 string to bytes.
	TArray<uint8> PubKeyBytes;
	FBase64::Decode(Pair.PubKey, PubKeyBytes);

	List.Append(PubKeyBytes);

	// Convert the bytes back to a Base64 string.
	OutSerializedSignature.Value = FBase64::Encode(List);
}

void FSignatureHelper::FromSerializedSignature(const FSerializedSignature& SerializedSignature, FSignaturePubkeyPair& OutSignaturePubkeyPair)
{
	// Decode the Base64 string to bytes.
	TArray<uint8> Bytes;
	FBase64::Decode(SerializedSignature.Value, Bytes);

	SignatureScheme Scheme = SignatureFlagToScheme[Bytes[0]];

	// Define public key size based on signature scheme
	int32 PubKeySize = Scheme == SignatureScheme::Ed25519 ? 32 : 33;

	// Slice signature bytes from array, skipping the first byte (scheme flag)
	// and stopping before the last pubKeySize bytes (public key)
	TArray<uint8> Signature(Bytes.GetData() + 1, Bytes.Num() - PubKeySize - 1);

	// Slice public key bytes from array, skipping the first byte (scheme flag)
	// and the signature bytes
	TArray<uint8> PubkeyBytes(Bytes.GetData() + Signature.Num() + 1, PubKeySize);

	OutSignaturePubkeyPair.Scheme = Scheme;
	OutSignaturePubkeyPair.Signature = Signature;
	OutSignaturePubkeyPair.PubKey = FBase64::Encode(PubkeyBytes);
}