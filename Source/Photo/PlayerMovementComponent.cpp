// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovementComponent.h"


// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!parentPlayer->IsOnGround(150.0f)) {
		velocity.Z -= gravitySpeed;
	}
	else {
		velocity.Z = 0.0f;
	}

	velocity.X += (acceleration*parentPlayer->xInputAxis) - (velocity.X / deceleration);
	velocity.Y += (acceleration*parentPlayer->yInputAxis) - (velocity.Y / deceleration);

	ApplyMovement(GetRelativeVector(velocity));
}

FVector UPlayerMovementComponent::GetRelativeVector(FVector inputVector) {
	FVector relativeX = parentPlayer->GetActorRightVector() * inputVector.X;
	FVector relativeY = parentPlayer->GetActorForwardVector() * inputVector.Y;
	FVector relativeZ = parentPlayer->GetActorUpVector() * inputVector.Z;

	return relativeX + relativeY + relativeZ;
}

void UPlayerMovementComponent::ApplyMovement(FVector desiredVector) {
	FHitResult movementHit;

	parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + FVector::VectorPlaneProject(desiredVector,parentPlayer->GetGroundNormal(150.0f)), true, &movementHit);

	if (movementHit.IsValidBlockingHit()) {
		FVector slideVector = FVector::VectorPlaneProject(desiredVector, movementHit.Normal);
		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + slideVector, true, &movementHit);
	}
}