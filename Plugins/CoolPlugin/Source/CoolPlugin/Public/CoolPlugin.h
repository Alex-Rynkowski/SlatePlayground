// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCoolPluginModule : public IModuleInterface
{
public:
	void HandleModuleChanged(FName ModuleName, EModuleChangeReason ChangeReason);
	void RegisterBlueprintVariableCustomization();

	FDelegateHandle ModuleChangedHandle;
	FDelegateHandle BlueprintVariableCustomizationHandle;
	/** IModuleInterface implementation */

	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
