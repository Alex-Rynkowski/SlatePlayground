// Fill out your copyright notice in the Description page of Project Settings.


#include "K2_CoolNode.h"

#include "KismetCompiler.h"

#define LOCTEXT_NAMESPACE "K2Node_CoolNode"

void UK2_CoolNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	// Transform pin
	UScriptStruct* TransformStruct = TBaseStructure<FTransform>::Get();

	UEdGraphPin* TestPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, "");
	UEdGraphPin* TestPin2 = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, "");
}

FText UK2_CoolNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}

void UK2_CoolNode::GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const
{
	Super::GetPinHoverText(Pin, HoverTextOut);
}

void UK2_CoolNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
}

FSlateIcon UK2_CoolNode::GetIconAndTint(FLinearColor& OutColor) const
{
	return Super::GetIconAndTint(OutColor);
}

bool UK2_CoolNode::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	return Super::IsCompatibleWithGraph(TargetGraph);
}
