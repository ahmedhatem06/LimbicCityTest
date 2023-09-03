// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Building.generated.h"

UCLASS()
class LIMBICCITYTEST_API AC_Building : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_Building();

	UFUNCTION()
	bool BuildingStatus();

	UFUNCTION()
	void BuildingSet();

	UFUNCTION()
	void ChangeColor();

	UFUNCTION()
	void RotateRight();

	UFUNCTION()
	void RotateLeft();

	UFUNCTION()
	void Delete();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool canSetBuilding = true;
	bool IsBuildingSet = false;
	bool IsSelected = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UMaterial* GreenMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UMaterial* RedMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	TArray<UMaterial*> ClickMaterials;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	class UMaterialInstance* DefaultMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* pComponent, FKey inKey);
};
