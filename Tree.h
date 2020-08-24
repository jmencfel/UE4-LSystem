// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include <stack> 
#include <queue> 
#include "CoreMinimal.h"
#include "Engine.h"


#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Tree.generated.h"




UCLASS()
class MYPROJECT_API ATree : public AActor
{
private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent * mesh;
	UPROPERTY(VisibleAnywhere, Category = ProcMesh)
		UMaterial* Material;
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	void CreateTriangle();
	std::string sentence;
	float length;
	float angle;
	FVector start;
	FVector current_location;
	std::stack<FVector> saved_locations;
	std::stack<FVector> saved_ups;
	std::queue<FVector> individual_locations;
	std::queue<FVector> individual_ups;
	FVector up;
	bool first_run = true;
	FColor col;
	float thickness;
	//float thickness = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		float loops = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		float angle_rand = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		float length_rand = 120.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
		int type = 0;

public:	
	// Sets default values for this actor's properties
	ATree();
	void setParams(float l, float a, float leng, int typ);
	void render();
	void setLength(float f);
	void setAngle(float a);
	void setSentence(std::string a);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
