#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SUIUNREALSDKCORE_API FIntentHelper
{
public:
	static void GetMessageWithIntent(const FString& Message, TArray<uint8>& OutMessageWithIntent)
	{
		// Decode the Base64 string to bytes.
		TArray<uint8> MessageBytes;
		FBase64::Decode(Message, MessageBytes);

		GetMessageWithIntent(MessageBytes, OutMessageWithIntent);
	}

	static void GetMessageWithIntent(const TArray<uint8>& Message, TArray<uint8>& OutMessageWithIntent)
	{
		// See: sui/crates/sui-types/src/intent.rs 
		// This is currently hardcoded with [IntentScope::TransactionData = 0, Version::V0 = 0, AppId::Sui = 0]
		const TArray<uint8> IntentBytes = { 0, 0, 0 };

		OutMessageWithIntent.Reset();
		OutMessageWithIntent.Append(IntentBytes);
		OutMessageWithIntent.Append(Message);
	}
};
