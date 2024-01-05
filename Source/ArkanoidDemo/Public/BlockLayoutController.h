// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.h"
#include "BlockLayoutController.generated.h"

// Enum declaration

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Option1 UMETA(DisplayName = "Indestructible"),
	Option2 UMETA(DisplayName = "Destructible-1HP"),
	Option3 UMETA(DisplayName = "Destructible-2HP")
};

UENUM(BlueprintType)
enum class EShapeSelector : uint8
{
	Option1 UMETA(DisplayName = "Cube"),
	Option2 UMETA(DisplayName = "DoubleCube"),
	Option3 UMETA(DisplayName = "Manual Selection")
};

UCLASS(Blueprintable,BlueprintType)
class ARKANOIDDEMO_API ABlockLayoutController : public AActor
{
	GENERATED_BODY()

public:

	ABlockLayoutController();

	// --FUNCTIONS SECTION--
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void LayoutSquare();

	
	UFUNCTION(Blueprintable)
	void BlockConfig(UBlockBase* TargetBlock);
	
	UFUNCTION(BlueprintCallable)
	UBlockBase* PlaceBlock(FVector BlockPosition = FVector(0.0f,0.0f,0.0f));
	
	// /** Please add a function description */
	// UFUNCTION(Blueprintable)
	// void SetBlockMesh(UBlockBase* TargetBlock);
	
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void SwitchMesh(UBlockBase* TargetBlock);
	
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void AddBlocksQuantity();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void SubtractBlocksQuantity();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void SelfDestruct();
	
	// --PROPERTIES SECTION--
	UPROPERTY(Blueprintable,EditAnywhere, Category= "BlockShape")
	EShapeSelector ShapeSelector;

	//SomeDesctription
	UPROPERTY(Blueprintable,EditAnywhere, Category= "BlockShape", meta=(EditCondition = "ShapeSelector == EShapeSelector::Option3",EditConditionHides))
	UStaticMesh* BlockMesh;

		
	//SomeDesctription
	UPROPERTY(Blueprintable,EditAnywhere,Category ="BlockProperties")
	EBlockType BlockType;
	
	// //SomeDesctription
	//  UPROPERTY(Blueprintable)
	//  UBlockBase* Block = nullptr;
		
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="1", UIMax="100", ClampMin="1", ClampMax="100"))
	int32 Columns;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="1", UIMax="100", ClampMin="1", ClampMax="100"))
	int32 Raws;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LayoutSettings", meta=(UIMin="0", ClampMin="0", UIMax="1000", ClampMax="1000"))
	FVector GAP;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BlockShape",meta=(EditCondition = "ShapeSelector == EShapeSelector::Option3",EditConditionHides))
	FVector BlockBounds;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Layout Settings")
	int32 BlocksQuantity;

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	
	//Construction Script
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBlockBase* BlockBase = nullptr;
	UMaterialInstance* IndestructableMaterial = nullptr;
	UMaterialInstance* OneHPMaterial = nullptr;
	UMaterialInstance* TwoHPMaterial = nullptr;

};
