// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VaRestJsonValue.h"
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
	WaitForEffectsCert = 1,
	WaitForLocalExecution = 2,
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

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FTransactionBlockResponseOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowBalanceChanges = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowEffects = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowEvents = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowObjectChanges = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sui | TransactionBlockResponseOptions")
	bool bShowRawInput = false;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FObjectDataOptions
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowBcs = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowContent = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowDisplay = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowOwner = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowPreviousTransaction = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowStorageRebate = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sui | FObjectDataOptions")
	bool bShowType = false;
};

UENUM(BlueprintType)
enum class SignatureScheme : uint8
{
	Ed25519 UMETA(DisplayName = "Ed25519"),
	Secp256k1 UMETA(DisplayName = "Secp256k1")
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FSignaturePubkeyPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Signature")
	SignatureScheme Scheme;

	// Base64-encoded signature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Signature")
	TArray<uint8> Signature;

	// Base64-encoded public key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Signature")
	FString PubKey;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FSerializedSignature
{
	GENERATED_BODY()

	// flag || signature || pubkey bytes, as base-64 encoded string
	// Signature is committed to the intent message of the transaction data, as base-64 encoded string
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Signature")
	FString Value;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FMoveCallTransaction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Signer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PackageObjectId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Module;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> TypeArguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UVaRestJsonValue*> Arguments; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Gas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GasBudget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESuiExecuteTransactionRequestType RequestType;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FMintNft
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Signer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PackageObjectId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ModuleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Url;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Recipient;

	FORCEINLINE FMoveCallTransaction BuildMoveCallTransaction(const FString& Gas = TEXT(""), const FString& GasBudget = TEXT("10000000"), ESuiExecuteTransactionRequestType RequestType = ESuiExecuteTransactionRequestType::WaitForLocalExecution)
	{
		FMoveCallTransaction MoveCallTransaction;
		MoveCallTransaction.Signer = Signer;
		MoveCallTransaction.PackageObjectId = PackageObjectId;
		MoveCallTransaction.Module = ModuleName;
		MoveCallTransaction.Function = Function;
		
		MoveCallTransaction.Arguments = BuildArguments();
		
		MoveCallTransaction.Gas = Gas;
		MoveCallTransaction.GasBudget = GasBudget;
		MoveCallTransaction.RequestType = RequestType;

		return MoveCallTransaction;
	}

	TArray<UVaRestJsonValue*> BuildArguments() const
	{
		TArray<UVaRestJsonValue*> Arguments;
		UVaRestSubsystem* VaRestSubSystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();

		// Add Name
		Arguments.Add(VaRestSubSystem->ConstructJsonValueString(Name));

		// Add Description
		Arguments.Add(VaRestSubSystem->ConstructJsonValueString(Description));

		// Add Url
		Arguments.Add(VaRestSubSystem->ConstructJsonValueString(Url));

		// Add Attributes
		TArray<UVaRestJsonValue*> KeysArray;
		TArray<UVaRestJsonValue*> ValuesArray;

		for (const auto& Attribute : Attributes)
		{
			KeysArray.Add(VaRestSubSystem->ConstructJsonValueString(Attribute.Key));
			ValuesArray.Add(VaRestSubSystem->ConstructJsonValueString(Attribute.Value));
		}

		// Add Keys and Values arrays to Arguments
		Arguments.Add(VaRestSubSystem->ConstructJsonValueArray(KeysArray));
		Arguments.Add(VaRestSubSystem->ConstructJsonValueArray(ValuesArray));

		// Add Recipient
		Arguments.Add(VaRestSubSystem->ConstructJsonValueString(Recipient));

		return Arguments;
	}
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FMoveModule
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Module;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Package;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FSuiObjectDataFilterCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UVaRestJsonValue*> MatchAll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UVaRestJsonValue*> MatchAny;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UVaRestJsonValue*> MatchNone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Package;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMoveModule MoveModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StructType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AddressOwner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectOwner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ObjectIds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FSuiObjectDataFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UVaRestJsonValue* FilterCondition;
};

USTRUCT(BlueprintType)
struct SUIUNREALSDKCORE_API FObjectResponseQuery
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSuiObjectDataFilter Filter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjectDataOptions Options;
};
