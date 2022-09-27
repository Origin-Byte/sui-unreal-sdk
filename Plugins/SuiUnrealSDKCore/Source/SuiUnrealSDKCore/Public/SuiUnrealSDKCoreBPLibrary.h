// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt64.h"
#include "SuiTypes.h"
#include "SuiUnrealSDKCoreBPLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FRpcResultReceivedDelegate, const FString&, Result);

UCLASS()
class USuiUnrealSDKCoreBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Total Transaction Number", Keywords = "Sui"), Category = "Sui")
	static void GetTotalTransactionNumber(const FRpcResultReceivedDelegate& OnResultDelegate);
};

