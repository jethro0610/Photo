#include "ShroomSlime.h"

AShroomSlime::AShroomSlime() {
	npcName = "Slime";
}

void AShroomSlime::BeginPlay() {
	Super::BeginPlay();
	animationInstance->AddAnimCondition("Walking");
}

void AShroomSlime::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetDistanceFromPlayer() <= 800.0f && !IsFlashed()) {
		FRotator interpRot = FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(0, GetLookAtPlayerRotation().Yaw - 180.0f, 0).Quaternion(), GetDeltaTick() * 0.01f).Rotator();
		SetActorRotation(interpRot);
		movementComponent->AddVelocity(GetActorRightVector() * (movementComponent->acceleration/5.0f));
		animationInstance->SetAnimCondition("Walking", true);
	}
	else {
		animationInstance->SetAnimCondition("Walking", false);
	}
}
