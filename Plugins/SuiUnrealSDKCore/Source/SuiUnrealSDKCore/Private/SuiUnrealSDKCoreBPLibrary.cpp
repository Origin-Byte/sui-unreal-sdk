// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiUnrealSDKCoreBPLibrary.h"
#include "SuiUnrealSDKCore.h"
#include "Interfaces/IHttpRequest.h"
#include "PlatformHttp.h"
#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"
#include "SuiTypes.h"

USuiUnrealSDKCoreBPLibrary::USuiUnrealSDKCoreBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void USuiUnrealSDKCoreBPLibrary::GetTotalTransactionNumber(const FRpcResultReceivedDelegate& OnResultDelegate)
{
	auto Client = RpcClient(TEXT("https://gateway.devnet.sui.io:443"));
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResultDelegate](const FJsonRpcValidResponse& RpcResponse) {
		OnResultDelegate.ExecuteIfBound(RpcResponse.Result);
	});
	Client.GetTotalTransactionNumber(RpcSuccessDelegate);
}

