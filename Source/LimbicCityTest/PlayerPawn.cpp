// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actor_BuildingGenerator.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AActor_BuildingGenerator* BuildingGen;

APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 2000.0f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetActorLocation();
	TargetZoom = 3000.f;

	const FRotator Rotation = SpringArmComponent->GetRelativeRotation();
	TargetRotation = FRotator(Rotation.Pitch + -50, Rotation.Yaw, 0.0f);

	UWorld* World = GetWorld();

	AActor* FoundActor;
	FoundActor = UGameplayStatics::GetActorOfClass(World, AActor_BuildingGenerator::StaticClass());


	if (FoundActor->IsA(AActor_BuildingGenerator::StaticClass()))
	{
		BuildingGen = static_cast<AActor_BuildingGenerator*>(FoundActor);
		//BuildingGeneratorr->BuildingPut();
	}
}

void APlayerPawn::Forward(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	TargetLocation = SpringArmComponent->GetForwardVector() * AxisValue * MoveSpeed + TargetLocation;
}

void APlayerPawn::Right(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	TargetLocation = SpringArmComponent->GetRightVector() * AxisValue * MoveSpeed + TargetLocation;
}

void APlayerPawn::Zoom(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	//Change 100 to a variable.
	const float Zoom = AxisValue * 100.f;
	TargetZoom = FMath::Clamp(Zoom + TargetZoom, MinZoom, MaxZoom);
}

void APlayerPawn::RotateRight()
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0.0f, -45, 0.0f));
}

void APlayerPawn::RotateLeft()
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0.0f, 45, 0.0f));
}

void APlayerPawn::EnableRotate()
{
	CanRotate = true;
}

void APlayerPawn::DisableRotate()
{
	CanRotate = false;
}

void APlayerPawn::RotateHorizontal(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	if (CanRotate)
	{
		TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation,
		                                                     FRotator(0.f, AxisValue * RotateHVSpeed, 0.f));
	}
}

void APlayerPawn::RotateVertical(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	if (CanRotate)
	{
		TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation,
		                                                     FRotator(AxisValue * RotateHVSpeed, 0.f, 0.f));
	}
}

void APlayerPawn::CameraBounds()
{
	float NewPitch = TargetRotation.Pitch;

	if (TargetRotation.Pitch < (RotatePitchMax * -1))
	{
		NewPitch = (RotatePitchMax * -1);
	}
	else if (TargetRotation.Pitch > (RotatePitchMin * -1))
	{
		NewPitch = (RotatePitchMin * -1);
	}

	TargetRotation = FRotator(NewPitch, TargetRotation.Yaw, 0.f);
	TargetLocation = FVector(TargetLocation.X, TargetLocation.Y, 0.f);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraBounds();

	const FVector InterpolatedLocation = UKismetMathLibrary::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime,
	                                                                   MoveSpeed);
	SetActorLocation(InterpolatedLocation);

	const float InterpolatedZoom = UKismetMathLibrary::FInterpTo(SpringArmComponent->TargetArmLength, TargetZoom,
	                                                             DeltaTime, ZoomSpeed);
	SpringArmComponent->TargetArmLength = InterpolatedZoom;

	const FRotator InterpolatedRotation = UKismetMathLibrary::RInterpTo(SpringArmComponent->GetRelativeRotation(),
	                                                                    TargetRotation, DeltaTime, RotateSpeed);
	SpringArmComponent->SetRelativeRotation(InterpolatedRotation);
}

void APlayerPawn::RotateBuilding()
{
	BuildingGen->RotateBuilding();
}

void APlayerPawn::ResetBuilding()
{
	BuildingGen->ResetBuilding();
}

void APlayerPawn::DeleteBuilding()
{
	BuildingGen->DeleteBuilding();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerPawn::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &APlayerPawn::Right);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &APlayerPawn::Zoom);
	PlayerInputComponent->BindAxis(TEXT("RotateHorizontal"), this, &APlayerPawn::RotateHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateVertical"), this, &APlayerPawn::RotateVertical);

	PlayerInputComponent->BindAction(TEXT("RotateRight"), IE_Pressed, this, &APlayerPawn::RotateRight);
	PlayerInputComponent->BindAction(TEXT("RotateLeft"), IE_Pressed, this, &APlayerPawn::RotateLeft);
	PlayerInputComponent->BindAction(TEXT("Rotate"), IE_Pressed, this, &APlayerPawn::EnableRotate);
	PlayerInputComponent->BindAction(TEXT("Rotate"), IE_Released, this, &APlayerPawn::DisableRotate);

	PlayerInputComponent->BindAction(TEXT("RotateBuilding"), IE_Pressed, this, &APlayerPawn::RotateBuilding);
	PlayerInputComponent->BindAction(TEXT("Reset"), IE_Pressed, this, &APlayerPawn::ResetBuilding);
	PlayerInputComponent->BindAction(TEXT("Delete"), IE_Pressed, this, &APlayerPawn::DeleteBuilding);
}
