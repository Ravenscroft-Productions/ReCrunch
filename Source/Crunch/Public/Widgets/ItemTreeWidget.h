// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "TreeNodeInterface.h"
#include "Blueprint/UserWidget.h"
#include "ItemTreeWidget.generated.h"

class UCanvasPanelSlot;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class CRUNCH_API UItemTreeWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	void ClearTree();
	UUserWidget* CreateWidgetForNode(const ITreeNodeInterface* Node, UCanvasPanelSlot*& OutCanvasSlot);
	void CreateConnection(const UUserWidget* From, UUserWidget* To);
	void DrawStream(bool bUpperStream, const ITreeNodeInterface* StartingNodeInterface, UUserWidget* StartingNodeWidget, UCanvasPanelSlot* StartingNodeSlot , int StartingNodeDepth, float& NextLeafXPosition, TArray<UCanvasPanelSlot*>& OutStreamSlots);
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootPanel;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D NodeSize = FVector2D{ 60.0f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D NodeGap = FVector2D{ 16.0f, 30.0f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FLinearColor ConnectionColour = FLinearColor{ 0.8f, 0.8f, 0.8f, 1.0f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	float ConnectionThickness = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D SourcePortLocalPos = FVector2D{ 0.5f, 0.9f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D DestinationPortLocalPos = FVector2D{ 0.5f, 0.1f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D SourcePortDirection = FVector2D{ 0.0f, 90.0f };
	
	UPROPERTY(EditDefaultsOnly, Category = "Tree")
	FVector2D DestinationPortDirection = FVector2D{ 0.0f, 90.0f };
};
