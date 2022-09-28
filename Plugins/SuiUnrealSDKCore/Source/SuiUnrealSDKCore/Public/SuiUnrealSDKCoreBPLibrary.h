// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt64.h"
#include "RpcTypes.h"
#include "SuiUnrealSDKCoreBPLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FRpcResultReceivedDelegate, UVaRestJsonValue*, Result);

UCLASS()
class USuiUnrealSDKCoreBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetTotalTransactionNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable,Category = "Sui")
	static void GetRecentTransactions(const FString& Endpoint, FKeshUInt64 Count, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetTransactionsInRange(const FString& Endpoint, FKeshUInt64 Start, FKeshUInt64 End, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult);

	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void MoveCall(const FString& Endpoint, const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<UVaRestJsonValue*> Arguments, const FString& Gas, FKeshUInt64 GasBudget, const FRpcResultReceivedDelegate& OnResult);
	
	UFUNCTION(BlueprintCallable, Category = "Sui")
	static void ExecuteTransaction(const FString& Endpoint, const FString& TxBytes, const FString& Signature, const FString& PublicKey, const FRpcResultReceivedDelegate& OnResult);
};

