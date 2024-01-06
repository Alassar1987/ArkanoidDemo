// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLayoutController.h"

// Sets default values
ABlockLayoutController::ABlockLayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BlockMesh = nullptr;
	BlockType = EBlockType::Option1;
	ShapeSelector = EShapeSelector::Option1;
	Columns = 1;
	Raws = 1;
	BlocksGap = FVector(15.0f,0.0f,15.0f);
	BlockBoundsSize = FVector(0.0f,0.0f,0.0f);
	BlocksQuantity = 0;

	IndestructableMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_White.MI_White'")));
    OneHPMaterial =  Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Blue.MI_Blue'")));
	TwoHPMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Yellow.MI_Yellow'")));
	UE_LOG(LogTemp, Warning, TEXT("ConstructionWorked"));
}

	
void ABlockLayoutController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	//PlaceBlock(FVector(0.0f,0.0f,0.0f));
	//PlaceBlock(FVector(115.0f,0.0f,0.0f));
	//PlaceBlock(FVector(230.0f,0.0f,0.0f));
	LayoutSquare();
	UE_LOG(LogTemp, Warning, TEXT("OnConstruction"));
	
}

void ABlockLayoutController::BlockConfig(UBlockBase* TargetBlock)
{
	UMaterialInstance* BlockMaterial;
	switch(BlockType)
	{
		
		//Block is Indestructable
	case EBlockType::Option1:
		if (TargetBlock)
		{
			TargetBlock->bIsDestroyable = false;
			TargetBlock->Health = 0;
			BlockMaterial = IndestructableMaterial;
			if(BlockMaterial)
			{
				TargetBlock->SetMaterial(0,BlockMaterial);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to initialize Material Instance!"));
			}
						
		}
		
		break;
		//Block is Destructible-1HP
	case EBlockType::Option2:
		if(TargetBlock)
		{
			TargetBlock->bIsDestroyable = true;
			TargetBlock->Health = 1;

			BlockMaterial = OneHPMaterial;
			if(BlockMaterial)
			{
				TargetBlock->SetMaterial(0,BlockMaterial);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to initialize Material Instance!"));
			}
		}
		break;
		
		//Block is Destructible-2HP
	case EBlockType::Option3:
		if(TargetBlock)
		{
			TargetBlock->bIsDestroyable = true;
			TargetBlock->Health = 2;
			
			BlockMaterial = TwoHPMaterial;
			if(BlockMaterial)
			{
				TargetBlock->SetMaterial(0,BlockMaterial);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to initialize Material Instance!"));
			}
		}
		break;
	}
}

/** Please add a function description */
UBlockBase* ABlockLayoutController::PlaceBlock(FVector const BlockPosition)
{
	UBlockBase* NewBlock = NewObject<UBlockBase>(this);
	
	//UBlockBase* NewBlock = CreateDefaultSubobject<UBlockBase>(TEXT("Block"));

	SwitchMesh(NewBlock);
	BlockConfig(NewBlock);
	
	NewBlock->SetupAttachment(RootComponent);
	NewBlock->SetRelativeLocation(BlockPosition);
	NewBlock->SetRelativeRotation(FQuat::Identity);
	NewBlock->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
	NewBlock->RegisterComponent();
		
	
	
	return NewBlock;
	
}

/** Please add a function description */
void ABlockLayoutController::SwitchMesh(UBlockBase* TargetBlock)
{
	UStaticMesh* LocalMesh = nullptr;
	
	switch (ShapeSelector)
	{
	case EShapeSelector::Option1:
		LocalMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/c_100.c_100")));
		
		if (!LocalMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load mesh: /Game/Assets/Meshes/c_100.c_100"));
		}
		else
		{
			if(LocalMesh)
			{
				TargetBlock->SetStaticMesh(LocalMesh);
				
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to initialize LocalMesh!"));

			}
			BlockBoundsSize = FVector(100.0f,100.0f,100.0f);
			//UE_LOG(LogTemp, Warning, TEXT("BlockBounds= %s "), *BlockBounds.ToString());
		}
		break;
		
	case EShapeSelector::Option2:
		LocalMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/p_200_100_100.p_200_100_100")));
		if (!LocalMesh)
		{
			//UE_LOG(LogTemp, Error, TEXT("Failed to load mesh: /Game/Assets/Meshes/p_200_100_100.p_200_100_100"));
		}
		else
		{
			if(LocalMesh)
			{
				TargetBlock->SetStaticMesh(LocalMesh);
				//UE_LOG(LogTemp, Warning, TEXT("BlockMesh initialized successfully!"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to initialize LocalMesh!"));
				
			}
			BlockBoundsSize = FVector(200.0f,100.0f,100.0f);
			//UE_LOG(LogTemp, Warning, TEXT("BlockBounds= %s "), *BlockBounds.ToString());
		}
		break;
		
	case EShapeSelector::Option3:
		if (!BlockMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load UPROPERTY BlockMesh"));
		}
		else
		{
			
			LocalMesh = BlockMesh;
			
		}
		break;
		
	}
	if (LocalMesh)
	{
		TargetBlock->SetStaticMesh(LocalMesh);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load LocalMesh: Block is NullPtr"))
	}
	
}


/** Please add a function description */
void ABlockLayoutController::LayoutSquare()
{
	float CoordinateX = 0.0f;
	float CoordinateZ = 0.0f;
	
	
	

	UE_LOG(LogTemp, Warning, TEXT("PreCycle"));
	
	ClearExistingBlocks();
	
	//Vertical Cycle
	for (size_t i = 0; i < Raws; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entering Cycle 1"));
		CoordinateZ = -1*(i*(BlocksGap.Z+BlockBoundsSize.Z)) ;
		//Horizontal Cycle
		for (size_t j = 0; j < Columns; j++)
		{
			CoordinateX = j*(BlocksGap.X + BlockBoundsSize.X);
			UBlockBase* Block = PlaceBlock(FVector(CoordinateX,0.0f,CoordinateZ)); // 226 строка
			BlocksArray.Add(Block);
			//AddBlocksQuantity();
			//UE_LOG(LogTemp, Warning, TEXT("Total Blocks: %d"),BlocksQuantity);
		}
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

void ABlockLayoutController::ClearExistingBlocks()
{
	// Iterate through existing blocks and destroy them
	for (auto& Block : BlocksArray)
	{
		if (Block)
		{
			Block->DestroyComponent();
		}
	}

	// Clear the array
	BlocksArray.Empty();
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