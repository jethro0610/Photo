#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VelocityMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTO_API UVelocityMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVelocityMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector velocity;
	FHitResult GetGroundTrace();

public:
	UPROPERTY(EditAnywhere)
		float gravitySpeed;

	UPROPERTY(EditAnywhere)
		float groundDistance;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "0.0"))
		float friction;

	UPROPERTY(EditAnywhere)
		float maxWalkSpeed;

	float acceleration;

	FVector GetVelocity();
	FVector GetVelocityXY();
	float GetGravity();
	void SetVelocity(FVector newVelocity);
	void SetGravity(float newGravity);
	void AddVelocity(FVector deltaVelocity);
	void AddGravity(float deltaGravity);

	bool IsOnGround();
	FVector GetGroundNormal();

	void MoveSliding(FVector deltaLocation, float deltaTick);
};
