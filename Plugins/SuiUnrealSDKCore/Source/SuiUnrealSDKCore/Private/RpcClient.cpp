// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcClient.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiUnrealSDKCore.h"
#include "JsonObjectConverter.h"
#include "Util.h"
#include "VaRestSubsystem.h"

FRpcClient::FRpcClient(const FString& InEndpoint)
	: Endpoint(InEndpoint)
{
}

void FRpcClient::GetRecentTransactions(uint64 Count, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Count))));
	const FJsonRpcRequest Request(TEXT("sui_getRecentTransactions"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate)
{
	const FJsonRpcRequest Request(TEXT("sui_getTotalTransactionNumber"), TArray<TSharedPtr<FJsonValue>>());
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Digest)));
	const FJsonRpcRequest Request(TEXT("sui_getTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Start))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(End))));
	const FJsonRpcRequest Request(TEXT("sui_getTransactionsInRange"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	const FJsonRpcRequest Request(TEXT("sui_getObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetObjectsOwnedByAddress(const FString& Address, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Address)));
	const FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByAddress"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetObjectsOwnedByObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	const FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::MoveCall(const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
		const TArray<FString>& TypeArguments, const TArray<TSharedPtr<FJsonValue>>& Arguments, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> TypeArgumentJsonValues;
	for(auto TypeArg : TypeArguments)
	{
		TypeArgumentJsonValues.Add(MakeShareable(new FJsonValueString(TypeArg)));
	}
	
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(PackageObjectId)));
	Params.Add(MakeShareable(new FJsonValueString(Module)));
	Params.Add(MakeShareable(new FJsonValueString(Function)));
	Params.Add(MakeShareable(new FJsonValueArray(TypeArgumentJsonValues)));
	Params.Add(MakeShareable(new FJsonValueArray(Arguments)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));

	const FJsonRpcRequest Request(TEXT("sui_moveCall"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::ExecuteTransaction(const FString& TxBytes, const FString& Signature, const FString& PublicKey, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(TxBytes)));
	Params.Add(MakeShareable(new FJsonValueString(TEXT("ED25519")))); // we support this scheme for now
	Params.Add(MakeShareable(new FJsonValueString(Signature)));
	Params.Add(MakeShareable(new FJsonValueString(PublicKey)));
	Params.Add(MakeShareable(new FJsonValueString(ESuiExecuteTransactionRequestTypeNS::ToString(ExecuteTransactionRequestType))));
	const FJsonRpcRequest Request(TEXT("sui_executeTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::TransferObject(const FString& Signer, const FString& ObjectId, const FString& Gas, uint64 GasBudget, const FString& Recipient, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	Params.Add(MakeShareable(new FJsonValueString(Recipient)));

	const FJsonRpcRequest Request(TEXT("sui_transferObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::TransferSui(const FString& Signer, const FString& SuiObjectId, uint64 GasBudget, const FString& Recipient, uint64 Amount, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(SuiObjectId)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	Params.Add(MakeShareable(new FJsonValueString(Recipient)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Amount))));

	const FJsonRpcRequest Request(TEXT("sui_transferSui"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::BatchTransaction(const FString& Signer, const TArray<TSharedPtr<FJsonValue>>& SingleTransactionParams, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueArray(SingleTransactionParams)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("sui_batchTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::Pay(const FString& Signer, const TArray<FString>& InputCoinObjectIds, const TArray<FString>& Recipients, const TArray<uint64>& Amounts, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> InputCoinJsonValues;
	for(auto Id : InputCoinObjectIds)
	{
		InputCoinJsonValues.Add(MakeShareable(new FJsonValueString(Id)));
	}

	TArray<TSharedPtr<FJsonValue>> RecipientsJsonValues;
	for(auto Recipient : Recipients)
	{
		RecipientsJsonValues.Add(MakeShareable(new FJsonValueString(Recipient)));
	}

	TArray<TSharedPtr<FJsonValue>> AmountsJsonValues;
	for(const auto Amount : Amounts)
	{
		AmountsJsonValues.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Amount))));
	}
	
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueArray(InputCoinJsonValues)));
	Params.Add(MakeShareable(new FJsonValueArray(RecipientsJsonValues)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("sui_pay"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::SplitCoin(const FString& Signer, const FString& CoinObjectId, const TArray<uint64>& SplitAmounts, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> AmountsJsonValues;
	for(const auto Amount : SplitAmounts)
	{
		AmountsJsonValues.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Amount))));
	}
	
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(CoinObjectId)));
	Params.Add(MakeShareable(new FJsonValueArray(AmountsJsonValues)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("sui_splitCoin"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::SplitCoinEqual(const FString& Signer, const FString& CoinObjectId, const uint64 SplitCount, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(CoinObjectId)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(SplitCount))));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("sui_splitCoinEqual"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::MergeCoins(const FString& Signer, const FString& PrimaryCoinId, const FString& CoinToMerge, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueString(PrimaryCoinId)));
	Params.Add(MakeShareable(new FJsonValueString(CoinToMerge)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("sui_mergeCoins"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsByModule(const FString& PackageId, const FString& ModuleName, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(PackageId)));
	Params.Add(MakeShareable(new FJsonValueString(ModuleName)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(StartTime))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(EndTime))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsByModule"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsByMoveEventStructName(const FString& MoveEventStructName, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(MoveEventStructName)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(StartTime))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(EndTime))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsByMoveEventStructName"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsByObject(const FString& ObjectId, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(StartTime))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(EndTime))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsByObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsBySender(const FString& SenderAddress, uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(SenderAddress)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(StartTime))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(EndTime))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsBySender"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsByTimeRange(uint32 Count, uint64 StartTime, uint64 EndTime, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(StartTime))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(EndTime))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsByTimeRange"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetEventsByTransaction(const FString& Digest, uint32 Count, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Digest)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt32ToFString(Count))));
	const FJsonRpcRequest Request(TEXT("sui_getEventsByTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate, const FRpcErrorDelegate& ErrorDelegate)
{
	const TSharedPtr<FJsonObject> JsonRequestObject = FJsonObjectConverter::UStructToJsonObject(Request);
	JsonRequestObject->SetArrayField("params", Request.Params);
	FString OutputString;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonRequestObject.ToSharedRef(), JsonWriter);
	
	UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("Request Body: %s"), *OutputString);

	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");

	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(Endpoint);
	HttpRequest->SetContentAsString(OutputString);

	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessDelegate, ErrorDelegate](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (!bWasSuccessful || !Response.IsValid())
			{
				UE_LOG(LogSuiUnrealSDKCore, Error, TEXT("Request error"));
				// TODO
				// ErrorDelegate
			}
			else
			{
				const FString ResponseString = Response->GetContentAsString();
				UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("ProcessRequestComplete. Response: %s"), *ResponseString);

				const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
				if (TSharedPtr<FJsonObject> JsonObject; FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					if (JsonObject->HasField("result"))
					{
						FJsonRpcValidResponse ValidResponse;			
						FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FJsonRpcValidResponse::StaticStruct(), &ValidResponse, 0, 0);
					
						ValidResponse.Result = JsonObject->Values[TEXT("result")];					
						SuccessDelegate.ExecuteIfBound(ValidResponse);
					}
				}
				else
				{
					// TODO
					//ErrorDelegate.ExecuteIfBound
				}
			}
		});

	HttpRequest->ProcessRequest();
}
