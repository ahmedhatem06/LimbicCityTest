// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

AMyHUD::AMyHUD()
{
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MyNewWidgetClass)
	{
		MyNewWidget = CreateWidget<UMyNewWidget>(GetWorld(), MyNewWidgetClass);

		if (MyNewWidget)
		{
			MyNewWidget->AddToViewport();
		}
	}
}

void AMyHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyHUD::PlacementButtonClicked()
{
	if (MyNewWidget)
	{
		MyNewWidget->PlacementButtonClicked();
	}
}

void AMyHUD::ClickedOnBuildingElement()
{
	if (MyNewWidget)
	{
		MyNewWidget->ClickedOnBuildingElement();
	}
}

void AMyHUD::PlacedBuilding()
{
	if (MyNewWidget)
	{
		MyNewWidget->PlacedBuilding();
	}
}

void AMyHUD::BuildingSelection()
{
	if (MyNewWidget)
	{
		MyNewWidget->BuildingSelection();
	}
}

void AMyHUD::ClickedOnColorBtn()
{
	if (MyNewWidget)
	{
		MyNewWidget->ColorBtnClicked();
	}
}
