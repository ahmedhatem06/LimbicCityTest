// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Building.h"
#include "GameFramework/Actor.h"
#include "BuildingManager.generated.h"

UCLASS()
class LIMBICCITYTEST_API ABuildingManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void RemoveBuilding();
	void ChangeColor();
	void RotateRight();
	void RotateLeft();
	void SelectedBuilding(AC_Building* Building);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class AC_Building* TempBuilding;
};
