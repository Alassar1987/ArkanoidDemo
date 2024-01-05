// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"


// Default constructor for UBlockBase.
UBlockBase::UBlockBase()
{
	// Initialize default values.
	bIsDestroyable = true;
	Size = FVector(0.0f,0.0f,0.0f);
	Health = 1;
}

// Function to subtract health from the block.
void UBlockBase::SubtractHealth(int32 Damage)
{
	if(bIsDestroyable)
	{
		Health = FMath::Max(Health-Damage, 0);
	}
	
}






