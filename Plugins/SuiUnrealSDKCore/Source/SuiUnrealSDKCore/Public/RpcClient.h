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
	
	void GetObject(const FString& ObjectId, const FObjectDataOptions& Options, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetOwnedObjects(const FString& Address, const FObjectResponseQuery& ResponseQuery, const FString& CursorId, const TOptional<uint64> Limit, const FRpcSuccessDelegate& SuccessDelegate);

	void MoveCall(const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<TSharedPtr<FJsonValue>>& Arguments, const FString& Gas, const FString& GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void ExecuteTransactionBlock(const FString& TxBytes, const TArray<FString>& SerializedSignatures, const FTransactionBlockResponseOptions& Options, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void TransferObject(const FString& Signer, const FString& ObjectId, const FString& Gas, uint64 GasBudget, const FString& Recipient, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void TransferSui(const FString& Signer, const FString& SuiObjectId, uint64 GasBudget, const FString& Recipient, uint64 Amount, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void BatchTransaction(const FString& Signer, const TArray<TSharedPtr<FJsonValue>>& SingleTransactionParams, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void Pay(const FString& Signer, const TArray<FString>& InputCoinObjectIds, const TArray<FString>& Recipients, const TArray<uint64>& Amounts, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void SplitCoin(const FString& Signer, const FString& CoinObjectId, const TArray<uint64>& SplitAmounts, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void SplitCoinEqual(const FString& Signer, const FString& CoinObjectId, const uint64 SplitCount, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void MergeCoins(const FString& Signer, const FString& PrimaryCoinId, const FString& CoinToMerge, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
		
	void GetEventsByModule(const FString& PackageId, const FString& ModuleName, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	void GetEventsByTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	// Extended API
	/**
	 * @brief Return the sequence number of the latest checkpoint that has been executed
	 * @param SuccessDelegate
	 */
	void GetLatestCheckpointSequenceNumber(const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	
	/**
	 * @brief Return the dynamic field object information for a specified object
	 * @param ParentObjectId
	 * @param DynamicFieldNameType
	 * @param DynamicFieldNameValue
	 * @param SuccessDelegate 
	 */
	void GetDynamicFieldObject(const FString& ParentObjectId, const FString& DynamicFieldNameType, const TSharedPtr<FJsonValue>& DynamicFieldNameValue, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	/**
	 * @brief Return the list of dynamic field objects owned by an object.
	 * @param ParentObjectId The ID of the parent object
	 * @param Cursor An optional paging cursor. If provided, the query will start from the next item after the specified cursor. Default to start from the first item if not specified.
	 * @param Limit Maximum item returned per page, default to [QUERY_MAX_RESULT_LIMIT] if not specified
	 * @param SuccessDelegate 
	 */
	void GetDynamicFields(const FString& ParentObjectId, const FString& Cursor, const TOptional<uint64> Limit, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	// CoinQuery API
	void GetBalance(const FString& OwnerAddress, const FString& CoinType, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetAllBalances(const FString& OwnerAddress, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetAllCoins(const FString& OwnerAddress, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	// Read API
	void GetTotalTransactionBlocks(const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransactionBlock(const FString& Digest, const FTransactionBlockResponseOptions& Options, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

	
private:
	void SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate(), const FRpcErrorDelegate& ErrorDelegate = FRpcErrorDelegate());

	FString Endpoint;
};
