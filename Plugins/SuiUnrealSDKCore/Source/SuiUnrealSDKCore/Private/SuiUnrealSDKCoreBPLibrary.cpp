// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiUnrealSDKCoreBPLibrary.h"
#include "RpcTypes.h"
#include "RpcClient.h"
#include "VaRestSubsystem.h"
#include "LibsodiumUE.h"
#include "SuiUnrealSDKCore.h"

USuiUnrealSDKCoreBPLibrary::USuiUnrealSDKCoreBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USuiUnrealSDKCoreBPLibrary::GetTotalTransactionNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
	});
	Client.GetTotalTransactionNumber(RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetRecentTransactions(const FString& Endpoint, FKeshUInt64 Count, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetRecentTransactions(Count.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTransaction(Digest, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransactionsInRange(const FString& Endpoint, FKeshUInt64 Start, FKeshUInt64 End, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTransactionsInRange(Start.Value, End.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObjectsOwnedByAddress(Address, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObjectsOwnedByObject(ObjectId, RpcSuccessDelegate);
}
