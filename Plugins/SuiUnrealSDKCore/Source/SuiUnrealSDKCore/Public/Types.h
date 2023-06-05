// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "VaRestSubsystem.h"
#include "Types.generated.h"

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FTypes
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

	TArray<TSharedPtr<FJsonValue>> Params;

	FJsonRpcRequest(const FString& InMethod, const TArray<TSharedPtr<FJsonValue>>& InParams, int32 InId = 1)
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

	TSharedPtr<FJsonValue> Result;
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

UENUM(BlueprintType, Category = "Sui")
enum class ESuiExecuteTransactionRequestType : uint8
{
	None = 0,
	ImmediateReturn = 1,
	WaitForTxCert = 2,
	WaitForEffectsCert = 3,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ESuiExecuteTransactionRequestType, ESuiExecuteTransactionRequestType::Count);

namespace ESuiExecuteTransactionRequestTypeNS
{
	inline FString ToString(const ESuiExecuteTransactionRequestType& EnumVal)
	{
		return *UEnum::GetValueAsName(EnumVal).ToString().Replace(TEXT("ESuiExecuteTransactionRequestType::"), TEXT(""));
	}
}