// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.h"
#include "TreeManager.generated.h"

UCLASS()
class MYPROJECT_API ATreeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeManager();
	//float thickness = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		int Number_of_bushes = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		int Number_of_weeds = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		int Number_of_trees = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
