// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "SK_MannequinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class QA_TECH_TEST_API USK_MannequinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMyCharacter* myCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	class UCharacterMovementComponent* myCharacterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float groundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float groundDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	bool bIsFalling;
	
};
