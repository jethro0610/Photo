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

	if (!parentPlayer->IsOnGround(30.0f)) {
		velocity.Z -= gravitySpeed;
	}
	else {
		velocity.Z = 0.0f;
	}

	velocity.Y += (acceleration*parentPlayer->xInputAxis) - (velocity.Y / deceleration);
	velocity.X += (acceleration*parentPlayer->yInputAxis) - (velocity.X / deceleration);

	ApplyMovement(GetRelativeVector(velocity));
}

FVector UPlayerMovementComponent::GetRelativeVector(FVector inputVector) {
	FVector relativeX;
	FVector relativeY;
	FVector relativeZ;

	relativeX = parentPlayer->GetActorForwardVector() * inputVector.X;
	relativeY = parentPlayer->GetActorRightVector() * inputVector.Y;
	relativeZ = parentPlayer->GetActorUpVector() * inputVector.Z;

	return relativeX + relativeY + relativeZ;
}

void UPlayerMovementComponent::ApplyMovement(FVector desiredVector) {
	FVector newLocation;
	FHitResult movementHit;
	newLocation = parentPlayer->GetActorLocation() + desiredVector;

	parentPlayer->SetActorLocation(newLocation, true, &movementHit);
	//while (movementHit.IsValidBlockingHit()) {
		//parentPlayer->SetActorLocation(newLocation * movementHit.Normal, true, &movementHit);
	//}
}