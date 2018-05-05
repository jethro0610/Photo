#include "PlayerMovementComponent.h"
#include "Engine.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*
	float deltaDifference = DeltaTime * 60.0f;

	if (!parentPlayer->IsOnGround(50.0f)) {
		if (velocity.Z == 0.0f) {
			velocity /= 2.0f;
		}
		velocity.Z -= gravitySpeed * deltaDifference;
	}
	else {
		if (velocity.Z <= 0.0f)
			velocity.Z = 0.0f;

		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() - (parentPlayer->GetActorUpVector()*50.0f), true);
	}

	if (parentPlayer->IsOnGround(50.0f)) {
		velocity += (parentPlayer->GetActorForwardVector() * (parentPlayer->yInputAxis* acceleration)) * deltaDifference;
		velocity += (parentPlayer->GetActorRightVector() * (parentPlayer->xInputAxis* acceleration)) * deltaDifference;
		velocity -= (FVector(velocity.X, velocity.Y, 0.0f) / deceleration) * deltaDifference;
	}
	MoveSliding(velocity, deltaDifference);
	*/
}

void UPlayerMovementComponent::MoveSliding(FVector desiredVector, float deltaDifference) {
	/*
	FHitResult movementHit;
	FVector deltaVector = desiredVector * deltaDifference;

	if (parentPlayer->IsOnGround(50.0f) && velocity.Z <= 0.0f) {
		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + FVector::VectorPlaneProject(deltaVector, parentPlayer->GetGroundNormal(50.0f)), true, &movementHit);
	}
	else{
		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + deltaVector, true, &movementHit);
	}
	if (movementHit.IsValidBlockingHit()) {
		FVector slideNormal = FVector::VectorPlaneProject(deltaVector, movementHit.Normal);
		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + slideNormal, true, &movementHit);
	}
	*/
}

void UPlayerMovementComponent::Jump(float height, FVector direction) {
	//velocity = (parentPlayer->GetActorUpVector()*height) + direction;
}