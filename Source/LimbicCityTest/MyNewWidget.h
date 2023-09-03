// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyNewWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIMBICCITYTEST_API UMyNewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMyNewWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ResetPlacementUI();

	UFUNCTION()
	void PlacementButtonClicked();

	UFUNCTION()
	void ClickedOnBuildingElement();

	UFUNCTION()
	void PlacedBuilding();

	UFUNCTION()
	void BuildingSelection();

	UFUNCTION()
	void ColorBtnClicked();

	UFUNCTION()
	void RotateRightBtnClicked();

	UFUNCTION()
	void RotateLeftBtnClicked();

	UFUNCTION()
	void DeleteBtnClicked();

	UFUNCTION()
	void BackBtnClicked();

	UFUNCTION()
	FEventReply OnImageClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* PlacementButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UListView* ListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* ColorBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* RotateRightBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* RotateLeftBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* DeleteBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* BackBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* BackgroundImage;
};
