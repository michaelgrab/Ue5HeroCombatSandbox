// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - ActualDamage, 0.0f, MaxHealth);
	FString DebugMsg = FString::Printf(TEXT("%s takes %.2f damage"), *GetName(), DamageAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMsg);


	if (Health <= 0.0f)
	{
		HandleDeath();
	}

	return ActualDamage;
}

void ABaseCharacter::RegisterAttackHit(AActor* HitActor, float DamageValue)
{
	if (HitActor && HitActor != this && !HitActorsThisAttack.Contains(HitActor))
	{
		HitActorsThisAttack.Add(HitActor);

		UGameplayStatics::ApplyDamage(
			HitActor,
			DamageValue,
			GetController(),
			this,
			UDamageType::StaticClass()
		);
	}
}

void ABaseCharacter::ClearHitList()
{
	HitActorsThisAttack.Empty();
}

void ABaseCharacter::HandleDeath()
{
	GetMesh()->SetSimulatePhysics(true);

	// Simulating Skeletal Mesh Component. All other channels will be set to default.
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));

	GetMesh()->AddImpulse(FVector(0, 0, 500.0f));

	//Call this function to detach safely pawn from its controller, knowing that we will be destroyed soon.
	DetachFromControllerPendingDestroy();
}

