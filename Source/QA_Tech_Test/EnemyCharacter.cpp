#include "EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
    PawnSensingComp->SightRadius = 2000.0f;
    PawnSensingComp->SetPeripheralVisionAngle(90.0f);

	AIControllerClass = AAIController::StaticClass();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    float HealthPercent = Health / MaxHealth;
    OnHealthChanged.Broadcast(HealthPercent);
    UE_LOG(LogTemp, Warning, TEXT("The Enemy sets HealthPercent to %f"), HealthPercent);

    return ActualDamage;    
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    UCharacterMovementComponent* MovementComp = GetCharacterMovement();
    MovementComp->MaxWalkSpeed = MaxWalkSpeed;

    if (PawnSensingComp)
    {
        PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
    }
}

void AEnemyCharacter::OnSeePawn(APawn* SeenPawn)
{
    if (SeenPawn->ActorHasTag(FName("Player")))
    {
        float Distance = FVector::Dist(GetActorLocation(), SeenPawn->GetActorLocation());
        if (Distance < 150.0f)
        {
            PerformAttack();
            return;
        }

		bisFollowingPlayer = true;
		FollowPlayer(SeenPawn);
    }
}

void AEnemyCharacter::FollowPlayer(APawn* PlayerPawn)
{
    AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC)
    {
        AIC->MoveToActor(PlayerPawn, 50.0f); 
	}
}

void AEnemyCharacter::PerformAttack()
{
    if (AttackMontage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy NPC is performing an attack!"));
        PlayAnimMontage(AttackMontage);
    }
}