#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Hitbox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTO_API UHitbox : public USceneComponent
{
	GENERATED_BODY()

public:	
	UHitbox();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* collisionBubble;

	UPROPERTY(EditAnywhere)
		FName hitboxName;

	UPROPERTY(EditAnywhere)
		bool isHitting = false;

	bool appliedHit = false;
	
	UPROPERTY(EditAnywhere)
		FVector knockbackForce;
};
