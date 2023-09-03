// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickDelegate, int32, buttonIndex);

UCLASS()
class LIMBICCITYTEST_API UMyButton : public UButton
{
	GENERATED_BODY()

public:

	UMyButton();
	int32 buttonIndex = 0;
	//DECLARE_DYNAMIC_DELEGATE_OneParam(FClickDelegate,int32);
	//DECLARE_DELEGATE_OneParam(FClickDelegate, int);
	UPROPERTY()
	FClickDelegate Click;

	UFUNCTION()
	void OnClick();
};
