// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BlockBase.generated.h"

/**
* Custom block component derived from UStaticMeshComponent.
*/
UCLASS(Blueprintable,BlueprintType)
class ARKANOIDDEMO_API UBlockBase : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	
	UBlockBase();

	/**
	 *Subtracts health from the block.
	 * @param Damage The amount of health to subtract.
	 */
	UFUNCTION(BlueprintCallable)
	void SubtractHealth(int32 Damage);
	
	/** 
	 * Indicates whether the block can be destroyed.
	 * Editable in Blueprints and defaults to true.
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category ="Block Structure")
	bool bIsDestroyable;

	/** 
	 * The health of the block.
	 * Editable in Blueprints and defaults to 0.
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category ="Block Structure")
	int32 Health;

	/** 
	 * The size of the block.
	 * Editable in Blueprints and defaults to FVector(100, 100, 100).
	 * Represents the dimensions of the block in the world.
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category ="Block Structure")
	FVector Size;

	
};
