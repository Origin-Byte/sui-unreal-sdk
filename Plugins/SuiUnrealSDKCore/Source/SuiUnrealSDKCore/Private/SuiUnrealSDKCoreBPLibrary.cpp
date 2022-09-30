// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiUnrealSDKCoreBPLibrary.h"
#include "Types.h"
#include "RpcClient.h"
#include "VaRestSubsystem.h"
#include "LibsodiumUE.h"
#include "Bip39UE.h"

USuiUnrealSDKCoreBPLibrary::USuiUnrealSDKCoreBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USuiUnrealSDKCoreBPLibrary::GetTotalTransactionNumber(const FString& Endpoint, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
	});
	Client.GetTotalTransactionNumber(RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetRecentTransactions(const FString& Endpoint, FKeshUInt64 Count, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetRecentTransactions(Count.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTransaction(Digest, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransactionsInRange(const FString& Endpoint, FKeshUInt64 Start, FKeshUInt64 End, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTransactionsInRange(Start.Value, End.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByAddress(const FString& Endpoint, const FString& Address, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObjectsOwnedByAddress(Address, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetObjectsOwnedByObject(const FString& Endpoint, const FString& ObjectId, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObjectsOwnedByObject(ObjectId, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::MoveCall(const FString& Endpoint, const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<UVaRestJsonValue*> Arguments, const FString& Gas, FKeshUInt64 GasBudget, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});

	TArray<TSharedPtr<FJsonValue>> ArgumentJsonValues;
	for(auto Arg : Arguments)
	{
		ArgumentJsonValues.Add(Arg->GetRootValue());
	}
	
	Client.MoveCall(Signer, PackageObjectId, Module, Function, TypeArguments, ArgumentJsonValues, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::SignAndExecuteTransaction(const FString& Endpoint, const FString& TxBytes, const FEd25519KeyPair KeyPair, const FRpcResultReceivedDelegate& OnResult)
{	
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	
	TArray<uint8> SignatureBytes;
	TArray<uint8> TxDecodedBytes;
	FBase64::Decode(TxBytes, TxDecodedBytes);
	
	FLibsodiumUEModule::Get().Sign(SignatureBytes, TxDecodedBytes, KeyPair.PrivateKey);
	
	const FString Signature = FBase64::Encode(SignatureBytes);
	
	Client.ExecuteTransaction(TxBytes, Signature, KeyPair.PublicKeyBase64, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::CreateKeypairFromMnemonic(FEd25519KeyPair& KeyPair, const FString& Mnemonic)
{
	TArray<uint8> Seed;
	// TODO validation
	FBip39UEModule::Get().MnemonicToSeed(Seed, Mnemonic, TEXT(""));
	FLibsodiumUEModule::Get().Ed25519KeyPairFromSeed(KeyPair, Seed);
}

void USuiUnrealSDKCoreBPLibrary::GenerateMnemonic(FString& Mnemonic)
{
	FBip39UEModule::Get().GenerateMnemonic(Mnemonic);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByModule(const FString& Endpoint, const FString& PackageId, const FString& ModuleName, FKeshUInt32 Count, FKeshUInt64 StartTime, FKeshUInt64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByModule(PackageId, ModuleName, Count.Value, StartTime.Value, EndTime.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByMoveEventStructName(const FString& Endpoint, const FString& MoveEventStructName, FKeshUInt32 Count, FKeshUInt64 StartTime, FKeshUInt64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByMoveEventStructName(MoveEventStructName, Count.Value, StartTime.Value, EndTime.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByObject(const FString& Endpoint, const FString& ObjectId, FKeshUInt32 Count, FKeshUInt64 StartTime, FKeshUInt64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByObject(ObjectId, Count.Value, StartTime.Value, EndTime.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsBySender(const FString& Endpoint, const FString& SenderAddress, FKeshUInt32 Count, FKeshUInt64 StartTime, FKeshUInt64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsBySender(SenderAddress, Count.Value, StartTime.Value, EndTime.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByTimeRange(const FString& Endpoint, FKeshUInt32 Count, FKeshUInt64 StartTime, FKeshUInt64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByTimeRange(Count.Value, StartTime.Value, EndTime.Value, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByTransaction(const FString& Endpoint, const FString& Digest, FKeshUInt32 Count, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByTransaction(Digest, Count.Value, RpcSuccessDelegate);
}