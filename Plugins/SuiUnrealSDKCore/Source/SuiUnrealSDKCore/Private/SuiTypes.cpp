// Fill out your copyright notice in the Description page of Project Settings.

#include "SuiTypes.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiUnrealSDKCore.h"
#include "JsonObjectConverter.h"

FKeshUInt64 RpcClient::GetTotalTransactionNumber()
{
	TArray<FString> Params;
	FJsonRpcRequest Request(TEXT("sui_getTotalTransactionNumber"), Params);
	MakeRequest(Request, TEXT("https://gateway.devnet.sui.io:443"));
	return FKeshUInt64(0);
}

bool RpcClient::MakeRequest(FJsonRpcRequest Request, const FString& URL)
{
	TSharedPtr<FJsonObject> JsontRequestObject = FJsonObjectConverter::UStructToJsonObject(Request);
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsontRequestObject.ToSharedRef(), JsonWriter);

	UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("%s"), *OutputString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");

	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(URL);
	HttpRequest->SetContentAsString(OutputString);

	HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (!bWasSuccessful || !Response.IsValid())
			{
				UE_LOG(LogSuiUnrealSDKCore, Error, TEXT("Request error"));
			}
			else
			{
				TSharedPtr<FJsonObject> JsonObject;
				FString ResponseString = Response->GetContentAsString();
				UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("%s"), *ResponseString);
			}
		});

	HttpRequest->ProcessRequest();

	return true;
}

void RpcClient::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogSuiUnrealSDKCore, Error, TEXT("Request error"));
	}
	else
	{
		TSharedPtr<FJsonObject> JsonObject;
		FString ResponseString = Response->GetContentAsString();
		UE_LOG(LogSuiUnrealSDKCore, Verbose, TEXT("%s"), *ResponseString);

		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			
		}
	}
}
