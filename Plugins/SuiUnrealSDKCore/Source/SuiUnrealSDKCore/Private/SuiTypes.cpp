// Fill out your copyright notice in the Description page of Project Settings.

#include "SuiTypes.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiUnrealSDKCore.h"
#include "JsonObjectConverter.h"

RpcClient::RpcClient(const FString& InEndpoint)
	: Endpoint(InEndpoint)
{
}

void RpcClient::GetRecentTransactions(uint64 Count, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(FString::Printf(TEXT("%llu"), Count));
	FJsonRpcRequest Request(TEXT("sui_getRecentTransactions"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	FJsonRpcRequest Request(TEXT("sui_getTotalTransactionNumber"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(Digest);
	FJsonRpcRequest Request(TEXT("sui_getTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(FString::Printf(TEXT("%llu"), Start));
	Params.Add(FString::Printf(TEXT("%llu"), End));
	FJsonRpcRequest Request(TEXT("sui_getTransactionsInRange"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(ObjectId);
	FJsonRpcRequest Request(TEXT("sui_getObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObjectsOwnedByAddress(const FString& Address, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(Address);
	FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByAddress"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObjectsOwnedByObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<FString> Params;
	Params.Add(ObjectId);
	FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByObject"), Params);
	SendRequest(Request, SuccessDelegate);
}


void RpcClient::SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate, const FRpcErrorDelegate& ErrorDelegate)
{
	TSharedPtr<FJsonObject> JsontRequestObject = FJsonObjectConverter::UStructToJsonObject(Request);
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsontRequestObject.ToSharedRef(), JsonWriter);

	UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("%s"), *OutputString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
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
				TSharedPtr<FJsonObject> JsonObject;
				FString ResponseString = Response->GetContentAsString();
				UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("ProcessRequestComplete. Response: %s"), *ResponseString);
				
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
				if (FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					FJsonRpcValidResponse ValidResponse;
					// TODO handle single value responses
					FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FJsonRpcValidResponse::StaticStruct(), &ValidResponse, 0, 0);

					SuccessDelegate.ExecuteIfBound(ValidResponse);
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
