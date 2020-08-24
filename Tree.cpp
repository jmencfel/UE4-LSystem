// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "DrawDebugHelpers.h"
#include "LSystem.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	up = GetActorUpVector();
	col = FColor::Red;
	thickness = 3.0f;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	//RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialOb(TEXT("Material'/Game/Geometry/Meshes/Tree.Tree'"));
	Material = MaterialOb.Object;

}
void ATree::setParams(float l, float a, float leng, int typ)
{
	loops = l;
	angle_rand = a;
	length_rand = leng;
	type = typ;

}
void ATree::PostActorCreated()
{
	Super::PostActorCreated();
	CreateTriangle();
}
void ATree::PostLoad()
{
	Super::PostLoad();
	CreateTriangle();
}
void ATree::CreateTriangle()
{
	TArray<FVector> vertices;
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(0, 150, 0));
	vertices.Add(FVector(0, 0, 150));

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector> normals;
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(10, 0));
	UV0.Add(FVector2D(0, 10));


	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

//	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	// Enable collision data
//	mesh->ContainsPhysicsTriMeshData(true);
}
// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	current_location = GetActorLocation();
	length = length_rand;
	angle = angle_rand;
	LSystem lsys;
	if (type == 1)
	{
		lsys.setType("tree");
	}
	//render();

	for (int i = 0; i < loops; i++)
	{
		lsys.generate();
	}
	sentence = lsys.getSentence();
	render();
	
	//CreateTriangle();
}


