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
		const TArray<FString>& TypeArguments, const TArray<TSharedPtr<FJsonValue>> Arguments, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
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

void FRpcClient::ExecuteTransaction(const FString& TxBytes, const FString& Signature, const FString& PublicKey, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(TxBytes)));
	Params.Add(MakeShareable(new FJsonValueString(TEXT("ED25519")))); // we support this scheme for now
	Params.Add(MakeShareable(new FJsonValueString(Signature)));
	Params.Add(MakeShareable(new FJsonValueString(PublicKey)));
	const FJsonRpcRequest Request(TEXT("sui_executeTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate, const FRpcErrorDelegate& ErrorDelegate)
{
	const TSharedPtr<FJsonObject> JsonRequestObject = FJsonObjectConverter::UStructToJsonObject(Request);
	JsonRequestObject->SetArrayField("params", Request.Params);
	FString OutputString;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonRequestObject.ToSharedRef(), JsonWriter);

	UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("%s"), *OutputString);

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
