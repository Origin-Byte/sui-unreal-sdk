// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcClient.h"

#include "EditorMetadataOverrides.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiUnrealSDKCore.h"
#include "JsonObjectConverter.h"
#include "Util.h"
#include "VaRestSubsystem.h"
#include "Math/BigInt.h"

FRpcClient::FRpcClient(const FString& InEndpoint)
	: Endpoint(InEndpoint)
{
}

void FRpcClient::GetObject(const FString& ObjectId, const FObjectDataOptions& Options, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ObjectId)));

	const TSharedPtr<FJsonObject> OptionsObject = MakeShared<FJsonObject>();
	OptionsObject->SetBoolField("showBcs", Options.bShowBcs);
	OptionsObject->SetBoolField("showContent", Options.bShowContent);
	OptionsObject->SetBoolField("showDisplay", Options.bShowDisplay);
	OptionsObject->SetBoolField("showOwner", Options.bShowOwner);
	OptionsObject->SetBoolField("showPreviousTransaction", Options.bShowPreviousTransaction);
	OptionsObject->SetBoolField("showStorageRebate", Options.bShowStorageRebate);
	OptionsObject->SetBoolField("showType", Options.bShowType);

	Params.Add(MakeShareable(new FJsonValueObject(OptionsObject)));
	
	const FJsonRpcRequest Request(TEXT("sui_getObject"), Params);
	SendRequest(Request, SuccessDelegate);
}


