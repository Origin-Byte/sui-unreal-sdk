// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiUnrealSDKCoreBPLibrary.h"
#include "Types.h"
#include "RpcClient.h"
#include "VaRestSubsystem.h"
#include "LibsodiumUE.h"
#include "Bip39UE.h"
#include "Signature/IntentHelper.h"
#include "Signature/Signer.h"

USuiUnrealSDKCoreBPLibrary::USuiUnrealSDKCoreBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USuiUnrealSDKCoreBPLibrary::GetObject(const FString& Endpoint, const FString& ObjectId, const FObjectDataOptions& Options, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetObject(ObjectId, Options, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetOwnedObjects(const FString& Endpoint, const FString& Address,
	const FObjectResponseQuery& ResponseQuery, const FString& CursorId, int64 Limit,
	const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});
	Client.GetOwnedObjects(Address, ResponseQuery, CursorId, Limit, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::MoveCall(const FString& Endpoint, const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<UVaRestJsonValue*>& Arguments, const FString& Gas, const FString& GasBudget, const FRpcResultReceivedDelegate& OnResult)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});

	TArray<TSharedPtr<FJsonValue>> ArgumentJsonValues;
	for(const auto Arg : Arguments)
	{
		ArgumentJsonValues.Add(Arg->GetRootValue());
	}
	
	Client.MoveCall(Signer, PackageObjectId, Module, Function, TypeArguments, ArgumentJsonValues, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::SignAndExecuteTransactionBlock(const FString& Endpoint, const FString& TxBytes, const FEd25519KeyPair KeyPair, const FTransactionBlockResponseOptions& Options, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcResultReceivedDelegate& OnResult)
{	
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResult.ExecuteIfBound(VaJsonValue);
		});

	TArray<uint8> MessageWithIntent;
	FIntentHelper::GetMessageWithIntent(TxBytes, MessageWithIntent);
	
	FSerializedSignature SerializedSignature;
	FSigner::SignData(KeyPair, MessageWithIntent, SerializedSignature);
	
	TArray<FString> Signatures;
	Signatures.Add(SerializedSignature.Value);
	
	Client.ExecuteTransactionBlock(TxBytes, Signatures, Options, ExecuteTransactionRequestType, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::TransferObject(const FString& Endpoint, const FString& Signer, const FString& ObjectId, const FString& Gas, int64 GasBudget, const FString& Recipient, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.TransferObject(Signer, ObjectId, Gas, GasBudget, Recipient, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::TransferSui(const FString& Endpoint, const FString& Signer, const FString& SuiObjectId, int64 GasBudget, const FString& Recipient, int64 Amount, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.TransferSui(Signer, SuiObjectId, GasBudget, Recipient, Amount, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::BatchTransaction(const FString& Endpoint, const FString& Signer, const TArray<UVaRestJsonValue*>& SingleTransactionParams, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	TArray<TSharedPtr<FJsonValue>> SingleTransactionParamsJsonValues;
	for(const auto Param : SingleTransactionParams)
	{
		SingleTransactionParamsJsonValues.Add(Param->GetRootValue());
	}

	Client.BatchTransaction(Signer, SingleTransactionParamsJsonValues, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::Pay(const FString& Endpoint, const FString& Signer, const TArray<FString>& InputCoinObjectIds, const TArray<FString>& Recipients, const TArray<int64>& Amounts, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});

	TArray<uint64> UintAmounts;
	for(const auto Amount : Amounts)
	{
		UintAmounts.Add(Amount);
	}
	
	Client.Pay(Signer, InputCoinObjectIds, Recipients, UintAmounts, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::SplitCoin(const FString& Endpoint, const FString& Signer, const FString& CoinObjectId, const TArray<int64>& SplitAmounts, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});

	TArray<uint64> UintAmounts;
	for(const auto Amount : SplitAmounts)
	{
		UintAmounts.Add(Amount);
	}
	
	Client.SplitCoin(Signer, CoinObjectId, UintAmounts, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::SplitCoinEqual(const FString& Endpoint, const FString& Signer, const FString& CoinObjectId, const int64 SplitCount, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.SplitCoinEqual(Signer, CoinObjectId, SplitCount, Gas, GasBudget, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::MergeCoins(const FString& Endpoint, const FString& Signer, const FString& PrimaryCoinId, const FString& CoinToMerge, const FString& Gas, int64 GasBudget, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.MergeCoins(Signer, PrimaryCoinId, CoinToMerge, Gas, GasBudget, RpcSuccessDelegate);	
}

void USuiUnrealSDKCoreBPLibrary::CreateKeypairFromMnemonic(FEd25519KeyPair& KeyPair, const FString& Mnemonic)
{
	TArray<uint8> Seed;
	// TODO validation
	FBip39UEModule::Get().DeriveKeyFromMnemonic(Seed, Mnemonic);
	//FBip39UEModule::Get().MnemonicToSeed(Seed, Mnemonic, TEXT(""));
	FLibsodiumUEModule::Get().Ed25519KeyPairFromSeed(KeyPair, Seed);
	// TODO clean this up
	FBip39UEModule::Get().PublicKeyBytesToSuiAddress(KeyPair.PublicKeyAsSuiAddress, KeyPair.PublicKey);
}

void USuiUnrealSDKCoreBPLibrary::GenerateMnemonic(FString& Mnemonic)
{
	FBip39UEModule::Get().GenerateMnemonic(Mnemonic);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByModule(const FString& Endpoint, const FString& PackageId, const FString& ModuleName, int32 Count, int64 StartTime, int64 EndTime, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByModule(PackageId, ModuleName, Count, StartTime, EndTime, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetEventsByTransaction(const FString& Endpoint, const FString& Digest, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
		const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
		OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetEventsByTransaction(Digest, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetLatestCheckpointSequenceNumber(const FString& Endpoint,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetLatestCheckpointSequenceNumber(RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetDynamicFields(const FString& Endpoint, const FString& ParentObjectId,
	const FString& Cursor, const int64 Limit, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetDynamicFields(ParentObjectId, Cursor, Limit, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetDynamicFieldObject(const FString& Endpoint, const FString& ParentObjectId,
	const FString& DynamicFieldNameType, UVaRestJsonValue* DynamicFieldNameValue,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetDynamicFieldObject(ParentObjectId, DynamicFieldNameType, DynamicFieldNameValue->GetRootValue(), RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetBalance(const FString& Endpoint, const FString& OwnerAddress,
                                            const FString& CoinType, const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetBalance(OwnerAddress, CoinType, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetAllBalances(const FString& Endpoint, const FString& OwnerAddress,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetAllBalances(OwnerAddress, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetAllCoins(const FString& Endpoint, const FString& OwnerAddress,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetAllCoins(OwnerAddress, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTotalTransactionBlocks(const FString& Endpoint,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTotalTransactionBlocks(RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::GetTransactionBlock(const FString& Endpoint, const FString& Digest, const FTransactionBlockResponseOptions& Options,
	const FRpcResultReceivedDelegate& OnResultReceived)
{
	auto Client = FRpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda(
		[OnResultReceived](const FJsonRpcValidResponse& RpcResponse) {
			const auto VaJsonValue = GEngine->GetEngineSubsystem<UVaRestSubsystem>()->ConstructJsonValue(RpcResponse.Result);
			OnResultReceived.ExecuteIfBound(VaJsonValue);
		});
	Client.GetTransactionBlock(Digest, Options, RpcSuccessDelegate);
}

void USuiUnrealSDKCoreBPLibrary::MoveCallWithTransaction(const FString& Endpoint, const FMoveCallTransaction& Transaction, const FRpcResultReceivedDelegate& OnResult)
{
	MoveCall(Endpoint, Transaction.Signer, Transaction.PackageObjectId, Transaction.Module, Transaction.Function, Transaction.TypeArguments, Transaction.Arguments, Transaction.Gas, Transaction.GasBudget, OnResult);
}

void USuiUnrealSDKCoreBPLibrary::MintNftMoveCall(const FString& Endpoint, const FMintNft& MintTransaction, const FRpcResultReceivedDelegate& OnResult)
{
	FMoveCallTransaction MoveTransaction;
	MoveTransaction.Signer = MintTransaction.Signer;
	MoveTransaction.PackageObjectId = MintTransaction.PackageObjectId;
	MoveTransaction.Module = MintTransaction.ModuleName;
	MoveTransaction.Function = MintTransaction.Function;
	MoveTransaction.Arguments = MintTransaction.BuildArguments();
	MoveTransaction.Gas = TEXT(""); // Default to empty string
	MoveTransaction.GasBudget = TEXT("10000000"); // Default to 10000

	MoveCallWithTransaction(Endpoint, MoveTransaction, OnResult);
}
