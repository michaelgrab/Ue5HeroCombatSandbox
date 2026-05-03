#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class QA_TECH_TEST_API AEnemyCharacter : public ABaseCharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    float MaxWalkSpeed = 500.0f;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UPawnSensingComponent* PawnSensingComp;

    UFUNCTION()
    void OnSeePawn(APawn* SeenPawn);

    void FollowPlayer(APawn* PlayerPawn);

    void PerformAttack();

    UPROPERTY(EditAnywhere, Category = "Combat")
    UAnimMontage* AttackMontage;

    // I dont know how to use this thing
    FTimerHandle AttackTimerHandle;



    bool bisFollowingPlayer = false;
};