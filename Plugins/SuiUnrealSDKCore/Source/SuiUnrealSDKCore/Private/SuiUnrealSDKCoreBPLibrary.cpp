// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiUnrealSDKCoreBPLibrary.h"
#include "SuiUnrealSDKCore.h"
#include "Interfaces/IHttpRequest.h"
#include "PlatformHttp.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiTypes.h"
#include "RpcClient.h"

USuiUnrealSDKCoreBPLibrary::USuiUnrealSDKCoreBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USuiUnrealSDKCoreBPLibrary::GetTotalTransactionNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
	});
	Client.GetTotalTransactionNumber(RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetRecentTransactions(const FString& Endpoint, FKeshUInt64 Count, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetRecentTransactions(Count.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetTransaction(Digest, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransactionsInRange(const FString& Endpoint, FKeshUInt64 Start, FKeshUInt64 End, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetTransactionsInRange(Start.Value, End.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetObjectsOwnedByAddress(Address, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		OnResult.ExecuteIfBound(RpcResponse.Result);
		});
	Client.GetObjectsOwnedByObject(ObjectId, RpcSuccessDelegate);
}
