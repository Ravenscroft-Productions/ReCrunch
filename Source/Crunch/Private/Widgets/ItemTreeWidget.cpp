// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/ItemTreeWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/SplineWidget.h"

void UItemTreeWidget::ClearTree()
{
	RootPanel->ClearChildren();
}

UUserWidget* UItemTreeWidget::CreateWidgetForNode(const ITreeNodeInterface* Node, UCanvasPanelSlot*& OutCanvasSlot)
{
	if (!Node) return nullptr;
	
	UUserWidget* NodeWidget = Node->GetWidget();
	OutCanvasSlot = RootPanel->AddChildToCanvas(NodeWidget);
	if (OutCanvasSlot)
	{
		OutCanvasSlot->SetSize(NodeSize);
		OutCanvasSlot->SetAnchors(FAnchors(0.5f));
		OutCanvasSlot->SetAlignment(FVector2D(0.5f));
		OutCanvasSlot->SetZOrder(1);
	}
	
	return NodeWidget;
}

void UItemTreeWidget::CreateConnection(const UUserWidget* From, UUserWidget* To)
{
	if (!From || !To) return;
	
	USplineWidget* Connection = CreateWidget<USplineWidget>(GetOwningPlayer());
	UCanvasPanelSlot* ConnectionPanelSlot = RootPanel->AddChildToCanvas(Connection);
	
	if (ConnectionPanelSlot)
	{
		ConnectionPanelSlot->SetAnchors(FAnchors(0.0f));
		ConnectionPanelSlot->SetAlignment(FVector2D(0.0f));
		ConnectionPanelSlot->SetPosition(FVector2D::Zero());
		ConnectionPanelSlot->SetZOrder(0);
	}
	
	Connection->SetupSpline(From, To, SourcePortLocalPos, DestinationPortLocalPos, SourcePortDirection, DestinationPortDirection);
	Connection->SetSplineStyle(ConnectionColour, ConnectionThickness);
}
