// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_BuildingGenerator.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "MyHUD.h"
#include "C_Building.h"
// Sets default values
AActor_BuildingGenerator::AActor_BuildingGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActor_BuildingGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_BuildingGenerator::SpawnBuilding(int BuildingIndex)
{
	//Change to mouse position.
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	TempActor = GetWorld()->SpawnActor<AActor>(ClassArrays[BuildingIndex], Location, Rotation);
	IsDragging = true;

	AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->ClickedOnBuildingElement();
}

void AActor_BuildingGenerator::BuildingPut()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Building::StaticClass(), FoundActors);
	AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		if (TempActor && TempActor == FoundActors[i])
		{
			AC_Building* Building = static_cast<AC_Building*>(FoundActors[i]);
			if (Building->BuildingStatus())
			{
				IsDragging = false;
				TempActor = nullptr;
				MyHUD->PlacedBuilding();
			}
		}
	}
}

void AActor_BuildingGenerator::RotateBuilding()
{
	if (TempActor)
	{
		FRotator TempActorRotator;
		TempActorRotator = TempActor->GetActorRotation();

		FRotator NewRotator;
		NewRotator.Pitch = TempActorRotator.Pitch;
		NewRotator.Yaw = TempActorRotator.Yaw + 45.f;
		NewRotator.Roll = TempActorRotator.Roll;
		TempActor->SetActorRotation(NewRotator);
	}
}

void AActor_BuildingGenerator::ResetBuilding()
{
	if (TempActor)
	{
		FRotator NewRotator;
		NewRotator.Pitch = 0;
		NewRotator.Yaw = 0;
		NewRotator.Roll = 0;
		TempActor->SetActorRotation(NewRotator);
	}
}

void AActor_BuildingGenerator::DeleteBuilding()
{
	if (TempActor)
	{
		IsDragging = false;
		TempActor->Destroy();
		TempActor = nullptr;
		AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		MyHUD->PlacedBuilding();
	}
}

// Called every frame
void AActor_BuildingGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsDragging && TempActor)
	{
		FHitResult Hit;
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(TempActor);
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->GetHitResultUnderCursor(ECC_WorldDynamic, true, Hit);
		FVector NewLocation;
		NewLocation.X = Hit.Location.X;
		NewLocation.Y = Hit.Location.Y;
		NewLocation.Z = 0;
		if (Hit.GetActor() != TempActor)
		{
			TempActor->SetActorLocation(Hit.Location);
		}
	}
}