void FRpcClient::GetOwnedObjects(const FString& Address, const FObjectResponseQuery& ResponseQuery, const FString& CursorId, const TOptional<uint64> Limit, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Address)));

	const TSharedPtr<FJsonObject> QueryParamsJson = MakeShared<FJsonObject>();
	const auto FilterJson = ResponseQuery.Filter->ToJson();
	QueryParamsJson->SetField("filter", FilterJson);

	const TSharedPtr<FJsonObject> OptionsObject = MakeShared<FJsonObject>();
	OptionsObject->SetBoolField("showBcs", ResponseQuery.Options.bShowBcs);
	OptionsObject->SetBoolField("showContent", ResponseQuery.Options.bShowContent);
	OptionsObject->SetBoolField("showDisplay", ResponseQuery.Options.bShowDisplay);
	OptionsObject->SetBoolField("showOwner", ResponseQuery.Options.bShowOwner);
	OptionsObject->SetBoolField("showPreviousTransaction", ResponseQuery.Options.bShowPreviousTransaction);
	OptionsObject->SetBoolField("showStorageRebate", ResponseQuery.Options.bShowStorageRebate);
	OptionsObject->SetBoolField("showType", ResponseQuery.Options.bShowType);

	QueryParamsJson->SetObjectField("options", OptionsObject);

	Params.Add(MakeShareable(new FJsonValueObject(QueryParamsJson)));

	if (!CursorId.IsEmpty())
	{
		Params.Add(MakeShareable(new FJsonValueString(CursorId)));
	}
	else
	{
		Params.Add(MakeShareable(new FJsonValueNull()));
	}

	if (Limit.IsSet())
	{
		Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Limit.GetValue()))));
	}
	
	const FJsonRpcRequest Request(TEXT("suix_getOwnedObjects"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::MoveCall(const FString& Signer, const FString& PackageObjectId, const FString& Module, const FString& Function,
                          const TArray<FString>& TypeArguments, const TArray<TSharedPtr<FJsonValue>>& Arguments, const FString& Gas, const FString& GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
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
	if (!Gas.IsEmpty())
	{
		Params.Add(MakeShareable(new FJsonValueString(Gas)));
	}
	else
	{
		Params.Add(MakeShareable(new FJsonValueNull()));
	}
	Params.Add(MakeShareable(new FJsonValueString(GasBudget)));

	const FJsonRpcRequest Request(TEXT("unsafe_moveCall"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::ExecuteTransactionBlock(const FString& TxBytes, const TArray<FString>& SerializedSignatures, const FTransactionBlockResponseOptions& Options, ESuiExecuteTransactionRequestType ExecuteTransactionRequestType, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> SignaturesJsonValues;
	for(auto Signature : SerializedSignatures)
	{
		SignaturesJsonValues.Add(MakeShareable(new FJsonValueString(Signature)));
	}
	
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(TxBytes)));
	Params.Add(MakeShareable(new FJsonValueArray(SignaturesJsonValues)));

	const TSharedPtr<FJsonObject> OptionsObject = MakeShared<FJsonObject>();
	OptionsObject->SetBoolField("showBalanceChanges", Options.bShowBalanceChanges);
	OptionsObject->SetBoolField("showEffects", Options.bShowEffects);
	OptionsObject->SetBoolField("showEvents", Options.bShowEvents);
	OptionsObject->SetBoolField("showInput", Options.bShowInput);
	OptionsObject->SetBoolField("showObjectChanges", Options.bShowObjectChanges);
	OptionsObject->SetBoolField("showRawInput", Options.bShowRawInput);

	Params.Add(MakeShareable(new FJsonValueObject(OptionsObject)));
	
	Params.Add(MakeShareable(new FJsonValueString(ESuiExecuteTransactionRequestTypeNS::ToString(ExecuteTransactionRequestType))));
	const FJsonRpcRequest Request(TEXT("sui_executeTransactionBlock"), Params);
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

	const FJsonRpcRequest Request(TEXT("unsafe_transferObject"), Params);
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

	const FJsonRpcRequest Request(TEXT("unsafe_transferSui"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::BatchTransaction(const FString& Signer, const TArray<TSharedPtr<FJsonValue>>& SingleTransactionParams, const FString& Gas, uint64 GasBudget, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Signer)));
	Params.Add(MakeShareable(new FJsonValueArray(SingleTransactionParams)));
	Params.Add(MakeShareable(new FJsonValueString(Gas)));
	Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(GasBudget))));
	
	const FJsonRpcRequest Request(TEXT("unsafe_batchTransaction"), Params);
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
	
	const FJsonRpcRequest Request(TEXT("unsafe_pay"), Params);
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
	
	const FJsonRpcRequest Request(TEXT("unsafe_splitCoin"), Params);
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
	
	const FJsonRpcRequest Request(TEXT("unsafe_splitCoinEqual"), Params);
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
	
	const FJsonRpcRequest Request(TEXT("unsafe_mergeCoins"), Params);
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

void FRpcClient::GetEventsByTransaction(const FString& Digest, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Digest)));
	const FJsonRpcRequest Request(TEXT("sui_getEvents"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetLatestCheckpointSequenceNumber(const FRpcSuccessDelegate& SuccessDelegate)
{
	const FJsonRpcRequest Request(TEXT("sui_getLatestCheckpointSequenceNumber"), TArray<TSharedPtr<FJsonValue>>());
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetDynamicFieldObject(const FString& ParentObjectId, const FString& DynamicFieldNameType,
	const TSharedPtr<FJsonValue>& DynamicFieldNameValue, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ParentObjectId)));

	const TSharedPtr<FJsonObject> DynamicFieldNameJsonObject = MakeShareable(new FJsonObject());
	DynamicFieldNameJsonObject->SetStringField("type", DynamicFieldNameType);
	DynamicFieldNameJsonObject->SetField("value", DynamicFieldNameValue);
	Params.Add(MakeShareable(new FJsonValueObject(DynamicFieldNameJsonObject)));
	
	const FJsonRpcRequest Request(TEXT("suix_getDynamicFieldObject"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetDynamicFields(const FString& ParentObjectId, const FString& Cursor, const TOptional<uint64> Limit,
	const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(ParentObjectId)));
	if (!Cursor.IsEmpty())
	{
		Params.Add(MakeShareable(new FJsonValueString(Cursor)));
	}
	else
	{
		Params.Add(MakeShareable(new FJsonValueNull()));
	}
	if (Limit.IsSet())
	{
		Params.Add(MakeShareable(new FJsonValueNumberString(FUtil::UInt64ToFString(Limit.GetValue()))));
	}

	const FJsonRpcRequest Request(TEXT("suix_getDynamicFields"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetBalance(const FString& OwnerAddress, const FString& CoinType,
	const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(OwnerAddress)));
	if (!CoinType.IsEmpty())
	{
		Params.Add(MakeShareable(new FJsonValueString(CoinType)));
	}
	const FJsonRpcRequest Request(TEXT("suix_getBalance"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetAllBalances(const FString& OwnerAddress, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(OwnerAddress)));
	const FJsonRpcRequest Request(TEXT("suix_getAllBalances"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetAllCoins(const FString& OwnerAddress, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(OwnerAddress)));
	const FJsonRpcRequest Request(TEXT("suix_getAllCoins"), Params);
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetTotalTransactionBlocks(const FRpcSuccessDelegate& SuccessDelegate)
{
	const FJsonRpcRequest Request(TEXT("sui_getTotalTransactionBlocks"), TArray<TSharedPtr<FJsonValue>>());
	SendRequest(Request, SuccessDelegate);
}

void FRpcClient::GetTransactionBlock(const FString& Digest, const FTransactionBlockResponseOptions& Options, const FRpcSuccessDelegate& SuccessDelegate)
{
	TArray<TSharedPtr<FJsonValue>> Params;
	Params.Add(MakeShareable(new FJsonValueString(Digest)));

	const TSharedPtr<FJsonObject> OptionsObject = MakeShared<FJsonObject>();
	OptionsObject->SetBoolField("showBalanceChanges", Options.bShowBalanceChanges);
	OptionsObject->SetBoolField("showEffects", Options.bShowEffects);
	OptionsObject->SetBoolField("showEvents", Options.bShowEvents);
	OptionsObject->SetBoolField("showInput", Options.bShowInput);
	OptionsObject->SetBoolField("showObjectChanges", Options.bShowObjectChanges);
	OptionsObject->SetBoolField("showRawInput", Options.bShowRawInput);

	Params.Add(MakeShareable(new FJsonValueObject(OptionsObject)));
	
	const FJsonRpcRequest Request(TEXT("sui_getTransactionBlock"), Params);
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
