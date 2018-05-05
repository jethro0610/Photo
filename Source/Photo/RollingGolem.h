#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "RollingGolem.generated.h"

UCLASS()
class PHOTO_API ARollingGolem : public ANPC
{
	GENERATED_BODY()
	
public:
	ARollingGolem();

private:


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
