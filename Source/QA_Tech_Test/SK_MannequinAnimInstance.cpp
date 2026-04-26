// Fill out your copyright notice in the Description page of Project Settings.


#include "SK_MannequinAnimInstance.h"
#include "BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void USK_MannequinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	myCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (myCharacter)
	{
		myCharacterMovement = myCharacter->GetCharacterMovement();
	}
}

void USK_MannequinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (myCharacterMovement && myCharacter)
	{
		FVector Velocity = myCharacter->GetVelocity();
		groundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		bIsFalling = myCharacterMovement->IsFalling();

		FRotator Rotation = myCharacter->GetActorRotation();
		// angle between -180 and 180
		groundDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);
	}
}