// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"
// Sets default values
ABuildingManager::ABuildingManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingManager::RemoveBuilding()
{
	if (TempBuilding)
	{
		TempBuilding->Delete();
		TempBuilding = nullptr;
	}
}

void ABuildingManager::ChangeColor()
{
	if (TempBuilding)
	{
		TempBuilding->ChangeColor();
	}
}

void ABuildingManager::RotateRight()
{
	if (TempBuilding)
	{
		TempBuilding->RotateRight();
	}
}

void ABuildingManager::RotateLeft()
{
	if (TempBuilding)
	{
		TempBuilding->RotateLeft();
	}
}

void ABuildingManager::SelectedBuilding(AC_Building* Building)
{
	TempBuilding = Building;
}
