// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Building.h"

#include "Actor_BuildingGenerator.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "MyHUD.h"
#include"BuildingManager.h"
AActor_BuildingGenerator* BuildingGener;
ABuildingManager* BuildingMan;
// Sets default values
AC_Building::AC_Building()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//StaticMeshComponent->SetCollisionProfileName("Trigger");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_Building::OnOverlapBegin);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AC_Building::OnOverlapEnd);
	StaticMeshComponent->OnClicked.AddUniqueDynamic(this, &AC_Building::OnClicked);
}

// Called when the game starts or when spawned
void AC_Building::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaterial = static_cast<UMaterialInstance*>(StaticMeshComponent->GetMaterial(0));

	UWorld* World = GetWorld();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, AActor_BuildingGenerator::StaticClass());


	if (FoundActor->IsA(AActor_BuildingGenerator::StaticClass()))
	{
		BuildingGener = static_cast<AActor_BuildingGenerator*>(FoundActor);
	}

	FoundActor = UGameplayStatics::GetActorOfClass(World, ABuildingManager::StaticClass());
	if (FoundActor->IsA(ABuildingManager::StaticClass()))
	{
		BuildingMan = static_cast<ABuildingManager*>(FoundActor);
	}
}

// Called every frame
void AC_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Building::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (!IsBuildingSet)
	{
		StaticMeshComponent->SetMaterial(0, RedMaterial);
	}
	canSetBuilding = false;
}

void AC_Building::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
	if (!IsBuildingSet)
	{
		StaticMeshComponent->SetMaterial(0, GreenMaterial);
	}
	canSetBuilding = true;
}

void AC_Building::OnClicked(UPrimitiveComponent* pComponent, FKey inKey)
{
	if (!BuildingGener->IsDragging && IsBuildingSet)
	{
		BuildingMan->SelectedBuilding(this);
		AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		MyHUD->BuildingSelection();
	}
}


bool AC_Building::BuildingStatus()
{
	if (canSetBuilding)
	{
		StaticMeshComponent->SetMaterial(0, DefaultMaterial);
		IsBuildingSet = true;
		return true;
	}
	else
	{
		return false;
	}
}

void AC_Building::BuildingSet()
{
	StaticMeshComponent->SetMaterial(0, DefaultMaterial);
}

void AC_Building::ChangeColor()
{
	int randomMaterialIndex = FMath::RandRange(0, ClickMaterials.Num() - 1);
	StaticMeshComponent->SetMaterial(0, ClickMaterials[randomMaterialIndex]);
}

void AC_Building::RotateRight()
{
	FRotator TempActorRotator = this->GetActorRotation();

	FRotator NewRotator;
	NewRotator.Pitch = TempActorRotator.Pitch;
	NewRotator.Yaw = TempActorRotator.Yaw + 45.f;
	NewRotator.Roll = TempActorRotator.Roll;
	this->SetActorRotation(NewRotator);
}

void AC_Building::RotateLeft()
{
	FRotator TempActorRotator = this->GetActorRotation();

	FRotator NewRotator;
	NewRotator.Pitch = TempActorRotator.Pitch;
	NewRotator.Yaw = TempActorRotator.Yaw - 45.f;
	NewRotator.Roll = TempActorRotator.Roll;
	this->SetActorRotation(NewRotator);
}

void AC_Building::Delete()
{
	this->Destroy();
}
