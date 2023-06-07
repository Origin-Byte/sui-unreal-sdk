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
	static void GetObject(const FString& Endpoint, const FString& ObjectId, const FObjectDataOptions& Options, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void MoveCall(const FString& Endpoint, const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<UVaRestJsonValue*>& Arguments, const FString& Gas, const FString& GasBudget, const FRpcResultReceivedDelegate& OnResult);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Transaction")
	static void SignAndExecuteTransactionBlock(const FString& Endpoint, const FString& TxBytes, const FEd25519KeyPair KeyPair, const FTransactionBlockResponseOptions& Options, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcResultReceivedDelegate& OnResult);

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
	static void GetEventsByTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResultReceived);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Extended")
	static void GetLatestCheckpointSequenceNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Extended")
	static void GetDynamicFields(const FString& Endpoint, const FString& ParentObjectId, const FString& Cursor, const int64 Limit, const FRpcResultReceivedDelegate& OnResultReceived);
	
	UFUNCTION(BlueprintCallable, Category = "Sui | Extended")
	static void GetDynamicFieldObject(const FString& Endpoint, const FString& ParentObjectId, const FString& DynamicFieldNameType, UVaRestJsonValue* DynamicFieldNameValue, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | CoinQuery")
	static void GetBalance(const FString& Endpoint, const FString& OwnerAddress, const FString& CoinType, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | CoinQuery")
	static void GetAllBalances(const FString& Endpoint, const FString& OwnerAddress, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | CoinQuery")
	static void GetAllCoins(const FString& Endpoint, const FString& OwnerAddress, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetTotalTransactionBlocks(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResultReceived);

	UFUNCTION(BlueprintCallable, Category = "Sui | Read")
	static void GetTransactionBlock(const FString& Endpoint, const FString& Digest, const FTransactionBlockResponseOptions& Options, const FRpcResultReceivedDelegate& OnResultReceived);

};

