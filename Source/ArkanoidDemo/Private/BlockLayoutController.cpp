// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLayoutController.h"

// Sets default values
ABlockLayoutController::ABlockLayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockType = EBlockType::Option1;
	BlockSize = EBlockSize::Option1;
	Columns = 1;
	Raws = 1;
	GAP = FVector(15.0f,0.0f,15.0f);
	BlockBounds = FVector(0.0f,0.0f,0.0f);
	BlocksQuantity = 0;
	
AddBlocksQuantity();
}

/** Please add a function description */
void ABlockLayoutController::LayoutCube()
{
	;
}

/** Please add a function description */
void ABlockLayoutController::AddBlocksQuantity()
{
	++BlocksQuantity;
}

/** Please add a function description */
void ABlockLayoutController::SubtractBlocksQuantity()
{
	BlocksQuantity = FMath::Max(--BlocksQuantity,0);
}

/** Please add a function description */
void ABlockLayoutController::SelfDestruct()
{
	if (BlocksQuantity <= 0)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void ABlockLayoutController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockLayoutController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

