// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoolPlugin.h"

#include "AmaingUnrealObject.h"
#include "AmazingObject.h"

#define LOCTEXT_NAMESPACE "FCoolPluginModule"

void FCoolPluginModule::HandleModuleChanged(FName ModuleName, EModuleChangeReason ChangeReason)
{
	if (ModuleName == TEXT("Kismet") && ChangeReason == EModuleChangeReason::ModuleLoaded)
	{
		RegisterBlueprintVariableCustomization();
		FModuleManager::Get().OnModulesChanged().Remove(ModuleChangedHandle);
		ModuleChangedHandle.Reset();
	}
}

void FCoolPluginModule::RegisterBlueprintVariableCustomization()
{
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	
	BlueprintVariableCustomizationHandle = BlueprintEditorModule.RegisterVariableCustomization(FProperty::StaticClass(),
	                                                    FOnGetVariableCustomizationInstance::CreateStatic(&FAmazingObject::MakeInstance));
	UE_LOG(LogTemp, Error, TEXT("Made an instance??"))

}

void FCoolPluginModule::StartupModule()
{
	if (FModuleManager::Get().IsModuleLoaded("Kismet"))
	{
		RegisterBlueprintVariableCustomization();
		//FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	}
	else
	{
		ModuleChangedHandle = FModuleManager::Get().OnModulesChanged().AddRaw(this, &FCoolPluginModule::HandleModuleChanged);
	}
	//PropertyModule.RegisterCustomClassLayout(UAmaingUnrealObject::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FAmazingObject::MakeInstance));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCoolPluginModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UAmaingUnrealObject::StaticClass()->GetFName());
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCoolPluginModule, CoolPlugin)
