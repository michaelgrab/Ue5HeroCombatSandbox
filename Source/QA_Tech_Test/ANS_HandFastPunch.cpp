// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_HandFastPunch.h"

void UANS_HandFastPunch::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp && MeshComp->GetOwner()) {
		AActor* Owner = MeshComp->GetOwner();
		UWorld* World = Owner->GetWorld();
		FName BoneName = TEXT("hand_r");

		FVector BoneLocation = MeshComp->GetBoneLocation(BoneName, EBoneSpaces::WorldSpace);

		UE_LOG(LogTemp, Warning, TEXT("Bone '%s' location: '%s'"), *BoneName.ToString(), *BoneLocation.ToString());

		TArray<FHitResult> HitResults;

		if (World == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("World is null"));
			return;
		}
		DrawDebugSphere(World, BoneLocation, 50.0, 16, FColor::Red, false, 0.0f, 0, 2.0f);
		bool bHit = World->SweepMultiByChannel(
			HitResults,
			BoneLocation,
			BoneLocation,
			FQuat::Identity,
			ECC_Pawn,
			FCollisionShape::MakeSphere(50.0f)
		);
		if (bHit) {
			for (const FHitResult& Hit : HitResults) {
				UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *Hit.GetActor()->GetActorLabel());
			}
		}
	}
}
