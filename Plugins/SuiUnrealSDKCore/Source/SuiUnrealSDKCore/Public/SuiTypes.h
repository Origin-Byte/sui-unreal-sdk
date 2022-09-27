// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "HttpRetrySystem.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt64.h"
#include "SuiTypes.generated.h"

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FSuiTypes
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FJsonRpcObjectBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Jsonrpc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	int32 Id;

	FJsonRpcObjectBase(int32 InId)
	{
		Jsonrpc = "2.0";
		Id = InId;
	}

	FJsonRpcObjectBase()
	{
		Jsonrpc = "2.0";
		Id = 1;
	}
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FJsonRpcRequest : public FJsonRpcObjectBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Method;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	TArray<FString> Params;

	FJsonRpcRequest(const FString& InMethod, const TArray<FString>& InParams, int32 InId = 1)
		: FJsonRpcObjectBase(InId)
	{
		Method = InMethod;
		Params = InParams;
	}

	FJsonRpcRequest()
		: FJsonRpcObjectBase(1)
	{
		Method = TEXT("");
	}
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FJsonRpcValidResponse : public FJsonRpcObjectBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Result;

	FJsonRpcValidResponse(const FString& InResult, int32 InId = 1)
		: FJsonRpcObjectBase(InId)
	{
		Result = InResult;
	}

	FJsonRpcValidResponse()
		: FJsonRpcObjectBase(1)
	{	
		Result = TEXT("");
	}
};

class SUIUNREALSDKCORE_API RpcClient
{
public:
	FKeshUInt64 GetTotalTransactionNumber();

private:
	bool MakeRequest(FJsonRpcRequest Request, const FString& URL);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponseReceivedDelegate, FString, Result);

