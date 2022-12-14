// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LibsodiumUETypes.h"
#include "Types.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VaRestJsonValue.h"
#include "SuiUnrealSDKCoreBPLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FRpcResultReceivedDelegate, UVaRestJsonValue*, Result);

UCLASS()
class USuiUnrealSDKCoreBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetTotalTransactionNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable,Category = "Sui | Read")
	static void GetRecentTransactions(const FString& Endpoint, int64 Count, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetTransactionsInRange(const FString& Endpoint, int64 Start, int64 End, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void MoveCall(const FString& Endpoint, const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<UVaRestJsonValue*>& Arguments, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResult);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void SignAndExecuteTransaction(const FString& Endpoint, const FString& TxBytes, const FEd25519KeyPair KeyPair, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void TransferObject(const FString& Endpoint, const FString& Signer, const FString& ObjectId, const FString& Gas, int64 GasBudget, const FString& Recipient, const FRpcResultReceivedDelegate& OnResultReceived);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void TransferSui(const FString& Endpoint, const FString& Signer, const FString& SuiObjectId, int64 GasBudget, const FString& Recipient, int64 Amount, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void BatchTransaction(const FString& Endpoint, const FString& Signer, const TArray<UVaRestJsonValue*>& SingleTransactionParams, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void Pay(const FString& Endpoint, const FString& Signer, const TArray<FString>& InputCoinObjectIds, const TArray<FString>& Recipients, const TArray<int64>& Amounts, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void SplitCoin(const FString& Endpoint, const FString& Signer, const FString& CoinObjectId, const TArray<int64>& SplitAmounts, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void SplitCoinEqual(const FString& Endpoint, const FString& Signer, const FString& CoinObjectId, const int64 SplitCount, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void MergeCoins(const FString& Endpoint, const FString& Signer, const FString& PrimaryCoinId, const FString& CoinToMerge, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Crypto")
	static void CreateKeypairFromMnemonic(FEd25519KeyPair& KeyPair, const FString& Mnemonic);

	UFUNCTION(BlueprintCallable, Category = "Sui | Crypto")
	static void GenerateMnemonic(FString& Mnemonic);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsByModule(const FString& Endpoint, const FString& PackageId, const FString& ModuleName, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsByMoveEventStructName(const FString& Endpoint, const FString& MoveEventStructName, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsByObject(const FString& Endpoint, const FString& ObjectId, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsBySender(const FString& Endpoint, const FString& SenderAddress, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsByTimeRange(const FString& Endpoint, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Event Read")
	static void GetEventsByTransaction(const FString& Endpoint, const FString& Digest, int32 Count, const FRpcResultReceivedDelegate& OnResultReceived);
};

