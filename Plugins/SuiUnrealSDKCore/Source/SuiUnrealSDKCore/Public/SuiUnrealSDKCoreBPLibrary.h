// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt64.h"
#include "SuiUnrealSDKCoreBPLibrary.generated.h"

UCLASS()
class USuiUnrealSDKCoreBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Total Transaction Number", Keywords = "Sui"), Category = "Sui")
	static FKeshUInt64 GetTotalTransactionNumber();
};
