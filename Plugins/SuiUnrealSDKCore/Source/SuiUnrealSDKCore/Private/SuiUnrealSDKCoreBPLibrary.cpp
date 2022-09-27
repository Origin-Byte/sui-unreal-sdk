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

FKeshUInt64 USuiUnrealSDKCoreBPLibrary::GetTotalTransactionNumber()
{
	auto Client = RpcClient();
	Client.GetTotalTransactionNumber();
	return FKeshUInt64(0);
}

