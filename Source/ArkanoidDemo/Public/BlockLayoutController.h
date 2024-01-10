// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.h"
#include "BlockLayoutController.generated.h"

//--ENUM DECLARATION--

// Enumerates the different types of blocks that can be placed in the game.
UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Option1 UMETA(DisplayName = "Indestructible"),
	Option2 UMETA(DisplayName = "Destructible-1HP"),
	Option3 UMETA(DisplayName = "Destructible-2HP")
};

// Enumerates the different shapes for blocks in the game.
UENUM(BlueprintType)
enum class EShapeSelector : uint8
{
	Option1 UMETA(DisplayName = "Cube"),
	Option2 UMETA(DisplayName = "DoubleCube"),
	Option3 UMETA(DisplayName = "Manual Selection")
};


/**
 * ABlockLayoutController is the main class responsible for laying out and managing blocks in the game.
 * It handles block configurations, placement, properties update and destroying blocks during gameplay.
 */
UCLASS(Blueprintable,BlueprintType)
class ARKANOIDDEMO_API ABlockLayoutController : public AActor
{
	GENERATED_BODY()

public:

	/**
	 * Default constructor for ABlockLayoutController.
	 * Initializes the default values and sets up any necessary components.
	 */
	ABlockLayoutController();

	// --FUNCTIONS SECTION--

	/**
	 * Builds a layout of blocks in the shape of a quadrangle (rectangle or square).
	 * The layout is determined by the number of rows and columns specified in the properties.
	 *
	 * Note: The functionality of this function may be extended in the future to support additional shapes,
	 * such as parallelograms. Please refer to the updated documentation for any new features.
	 */
	void QuadrangleLayout();

	/**
	 * Configures the specified block based on the chosen block type.
	 *
	 * @param TargetBlock The block to be configured.
	 */
	void BlockConfig(UBlockBase* TargetBlock);

	/**
	 * Places a new block at the specified position in the layout.
	 *
	 * @param BlockPosition The position where the new block will be placed.
	 * @return The newly created block.
	 */
	UBlockBase* PlaceBlock(FVector BlockPosition = FVector(0.0f,0.0f,0.0f));
	
		
	/**
	 * Switches the mesh of the target block based on the selected shape.
	 *
	 * @param TargetBlock The block whose mesh will be switched.
	 */
	void SwitchMesh(UBlockBase* TargetBlock);
	
	/**
	 * Increases the count of blocks.
	 */
	void AddBlocksQuantity();

	/**
	 * Decreases the block quantity by one, ensuring it does not go below zero.
	 */
	void SubtractBlocksQuantity();

	/**
	 * Destroys the block layout controller if the block quantity is less than or equal to zero.
	 */
	void SelfDestruct();
	
	// --PROPERTIES SECTION--

	/** Enum to define the shape of the blocks. */
	UPROPERTY(Blueprintable,EditAnywhere, Category= "BlockShape")
	EShapeSelector ShapeSelector;

	/** Mesh for the block when 'Manual Selection' is chosen as the shape. */
	UPROPERTY(Blueprintable,EditAnywhere, Category= "BlockShape", meta=(EditCondition = "ShapeSelector == EShapeSelector::Option3",EditConditionHides))
	UStaticMesh* BlockMesh;

	/** Size of the block when 'Manual Selection' is chosen as the shape. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BlockShape",meta=(EditCondition = "ShapeSelector == EShapeSelector::Option3",EditConditionHides))
	FVector BlockBoundsSize;
		
	/** Type of the block, indicating its destructibility. */
	UPROPERTY(Blueprintable,EditAnywhere,Category ="BlockProperties")
	EBlockType BlockType;
	
	/** Number of columns in the block layout. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="1", UIMax="100", ClampMin="1", ClampMax="100"))
	int32 Columns;

	/** Number of rows in the block layout. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="1", UIMax="100", ClampMin="1", ClampMax="100"))
	int32 Raws;

	/** Gap between the blocks in the layout. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="0", ClampMin="0", UIMax="1000", ClampMax="1000"))
	FVector BlocksGap;
	
	/** Total quantity of blocks in the layout. */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Layout Settings")
	int32 BlocksQuantity;

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	
	/**
	 * Construction script called when the actor is constructed or when the editor is manipulating the actor.
	 * This function is used to handle construction-time initialization and updates.
	 * @param Transform The transform of the actor when constructed.
	 */
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

	/**
	 * Event handler for collision notifications.
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
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	
	
	/**
	 * Clears the existing blocks by destroying them and emptying the Blocks Array.
	 */
	void ClearExistingBlocks();

	// Main block managing the functionality of individual blocks
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBlockBase* BlockBase = nullptr;

	// Array for storing created blocks
	TArray<UBlockBase*> BlocksArray;
	
	// Materials for different types of blocks
	UMaterialInstance* IndestructableMaterial = nullptr;
	UMaterialInstance* OneHPMaterial = nullptr;
	UMaterialInstance* TwoHPMaterial = nullptr;
	

};
