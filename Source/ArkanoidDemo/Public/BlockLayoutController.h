// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockLayoutController.generated.h"

// Enum declaration
UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Option1 UMETA(DisplayName = "Destructible"),
	Option2 UMETA(DisplayName = "Indestructible")
};

UENUM(BlueprintType)
enum class EBlockSize : uint8
{
	Option1 UMETA(DisplayName = "Cube"),
	Option2 UMETA(DisplayName = "DoubleCube")	
};

UCLASS(Blueprintable,BlueprintType)
class ARKANOIDDEMO_API ABlockLayoutController : public AActor
{
	GENERATED_BODY()

public:

	ABlockLayoutController();
	
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void LayoutCube();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void AddBlocksQuantity();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void SubtractBlocksQuantity();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void SelfDestruct();



	//SomeDesctription
	UPROPERTY(Blueprintable,EditAnywhere,Category ="BlockPropertie")
	EBlockType BlockType;
	
	//SomeDesctription
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category ="BlockPropertie")
	EBlockSize BlockSize;
	
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
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="BlockBounds")
	FVector BlockBounds;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Layout Settings")
	int32 BlocksQuantity;



		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
