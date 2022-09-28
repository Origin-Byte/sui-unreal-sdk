// Copyright Origin Byte, 2022 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SUIUNREALSDKCORE_API FUtil
{
public:
    static FString UInt64ToFString(uint64 Value)
    {
        return FString::Printf(TEXT("%llu"), Value);
    }
};
