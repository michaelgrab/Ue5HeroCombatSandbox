// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintingComponent.h"

// Sets default values for this component's properties
USprintingComponent::USprintingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USprintingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USprintingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsSprinting && CurrentStamina > 0)
    {
        CurrentStamina -= StaminaDrainRate * DeltaTime;
        if (CurrentStamina <= 0)
        {
            StopSprinting();
        }
    }
    else if (CurrentStamina < MaxStamina)
    {
        CurrentStamina += (StaminaDrainRate * 0.5f) * DeltaTime;
    }

}

void USprintingComponent::StartSprinting(){ bIsSprinting = true; }
void USprintingComponent::StopSprinting(){ bIsSprinting = false; }

