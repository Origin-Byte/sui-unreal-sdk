// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcClient.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiUnrealSDKCore.h"
#include "JsonObjectConverter.h"
#include "VaRestSubsystem.h"

RpcClient::RpcClient(const FString& InEndpoint)
	: Endpoint(InEndpoint)
{
}

void RpcClient::GetRecentTransactions(uint64 Count, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueNumberString(FString::Printf(TEXT("%llu"), Count))));
	const FJsonRpcRequest Request(TEXT("sui_getRecentTransactions"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate)
{
	const FJsonRpcRequest Request(TEXT("sui_getTotalTransactionNumber"), TArray<TSharedPtr<FJsonValue>>());
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Digest)));
	const FJsonRpcRequest Request(TEXT("sui_getTransaction"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueNumberString(FString::Printf(TEXT("%llu"), Start))));
	Params.Add(MakeShareable(new FJsonValueNumberString(FString::Printf(TEXT("%llu"), End))));
	const FJsonRpcRequest Request(TEXT("sui_getTransactionsInRange"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	const FJsonRpcRequest Request(TEXT("sui_getObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObjectsOwnedByAddress(const FString& Address, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Address)));
	const FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByAddress"), Params);
	SendRequest(Request, SuccessDelegate);
}

void RpcClient::GetObjectsOwnedByObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));
	const FJsonRpcRequest Request(TEXT("sui_getObjectsOwnedByObject"), Params);
	SendRequest(Request, SuccessDelegate);
}


void RpcClient::SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate, const FRpcErrorDelegate& ErrorDelegate)
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
					FJsonRpcValidResponse ValidResponse;			
					FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FJsonRpcValidResponse::StaticStruct(), &ValidResponse, 0, 0);

					ValidResponse.Result = JsonObject->Values[TEXT("result")];					
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
