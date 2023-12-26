// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLayoutController.h"



// Sets default values
ABlockLayoutController::ABlockLayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	
	Block = nullptr;
	BlockMesh = nullptr;
	BlockType = EBlockType::Option1;
	BlockSize = EBlockSize::Option1;
	Columns = 1;
	Raws = 1;
	GAP = FVector(15.0f,0.0f,15.0f);
	BlockBounds = FVector(0.0f,0.0f,0.0f);
	BlocksQuantity = 0;
	
}

	
void ABlockLayoutController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	AddBlock();
	
}

/** Please add a function description */
void ABlockLayoutController::AddBlock()
{
	
	//Block = CreateDefaultSubobject<UBlockBase>(TEXT("Block"));
	Block = NewObject<UBlockBase>(this, TEXT("MyStaticMeshComponent"));
	Block->SetupAttachment(RootComponent);
	Block->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
	Block->SetRelativeRotation(FQuat::Identity);
	Block->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));

	switch (BlockSize)
		{
		case EBlockSize::Option1:
			BlockMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/c_100.c_100")));
			//BlockMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Script/Engine.StaticMesh'/Game/Assets/Meshes/c_100.c_100'")));
			//static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Assets/Meshes/c_100.c_100"));
			break;
		case EBlockSize::Option2:
			BlockMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/p_200_100_100.p_200_100_100")));
			//BlockMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Script/Engine.StaticMesh'/Game/Assets/Meshes/p_200_100_100.p_200_100_100'")));
			//static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Assets/Meshes/p_200_100_100.p_200_100_100"));
			break;
		}
	
	if(BlockMesh)
	{
		Block->SetStaticMesh(BlockMesh);
		UE_LOG(LogTemp, Warning, TEXT("BlockMesh initialized successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize BlockMesh!"));

	}

	Block->RegisterComponent();
	
}


/** Please add a function description */
void ABlockLayoutController::LayoutCube()
{
	//First Cycle
	for (size_t i = 0; i < (Raws-1); i++)
	{
		;
	}

	for (size_t i = 0; i < (Columns-1); i++)
	{
		;
	}
	
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

