// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "MyNewWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class LIMBICCITYTEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void PlacementButtonClicked();

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> MyNewWidgetClass;

	UFUNCTION()
	void ClickedOnBuildingElement();

	UFUNCTION()
	void PlacedBuilding();

	UFUNCTION()
	void BuildingSelection();
	
	UFUNCTION()
	void ClickedOnColorBtn();
	
private:
	UMyNewWidget* MyNewWidget;
};
