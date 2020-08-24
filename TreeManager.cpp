// Fill out your copyright notice in the Description page of Project Settings.

#include "TreeManager.h"

#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "DrawDebugHelpers.h"
#include <random>
// Sets default values
ATreeManager::ATreeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATreeManager::BeginPlay()
{
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_real_distribution<double> pos_distribution(-1800.0f, 1800.0f);

	Super::BeginPlay();
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = GetActorRotation();
		const FVector SpawnLocation = FVector(pos_distribution(e), pos_distribution(e), 150);
	//	ATree tree1 = ATree();
	//	tree1.setParams(10, 10, 10, 1);
	//	tree1.SetActorLocation(SpawnLocation);
		//World->SpawnActor<tree1>( SpawnLocation, SpawnRotation);
	}
}

// Called every frame
void ATreeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

