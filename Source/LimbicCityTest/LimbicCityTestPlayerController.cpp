// Copyright Epic Games, Inc. All Rights Reserved.

#include "LimbicCityTestPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actor_BuildingGenerator.h"
#include "Kismet/GameplayStatics.h"
AActor_BuildingGenerator* BuildingGeneratorr;

ALimbicCityTestPlayerController::ALimbicCityTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ALimbicCityTestPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	UWorld* World = GetWorld();

	AActor* FoundActor;
	FoundActor = UGameplayStatics::GetActorOfClass(World, AActor_BuildingGenerator::StaticClass());


	if (FoundActor->IsA(AActor_BuildingGenerator::StaticClass()))
	{
		BuildingGeneratorr = static_cast<AActor_BuildingGenerator*>(FoundActor);
	}
}

void ALimbicCityTestPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this,
		                                   &ALimbicCityTestPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
		                                   &ALimbicCityTestPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
		                                   &ALimbicCityTestPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
		                                   &ALimbicCityTestPlayerController::OnSetDestinationReleased);

		// // Setup touch input events
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this,
		//                                    &ALimbicCityTestPlayerController::OnInputStarted);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this,
		//                                    &ALimbicCityTestPlayerController::OnTouchTriggered);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this,
		//                                    &ALimbicCityTestPlayerController::OnTouchReleased);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this,
		//                                    &ALimbicCityTestPlayerController::OnTouchReleased);
	}
}

void ALimbicCityTestPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ALimbicCityTestPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ALimbicCityTestPlayerController::OnSetDestinationReleased()
{
	if (BuildingGeneratorr)
	{
		BuildingGeneratorr->BuildingPut();
	}
	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ALimbicCityTestPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ALimbicCityTestPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
