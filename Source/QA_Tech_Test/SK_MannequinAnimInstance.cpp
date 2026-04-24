// Fill out your copyright notice in the Description page of Project Settings.


#include "SK_MannequinAnimInstance.h"
#include "MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USK_MannequinAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	myCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (myCharacter)
	{
		myCharacterMovement = myCharacter->GetCharacterMovement();
	}
}

void USK_MannequinAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (myCharacterMovement)
	{
		groundSpeed = UKismetMathLibrary::VSizeXY(myCharacterMovement->Velocity);
		bIsFalling = myCharacterMovement->IsFalling();
	}
}