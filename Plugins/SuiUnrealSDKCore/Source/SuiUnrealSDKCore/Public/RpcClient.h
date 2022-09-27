// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuiTypes.h"

DECLARE_DELEGATE_OneParam(FRpcSuccessDelegate, const FJsonRpcValidResponse&);
DECLARE_DELEGATE_OneParam(FRpcErrorDelegate, const FJsonRpcErrorResponse&);

/**
 * 
 */
class SUIUNREALSDKCORE_API RpcClient
{
public:
	RpcClient(const FString& InEndpoint);
	FORCEINLINE const FString& GetEndpoint() const { return Endpoint; }

	void GetRecentTransactions(uint64 Count, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObjectsOwnedByAddress(const FString& Address, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObjectsOwnedByObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

private:
	void SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate(), const FRpcErrorDelegate& ErrorDelegate = FRpcErrorDelegate());

	FString Endpoint;
};