void ATree::render()
{
	//length *= 0.99f;
	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;
	////// thickness of treee meshes at the base of a segment and at the top of the segment
	int tree_thickness = 8;
	int tree_thickness_top = 1;
	////////number of vertices added by each tree segment
	int var = 8;
	/////// counts chars in sentence that were not drawing lines ( needed for indexing of triangles)
	int not_drawing_count = 0;
	///////random multiplier for length of the first segment
	float multip = FMath::RandRange(10, 20) / 10.0f;
	for (int i = 0; i < sentence.length(); i++)
	{
		//thickness *= 0.99f;
		int extra = FMath::RandRange(15, 60);
		int rand_angle = FMath::RandRange(0, 0);
		char c = sentence.at(i);
		if (c == 'F')
		{
			if (type == 1)
			{

				tree_thickness = FMath::Clamp(int(40 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(40 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 0)
			{
				tree_thickness = FMath::Clamp(int(10 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(10 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 2)
			{
				tree_thickness = FMath::Clamp(int(4 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(4 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			vertices.Add(GetActorLocation());
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)));
			vertices.Add(GetActorLocation() + up * length);
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length);
			vertices.Add(GetActorLocation() + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + up * length + FVector(tree_thickness_top, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length + FVector(tree_thickness_top, 0, 0));
			/////////////////////front side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)));		//normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			////////////////////back side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 5); //normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			////////////////////left side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 4);	//normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));//	normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));	//normals.Add(FVector(0, 1, 0));
			////////////////////right side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			
			individual_locations.push(GetActorLocation() + up * length);
			individual_ups.push(up);
		//	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + up* (length), col, false, 5, 5, thickness);
			SetActorLocation(GetActorLocation() + up* (length));
		}
		
		else if (c == 'G')
		{
			if (!first_run)
			{
				SetActorLocation(individual_locations.front());
				individual_locations.pop();
				up = individual_ups.front();
				individual_ups.pop();
			}
			if (type == 1)
			{

				tree_thickness = FMath::Clamp(int(40 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(40 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 0)
			{
				tree_thickness = FMath::Clamp(int(10 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(10 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 2)
			{
				tree_thickness = FMath::Clamp(int(5 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(5 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			vertices.Add(GetActorLocation());
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)));
			vertices.Add(GetActorLocation() + up * length);
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length);
			vertices.Add(GetActorLocation() + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + up * length + FVector(tree_thickness_top, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length + FVector(tree_thickness_top, 0, 0));
			/////////////////////front side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)));		//normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			////////////////////back side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 5); //normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			////////////////////left side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 4);	//normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));//	normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));	//normals.Add(FVector(0, 1, 0));
			////////////////////right side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			
			
			individual_locations.push(GetActorLocation() + up * length);
			individual_ups.push(up);
		//	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + up * (length), col, false, 5, 5, thickness);
			SetActorLocation(GetActorLocation() + up * (length));

			
		}
		else if (c == 'S')
		{
		length *= multip;
			if (!first_run)
			{
				SetActorLocation(individual_locations.front());
				individual_locations.pop();
				up = individual_ups.front();
				individual_ups.pop();
			}
			if (type == 1)
			{

				tree_thickness = FMath::Clamp(int(40 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(40 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 0)
			{
				tree_thickness = FMath::Clamp(int(10 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(10 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			else if (type == 2)
			{
				tree_thickness = FMath::Clamp(int(5 - ((GetActorLocation() - current_location).Size() / 20)), 0, 40);
				tree_thickness_top = FMath::Clamp(int(5 - ((GetActorLocation() + up * length - current_location).Size() / 20)), 0, 40);
			}
			vertices.Add(GetActorLocation());
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)));
			vertices.Add(GetActorLocation() + up * length);
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length);
			vertices.Add(GetActorLocation() + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + FVector(tree_thickness, 0, 0));
			vertices.Add(GetActorLocation() + up * length + FVector(tree_thickness_top, 0, 0));
			vertices.Add(GetActorLocation() + tree_thickness_top * FVector::CrossProduct(up / up.Size(), FVector(1, 0, 0)) + up * length + FVector(tree_thickness_top, 0, 0));
			/////////////////////front side of each tree segment
			Triangles.Add((var * (i-not_drawing_count)));		//normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2); //normals.Add(FVector(1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(1, 0, 0));
			////////////////////back side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 5); //normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(-1, 0, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 4);// normals.Add(FVector(-1, 0, 0));
			////////////////////left side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 4);	//normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));//	normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 2);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 6);// normals.Add(FVector(0, 1, 0));
			Triangles.Add((var * (i - not_drawing_count)));	//normals.Add(FVector(0, 1, 0));
			////////////////////right side of each tree segment
			Triangles.Add((var * (i - not_drawing_count)) + 1); //normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 7);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 3);// normals.Add(FVector(0, -1, 0));
			Triangles.Add((var * (i - not_drawing_count)) + 5);//	normals.Add(FVector(0, -1, 0));
			

			
			
			individual_locations.push(GetActorLocation() + up * length);
			individual_ups.push(up);
			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + up * (length), col, false, 5, 5, thickness);
			SetActorLocation(GetActorLocation() + up * (length));
			length /= multip;
		}
		else if (c == '+')
		{
		not_drawing_count++;
			up = up.RotateAngleAxis(angle+ rand_angle, FVector(1.f, 0.f, 0.f));

		}
		else if (c == '-')
		{
		not_drawing_count++;
			up = up.RotateAngleAxis(-angle - rand_angle, FVector(1.f, 0.f, 0.f));

		}
		else if (c == '*')
		{
		not_drawing_count++;
			up = up.RotateAngleAxis(45 + extra , FVector(0.f, 0.f, 1.f));

		}
		else if (c == '/')
		{
		not_drawing_count++;
			up = up.RotateAngleAxis(-45 - extra, FVector(0.f, 0.f, 1.f));

		}
		else if (c == '[')
		{			
		not_drawing_count++;
			saved_locations.push(GetActorLocation());
			saved_ups.push(up);
			
		}
		else if (c == ']')
		{
		not_drawing_count++;
			SetActorLocation(saved_locations.top());
			saved_locations.pop();		
			up = saved_ups.top();
			saved_ups.pop();
		}
		first_run = false;		
	
	}		
	for (int32 i = 0; i < vertices.Num(); i++)
	{
		vertexColors.Add(FLinearColor::Red);
	}
	SetActorLocation(FVector(0,0,0));
	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	mesh->SetMaterial(0, Material);
	// Enable collision data

		mesh->ContainsPhysicsTriMeshData(true);
	
	
}
void ATree::setAngle(float a) { angle = a; }
void ATree::setLength(float a) { length = a; }
void ATree::setSentence(std::string a) { sentence = a; }
// Called every frame
void ATree::Tick(float DeltaTime)
{		
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("LEL HELLLO:  %s"), sentence));
}

