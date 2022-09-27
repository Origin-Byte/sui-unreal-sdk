// Copyright 2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma  once

#include "IKeshUE4FundamentalTypeWrapperPlugin.h"

class FKeshUE4FundamentalTypeWrapperPlugin : public IKeshUE4FundamentalTypeWrapperPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
