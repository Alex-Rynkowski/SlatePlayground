// Fill out your copyright notice in the Description page of Project Settings.


#include "AmazingObject.h"

#include "AmaingUnrealObject.h"
#include "IDetailCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "DetailWidgetRow.h"
#include "Kismet/Public/SMyBlueprint.h"
#include "EdGraphSchema_K2_Actions.h"
#include "ISinglePropertyView.h"
#include "K2Node_Variable.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Toolkits/ToolkitManager.h"
#include "UObject/WeakFieldPtr.h"

#define LOCTEXT_NAMESPACE "MyLocText"

TSharedPtr<IDetailCustomization> FAmazingObject::MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor)
{
	const TArray<UObject*>* Objects = (InBlueprintEditor.IsValid()) ? InBlueprintEditor->GetObjectsCurrentlyBeingEdited() : nullptr;
	if (Objects && Objects->Num() == 1)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>((*Objects)[0]))
		{
			if (Blueprint->ParentClass->IsChildOf(UAmaingUnrealObject::StaticClass()))
			{
				return MakeShareable(new FAmazingObject(InBlueprintEditor, Blueprint));
			}
		}
	}
	return nullptr;
}

void FAmazingObject::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	if (ObjectsBeingCustomized.Num() > 0)
	{
		UPropertyWrapper* PropertyWrapper = Cast<UPropertyWrapper>(ObjectsBeingCustomized[0].Get());
		const TWeakFieldPtr<FProperty> PropertyBeingCustomized = PropertyWrapper ? PropertyWrapper->GetProperty() : nullptr;
		if (PropertyBeingCustomized.IsValid() && PropertyBeingCustomized->Owner.IsValid())
		{
			IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Variable");
			UAmaingUnrealObject* NodeInstance = CastChecked<UAmaingUnrealObject>(BlueprintPtr->GeneratedClass->ClassDefaultObject);

			const FSinglePropertyParams InitParams;
			FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

			TSharedPtr<ISinglePropertyView> PropertyView = PropertyEditorModule.CreateSingleProperty(
				NodeInstance,
				FName(PropertyBeingCustomized->GetName()),
				InitParams);

			auto PropHandle = PropertyView->GetPropertyHandle();
			const FSimpleDelegate OnStructContentsPreChangedDelegate = FSimpleDelegate::CreateSP(this,
			                                                                                     &FAmazingObject::OnStructContentsPreChanged, NodeInstance);
			PropHandle->SetOnPropertyValuePreChange(OnStructContentsPreChangedDelegate);

			UE_LOG(LogTemp, Warning, TEXT("Value changed!"))
			if (PropertyBeingCustomized->HasAnyPropertyFlags(CPF_Config))
			{
				UBlueprint* const BlueprintObj = UBlueprint::GetBlueprintFromClass(NodeInstance->GetClass());
				FString NewFuncName = FString::Printf(TEXT("Ini_%s"), *PropertyBeingCustomized->GetName());
				UEdGraph* FuncGraph = FindObject<UEdGraph>(BlueprintObj, *NewFuncName);
				if (!FuncGraph)
				{
					FuncGraph = FBlueprintEditorUtils::CreateNewGraph(BlueprintObj, FName(*NewFuncName), UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
					FBlueprintEditorUtils::AddFunctionGraph<UClass>(BlueprintObj, FuncGraph, false, NULL);
				}
			}
			Category.AddGroup("MyVars", LOCTEXT("MyVariableDisplayName", "My Variable"), false, true);
		}
	}
	// 	Category.AddCustomRow( LOCTEXT("VariableExposeToSpawnLabel", "Expose on Spawn") )
	// .Visibility(TAttribute<EVisibility>(this, &FBlueprintVarActionDetails::ExposeOnSpawnVisibility))
	// .NameContent()
	// [
	// 	SNew(STextBlock)
	// 	.ToolTip(ExposeOnSpawnTooltip)
	// 	.Text( LOCTEXT("VariableExposeToSpawnLabel", "Expose on Spawn") )
	// 	.Font( DetailFontInfo )
	// ]
	// .ValueContent()
	// [
	// 	SNew(SCheckBox)
	// 	.IsChecked( this, &FBlueprintVarActionDetails::OnGetExposedToSpawnCheckboxState )
	// 	.OnCheckStateChanged( this, &FBlueprintVarActionDetails::OnExposedToSpawnChanged )
	// 	.IsEnabled(IsVariableInBlueprint())
	// 	.ToolTip(ExposeOnSpawnTooltip)
	// ];
}

void FAmazingObject::OnStructContentsPreChanged(class UAmaingUnrealObject* InNodeInstance)
{
	UE_LOG(LogTemp, Error, TEXT("PRE Value changed!"))
}
