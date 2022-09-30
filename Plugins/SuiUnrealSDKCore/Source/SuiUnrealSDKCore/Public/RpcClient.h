// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

DECLARE_DELEGATE_OneParam(FRpcSuccessDelegate, const FJsonRpcValidResponse&);
DECLARE_DELEGATE_OneParam(FRpcErrorDelegate, const FJsonRpcErrorResponse&);

/**
 * 
 */
class SUIUNREALSDKCORE_API FRpcClient
{
public:
	FRpcClient(const FString& InEndpoint);
	FORCEINLINE const FString& GetEndpoint() const { return Endpoint; }

	void GetRecentTransactions(uint64 Count, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObjectsOwnedByAddress(const FString& Address, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObjectsOwnedByObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	void MoveCall(const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<TSharedPtr<FJsonValue>> Arguments, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate);
	void ExecuteTransaction(const FString& TxBytes, const FString& Signature, const FString& PublicKey, const FRpcSuccessDelegate& SuccessDelegate);

	void GetEventsByModule(const FString& PackageId, const FString& ModuleName, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetEventsByMoveEventStructName(const FString& MoveEventStructName, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetEventsByObject(const FString& ObjectId, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	// TODO Owner
	//void GetEventsByRecipient(const FObjectOwner& Owner, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetEventsBySender(const FString& SenderAddress, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetEventsByTimeRange(uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetEventsByTransaction(const FString& Digest, uint32 Count, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

private:
	void SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate(), const FRpcErrorDelegate& ErrorDelegate = FRpcErrorDelegate());

	FString Endpoint;
};
