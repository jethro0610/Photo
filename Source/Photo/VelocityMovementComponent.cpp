// Fill out your copyright notice in the Description page of Project Settings.

#include "VelocityMovementComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UVelocityMovementComponent::UVelocityMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UVelocityMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	acceleration = maxWalkSpeed * friction;
}


// Called every frame
void UVelocityMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float deltaTick = DeltaTime * 60.0f;

	if (IsOnGround()) {
		AddVelocity((-GetVelocityXY() * friction) * deltaTick);
		if (GetGravity() < 0.0f) {
			SetGravity(0.0f);
			GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + (GetOwner()->GetActorUpVector() * (-2.0f * deltaTick)), true);
		}
	}
	else {
		AddGravity(-gravitySpeed);
	}

	MoveSliding(GetVelocity(), deltaTick);
}

FHitResult UVelocityMovementComponent::GetGroundTrace() {
	FHitResult groundTrace;

	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(GetOwner());
	traceParams.AddIgnoredComponent(Cast<UPrimitiveComponent, USceneComponent>(GetOwner()->GetRootComponent()));

	GetWorld()->LineTraceSingleByChannel(groundTrace, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + (GetOwner()->GetActorUpVector() * -groundDistance), ECC_WorldStatic, traceParams);

	return groundTrace;
}

bool UVelocityMovementComponent::IsOnGround() {
	return GetGroundTrace().IsValidBlockingHit();
}

FVector UVelocityMovementComponent::GetGroundNormal() {
	return GetGroundTrace().Normal;
}

FVector UVelocityMovementComponent::GetVelocity() {
	return velocity;
}

FVector UVelocityMovementComponent::GetVelocityXY() {
	return FVector(velocity.X, velocity.Y, 0);
}

float UVelocityMovementComponent::GetGravity() {
	return velocity.Z;
}

void UVelocityMovementComponent::SetVelocity(FVector newVelocity) {
	velocity = newVelocity;
}

void UVelocityMovementComponent::SetGravity(float newGravity) {
	velocity = FVector(velocity.X, velocity.Y, newGravity);
}

void UVelocityMovementComponent::AddVelocity(FVector deltaVelocity) {
	velocity += deltaVelocity;
}

void UVelocityMovementComponent::AddGravity(float deltaGravity) {
	velocity += FVector(0.0f, 0.0f, deltaGravity);
}

void UVelocityMovementComponent::MoveSliding(FVector deltaLocation, float deltaTick) {
	FHitResult movementHit;
	FVector deltaVector = deltaLocation * deltaTick;

	if (IsOnGround() && GetGravity() <= 0.0f) {
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector::VectorPlaneProject(deltaVector, GetGroundNormal()), true, &movementHit);
	}
	else {
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + deltaVector, true, &movementHit);
	}

	while (movementHit.IsValidBlockingHit()) {
		if (movementHit.GetActor()->IsValidLowLevel() && movementHit.GetActor()->IsA(UPrimitiveComponent::StaticClass())) {
			UPrimitiveComponent* hitObject = Cast<UPrimitiveComponent, AActor>(movementHit.GetActor());
			if(hitObject->IsSimulatingPhysics())
				hitObject->AddForceAtLocation(deltaLocation, movementHit.Location);
		}
		FVector slideNormal = FVector::VectorPlaneProject(deltaVector, movementHit.Normal);
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + slideNormal, true, &movementHit);
	}
}