// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_BuildingGenerator.generated.h"

UCLASS()
class LIMBICCITYTEST_API AActor_BuildingGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_BuildingGenerator();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	TArray<UClass*> ClassArrays;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	UClass* CurrentActor;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	AActor* TempActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsDragging = false;
	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(int BuildingIndex);
	void BuildingPut();

	void RotateBuilding();
	void ResetBuilding();
	void DeleteBuilding();
};
