// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmaingUnrealObject.h"
#include "EdGraphSchema_K2_Actions.h"
#include "IDetailCustomization.h"
#include "SMyBlueprint.h"

class FAmazingObject : public IDetailCustomization
{
public:
	static TSharedPtr<IDetailCustomization> MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);

	FAmazingObject(TSharedPtr<IBlueprintEditor> InBlueprintEditor, UBlueprint* Blueprint)
		: MyBlueprint(InBlueprintEditor)
		, BlueprintPtr(Blueprint)
	{
		Properties.Empty();
		UAmaingUnrealObject* NodeInstance = CastChecked<UAmaingUnrealObject>(BlueprintPtr->GeneratedClass->ClassDefaultObject);
		
		UE_LOG(LogTemp, Warning, TEXT("helooo"))
		for (TFieldIterator<FProperty> PropIt(NodeInstance->GetClass()); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;
			Properties.Add(Property->GetName(), Property->PropertyFlags);
		}
	}

	TMap<FString, EPropertyFlags> Properties;
	
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	TObjectPtr<IDetailLayoutBuilder> DetailLayout;
	TWeakObjectPtr<UBlueprint> BlueprintPtr;
	TWeakPtr<IBlueprintEditor> MyBlueprint;
	
	void OnStructContentsPreChanged(class UAmaingUnrealObject* InNodeInstance);
};
