// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"

// Default constructor for UBlockBase.
UBlockBase::UBlockBase()
{
	// Initialize default values.
	IsDestroyable = true;
	Size = FVector(100.0f,100.0f,100.0f);
	Health = 1;
}

// Function to subtract health from the block.
void UBlockBase::SubtractHealth(int32 Damage)
{
	if(IsDestroyable)
	{
		Health = FMath::Max(Health-Damage, 0);
	}
	
}



