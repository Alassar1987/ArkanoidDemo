// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLayoutController.h"

// Sets default values
ABlockLayoutController::ABlockLayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Block = nullptr;
	BlockMesh = nullptr;
	BlockType = EBlockType::Option1;
	ShapeSelector = EShapeSelector::Option1;
	Columns = 1;
	Raws = 1;
	GAP = FVector(15.0f,0.0f,15.0f);
	BlockBounds = FVector(0.0f,0.0f,0.0f);
	BlocksQuantity = 0;

	IndestructableMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_White.MI_White'")));
    OneHPMaterial =  Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Blue.MI_Blue'")));
	TwoHPMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Yellow.MI_Yellow'")));
}

	
void ABlockLayoutController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	PlaceBlock();
	
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
	UBlockBase* NewBlock = NewObject<UBlockBase>(this, TEXT("Block"));

	NewBlock->SetupAttachment(RootComponent);
	NewBlock->SetRelativeLocation(BlockPosition);
	NewBlock->SetRelativeRotation(FQuat::Identity);
	NewBlock->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
	NewBlock->RegisterComponent();
		
	SwitchMesh(NewBlock);
	BlockConfig(NewBlock);
	
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
			BlockBounds = FVector(100.0f,100.0f,100.0f);
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
			BlockBounds = FVector(200.0f,100.0f,100.0f);
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
	//Vertical Cycle
	for (size_t i = 0; i < (Raws-1); i++)
	{
		//Horizontal Cycle
		for (size_t j = 0; j < (Columns-1); i++)
		{
			PlaceBlock();
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