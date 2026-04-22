// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QA_TECH_TEST_API USprintingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintingComponent();

	bool bIsSprinting = false;

	void StartSprinting();
	void StopSprinting();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiplier = 1.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaDrainRate = 20.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
