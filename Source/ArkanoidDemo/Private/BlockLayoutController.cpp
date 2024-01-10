// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLayoutController.h"

// Sets default values
ABlockLayoutController::ABlockLayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	// Initialize default values for the block layout
	BlockMesh = nullptr;
	BlockType = EBlockType::Option1;
	ShapeSelector = EShapeSelector::Option1;
	Columns = 1;
	Raws = 1;
	BlocksGap = FVector(15.0f,0.0f,15.0f);
	BlockBoundsSize = FVector(0.0f,0.0f,0.0f);
	BlocksQuantity = 0;

	// Load material instances for different block types
	IndestructableMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_White.MI_White'")));
    OneHPMaterial =  Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Blue.MI_Blue'")));
	TwoHPMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/2D/Materials/Coloring/MI_Yellow.MI_Yellow'")));
	
}

/**
 * Construction script implementation.
 * This function is called when the actor is constructed or when the editor is manipulating the actor.
 * It invokes the QuadrangleLayout function to handle construction-time initialization and updates.
 * @param Transform The transform of the actor when constructed.
 */
void ABlockLayoutController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
		
	QuadrangleLayout();
		
}

/**
 * Implementation of BlockConfig function.
 *
 * @param TargetBlock The block to be configured.
 */
void ABlockLayoutController::BlockConfig(UBlockBase* TargetBlock)
{
	UMaterialInstance* BlockMaterial;
	switch(BlockType)
	{

		//Block is Indestructable
	case EBlockType::Option1:
		if (TargetBlock)
		{
			// Set block properties for an indestructible block
			TargetBlock->bIsDestructable = false;
			TargetBlock->Health = 0;

			// Set material for the block
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
			// Set block properties for a destructible block with 1 health point
			TargetBlock->bIsDestructable = true;
			TargetBlock->Health = 1;
			
			// Set material for the block
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
			// Set block properties for a destructible block with 2 health points
			TargetBlock->bIsDestructable = true;
			TargetBlock->Health = 2;

			// Set material for the block
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

/**
 * Implementation of the PlaceBlock function.
 *
 * @param BlockPosition The position where the new block will be placed.
 * @return The newly created block.
 */
UBlockBase* ABlockLayoutController::PlaceBlock(FVector const BlockPosition)
{
	// Create a new block object
	UBlockBase* NewBlock = NewObject<UBlockBase>(this);

	// Set the mesh and configuration for the new block
	SwitchMesh(NewBlock);
	BlockConfig(NewBlock);

	// Set the relative location, rotation, and scale for the new block
	NewBlock->SetupAttachment(RootComponent);
	NewBlock->SetRelativeLocation(BlockPosition);
	NewBlock->SetRelativeRotation(FQuat::Identity);
	NewBlock->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));

	// Register the new block as an Actor Component
	NewBlock->RegisterComponent();

	// Return the newly created block
	return NewBlock;
	
}

/**
 * Implementation of the SwitchMesh function.
 *
 * @param TargetBlock The block whose mesh will be switched.
 */
void ABlockLayoutController::SwitchMesh(UBlockBase* TargetBlock)
{
	// Local variable to store the loaded mesh
	UStaticMesh* LocalMesh = nullptr;

	// Switch statement based on the selected shape
	switch (ShapeSelector)
	{

	// Option 1: Cube
	case EShapeSelector::Option1:
		// Load the cube mesh
		LocalMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/c_100.c_100")));

		// Check if the mesh loaded successfully
		if (!LocalMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load mesh: /Game/Assets/Meshes/c_100.c_100"));
		}
		
		else
		{
			// Set the static mesh for the target block
			TargetBlock->SetStaticMesh(LocalMesh);
			BlockBoundsSize = FVector(100.0f,100.0f,100.0f);
			
		}
		break;

	// Option 2: Double Cube
	case EShapeSelector::Option2:

		// Load the double cube mesh
		LocalMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Meshes/p_200_100_100.p_200_100_100")));

		// Check if the mesh loaded successfully
		if (!LocalMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load mesh: /Game/Assets/Meshes/p_200_100_100.p_200_100_100"));
		}
		
		else
		{
			
			TargetBlock->SetStaticMesh(LocalMesh);
			BlockBoundsSize = FVector(200.0f,100.0f,100.0f);
		}
		break;

		// Option 3: Manual Selection
	case EShapeSelector::Option3:
		
		// Check if the mesh loaded successfully
		if (!BlockMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load UPROPERTY BlockMesh"));
		}
		else
		{
			// Use the provided BlockMesh property
			LocalMesh = BlockMesh;
			TargetBlock->SetStaticMesh(LocalMesh);
		}
		break;
		
	}
	
	// if (LocalMesh)
	// {
	// 	TargetBlock->SetStaticMesh(LocalMesh);
	// }
	//
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to load LocalMesh: Block is NullPtr"))
	// }
	
}


/**
 * Implementation of QuadrangleLayout function.
 * Arranges blocks in a quadrangle layout based on the specified number of rows and columns.
 */
void ABlockLayoutController::QuadrangleLayout()
{
	float CoordinateX = 0.0f;
	float CoordinateZ = 0.0f;

	// Clears existing blocks before laying out new ones 
	ClearExistingBlocks();
	
	//Vertical Cycle
	for (size_t i = 0; i < Raws; i++)
	{
		CoordinateZ = -1*(i*(BlocksGap.Z+BlockBoundsSize.Z)) ;

		//Horizontal Cycle
		for (size_t j = 0; j < Columns; j++)
		{
			CoordinateX = j*(BlocksGap.X + BlockBoundsSize.X);
			UBlockBase* Block = PlaceBlock(FVector(CoordinateX,0.0f,CoordinateZ));
			BlocksArray.Add(Block);
			AddBlocksQuantity();
		}
	}
}

/**
 * Implementation of AddBlocksQuantity function.
 * Increments the count of blocks.
 */
void ABlockLayoutController::AddBlocksQuantity()
{
	++BlocksQuantity;
}

/**
 * Implementation of SubtractBlocksQuantity function.
 * Decreases the block quantity by one, ensuring it does not go below zero.
 */
void ABlockLayoutController::SubtractBlocksQuantity()
{
	// Ensure BlocksQuantity does not go below zero
	BlocksQuantity = FMath::Max(--BlocksQuantity,0);
}

/**
 * Implementation of SelfDestruct function.
 * Destroys the block layout controller if the block quantity is less than or equal to zero.
 */
void ABlockLayoutController::SelfDestruct()
{
	if (BlocksQuantity <= 0)
	{
		Destroy();
	}
}

/**
 * Implementation of ClearExistingBlocks function.
 * Iterates through existing blocks, destroys them, and clears the array.
 */
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

/**
 * Implementation of the NotifyHit function.
 * Note: This functionality is still under development.
 * This function logs information about the block and the actor that collided with it.
 * @param MyComp The primitive component of the block.
 * @param Other The actor that collided with the block.
 * @param OtherComp The primitive component of the other actor.
 * @param bSelfMoved Indicates whether the collision was caused by the block itself moving.
 * @param HitLocation The location where the collision occurred.
 * @param HitNormal The normal vector at the collision point.
 * @param NormalImpulse The impulse applied during the collision.
 * @param Hit The hit result containing information about the collision.
 */
void ABlockLayoutController::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the other actor is valid and not equal to this block    
	if (Other && Other != this)
	{
		// Get the names of the block and the other actor
       	FString BlockName = MyComp->GetName();
		FString OtherActorName = Other->GetName();

		// Log information about the collision
		UE_LOG(LogTemp, Warning, TEXT("%s was hit by %s"), *BlockName, *OtherActorName);
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

