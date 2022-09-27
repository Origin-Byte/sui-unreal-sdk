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

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FJsonRpcError
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	int32 Code;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Message;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Data;

	FJsonRpcError(int32 InCode, const FString& InMessage, const FString& InData)
	{
		Code = InCode;
		Message = InMessage;
		Data = InData;
	}

	FJsonRpcError()
	{
		Code = 0;
		Message = TEXT("");
		Data = TEXT("");
	}
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FJsonRpcErrorResponse : public FJsonRpcObjectBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FJsonRpcError Error;

	FJsonRpcErrorResponse(const FJsonRpcError& InError, int32 InId = 1)
		: FJsonRpcObjectBase(InId)
	{
		Error = InError;
	}

	FJsonRpcErrorResponse()
		: FJsonRpcObjectBase(1)
	{
		Error = FJsonRpcError();
	}
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FRpcResult
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	bool IsSuccess;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString RawRpcRequest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString RawRpcResponse;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sui")
	FString ErrorMessage;
};

DECLARE_DELEGATE_OneParam(FRpcSuccessDelegate, const FJsonRpcValidResponse&);
DECLARE_DELEGATE_OneParam(FRpcErrorDelegate, const FJsonRpcErrorResponse&);



class SUIUNREALSDKCORE_API RpcClient
{
public:
	RpcClient(const FString& InEndpoint);
	FORCEINLINE const FString& GetEndpoint() const { return Endpoint; }

	void GetTotalTransactionNumber(const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetTransactionsInRange(uint64 Start, uint64 End, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());
	void GetObject(const FString& ObjectId, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate());

private:
	void SendRequest(const FJsonRpcRequest& Request, const FRpcSuccessDelegate& SuccessDelegate = FRpcSuccessDelegate(), const FRpcErrorDelegate& ErrorDelegate = FRpcErrorDelegate());

	FString Endpoint;
};

