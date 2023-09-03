// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ListView.h"

#include "Components/Button.h"
#include "Components/ListView.h"
#include "Actor_BuildingGenerator.h"
#include "Kismet/GameplayStatics.h"
AActor_BuildingGenerator* BuildingGenerator;
void UC_ListView::NativeConstruct()
{
	Super::NativeConstruct();

	//auto Event = MyList->OnItemClicked();
	//Event.AddUObject(this, &UC_ListView::MyEventCallback);
	//MyList->OnItemClicked.AddDynamic(this, &UC_ListView::OnButtonClicked);

	auto Event = MyList->OnItemClicked();
	Event.AddUObject(this, &UC_ListView::MyEventCallback);

	UWorld* World = GetWorld();

	AActor* FoundActor;
	FoundActor = UGameplayStatics::GetActorOfClass(World, AActor_BuildingGenerator::StaticClass());


	if (FoundActor->IsA(AActor_BuildingGenerator::StaticClass()))
	{
		BuildingGenerator = static_cast<AActor_BuildingGenerator*>(FoundActor);
		for(int32 i=0;i<BuildingGenerator->ClassArrays.Num();i++)
		{
			UMyButton* TempButton = NewObject<UMyButton>();
			//TempButton->buttonIndex=i;
			TempButton->Click.AddUniqueDynamic(this,&UC_ListView::OnPlacementButtonClicked);
			//TempButton->click.AddDynamic(this,&AActor_BuildingGenerator::SpawnBuilding);
			ButtonArray.Add(TempButton);
		}
		
	}

	MyList->SetListItems(ButtonArray);
}

void UC_ListView::OnPlacementButtonClicked(int n)
{
	BuildingGenerator->SpawnBuilding(n);
}

void UC_ListView::MyEventCallback(UObject* Object)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("List View Element"));
}

void UC_ListView::OnButtonClicked(int Index)
{
	//UE_LOG(LogTemp, Warning, TEXT("Button clicked at index: %d"), Index);
}

void MyEventCallback(UObject* e)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Started"));
}
