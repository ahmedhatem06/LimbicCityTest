// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNewWidget.h"

#include "BuildingManager.h"
#include "C_Building.h"
#include "Actor_BuildingGenerator.h"
ABuildingManager* BM;
AActor_BuildingGenerator* ActorBuildingGenerator;
AC_Building* TempBuilding;

UMyNewWidget::UMyNewWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMyNewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlacementButton->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::PlacementButtonClicked);
	ColorBtn->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::ColorBtnClicked);
	RotateLeftBtn->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::RotateLeftBtnClicked);
	RotateRightBtn->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::RotateRightBtnClicked);
	DeleteBtn->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::DeleteBtnClicked);
	BackBtn->OnClicked.AddUniqueDynamic(this, &UMyNewWidget::BackBtnClicked);
	BackgroundImage->OnMouseButtonDownEvent.BindDynamic(this, &UMyNewWidget::OnImageClicked);
}

void UMyNewWidget::ResetPlacementUI()
{
	ListView->SetVisibility(ESlateVisibility::Hidden);
	PlacementButton->SetVisibility(ESlateVisibility::Visible);
	VerticalBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMyNewWidget::PlacementButtonClicked()
{
	PlacementButton->SetVisibility(ESlateVisibility::Hidden);
	ListView->SetVisibility(ESlateVisibility::Visible);
}

void UMyNewWidget::ClickedOnBuildingElement()
{
	ListView->SetVisibility(ESlateVisibility::Hidden);
}

void UMyNewWidget::PlacedBuilding()
{
	PlacementButton->SetVisibility(ESlateVisibility::Visible);
}

void UMyNewWidget::BuildingSelection()
{
	ListView->SetVisibility(ESlateVisibility::Hidden);
	PlacementButton->SetVisibility(ESlateVisibility::Hidden);
	VerticalBox->SetVisibility(ESlateVisibility::Visible);
}

void UMyNewWidget::ColorBtnClicked()
{
	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ABuildingManager::StaticClass());


	if (FoundActor->IsA(ABuildingManager::StaticClass()))
	{
		BM = static_cast<ABuildingManager*>(FoundActor);
		BM->ChangeColor();
	}
}

void UMyNewWidget::RotateRightBtnClicked()
{
	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ABuildingManager::StaticClass());


	if (FoundActor->IsA(ABuildingManager::StaticClass()))
	{
		BM = static_cast<ABuildingManager*>(FoundActor);
		BM->RotateRight();
	}
}

void UMyNewWidget::RotateLeftBtnClicked()
{
	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ABuildingManager::StaticClass());


	if (FoundActor->IsA(ABuildingManager::StaticClass()))
	{
		BM = static_cast<ABuildingManager*>(FoundActor);
		BM->RotateLeft();
	}
}

void UMyNewWidget::DeleteBtnClicked()
{
	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ABuildingManager::StaticClass());


	if (FoundActor->IsA(ABuildingManager::StaticClass()))
	{
		BM = static_cast<ABuildingManager*>(FoundActor);
		BM->RemoveBuilding();
		BackBtnClicked();
	}
}

void UMyNewWidget::BackBtnClicked()
{
	ResetPlacementUI();
}

FEventReply UMyNewWidget::OnImageClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, AActor_BuildingGenerator::StaticClass());

	if (FoundActor->IsA(AActor_BuildingGenerator::StaticClass()))
	{
		ActorBuildingGenerator = static_cast<AActor_BuildingGenerator*>(FoundActor);

		if (ActorBuildingGenerator->IsDragging == false && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			ResetPlacementUI();
		}
	}
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		return FEventReply(true); // Handled
	}
	else
	{
		return FEventReply(false); // Handled
	}
}
