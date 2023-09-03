// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyButton.h"
#include "Blueprint/IUserListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "C_ListView.generated.h"

/**
 * 
 */
UCLASS()
class LIMBICCITYTEST_API UC_ListView : public UUserWidget, public IUserListEntry
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UFUNCTION()
	void OnPlacementButtonClicked(int n);

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, meta=(BindWidget))
	class UListView* MyList;

	void MyEventCallback(UObject* Object);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	TArray<UMyButton*> ButtonArray;

	UFUNCTION()
	void OnButtonClicked(int Index);
};
