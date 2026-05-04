#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, HealthPercent);

UCLASS()
class QA_TECH_TEST_API AEnemyCharacter : public ABaseCharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    float MaxWalkSpeed = 500.0f;

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnHealthChanged OnHealthChanged;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UPawnSensingComponent* PawnSensingComp;

    UFUNCTION()
    void OnSeePawn(APawn* SeenPawn);

    void FollowPlayer(APawn* PlayerPawn);

    void PerformAttack();

    UPROPERTY(EditAnywhere, Category = "Combat")
    UAnimMontage* AttackMontage = nullptr;

    // I dont know how to use this thing
    FTimerHandle AttackTimerHandle;

    bool bisFollowingPlayer = false;
};