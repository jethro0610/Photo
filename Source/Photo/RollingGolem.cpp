#include "RollingGolem.h"

ARollingGolem::ARollingGolem()
{
	canFlashByDefault = false;
	npcName = "Golem";
}

void ARollingGolem::BeginPlay()
{
	Super::BeginPlay();

	animationInstance->AddAnimCondition("Arm Attack");
	animationInstance->AddAnimCondition("Charge Attack");
}

void ARollingGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsNoticingPlayer()) {

		if (ShouldMove()) {
			FRotator interpRot = FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(0, GetLookAtPlayerRotation().Yaw, 0).Quaternion(), GetDeltaTick() * 0.05f).Rotator();
			SetActorRotation(interpRot);

			if (GetDistanceFromPlayer() >= 350.0f && movementComponent->IsOnGround()) {
				movementComponent->AddVelocity(GetActorRightVector() * movementComponent->acceleration);
			}
		}

		if (animationInstance->GetAnimCondition("Arm Attack") == false && FMath::RandRange(1,50) == 50 && GetDistanceFromPlayer() <= 350.0f && PlayerIsLevel(300.0f) && ShouldMove()) {
			animationInstance->SetAnimCondition("Arm Attack", true);
		}

		if (animationInstance->GetAnimCondition("Charge Attack") == false && FMath::RandRange(1, 100) == 100 && GetDistanceFromPlayer() >= 600.0f && PlayerIsLevel(300.0f) && ShouldMove()) {
			animationInstance->SetAnimCondition("Charge Attack", true);
		}

		if (FMath::Abs(GetPlayerLocation().Z - GetActorLocation().Z) <= 150.0f && GetDistanceFromPlayer() <= 200.0f) {
			animationInstance->SetAnimCondition("Charge Attack", false);
		}
		
		if (GetHitboxFromName(FName("Right_Arm"))->isHitting) {
			FRotator interpRot = FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(0, GetLookAtPlayerRotation().Yaw, 0).Quaternion(), GetDeltaTick() * 0.85f).Rotator();
			SetActorRotation(interpRot);
		}

		if (GetHitboxFromName(FName("Head"))->isHitting) {
			FRotator interpRot = FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(0, GetLookAtPlayerRotation().Yaw, 0).Quaternion(), GetDeltaTick() * 0.85f).Rotator();
			SetActorRotation(interpRot);
			movementComponent->AddVelocity(GetActorRightVector() * (movementComponent->acceleration*10.0f));
		}

		if (GetHitboxFromName(FName("Head"))->appliedHit == true) {
			movementComponent->SetVelocity(GetActorRightVector() * (movementComponent->acceleration*-100.0f));
			animationInstance->SetAnimCondition("Charge Attack", false);
		}
		
	}
}


