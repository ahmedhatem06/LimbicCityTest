// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"


UMyButton::UMyButton()
{
	OnClicked.AddDynamic(this, &UMyButton::OnClick);
}

void UMyButton::OnClick()
{
	Click.Broadcast(buttonIndex);
}
