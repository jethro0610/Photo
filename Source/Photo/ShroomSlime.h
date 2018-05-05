#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "ShroomSlime.generated.h"

UCLASS()
class PHOTO_API AShroomSlime : public ANPC
{
	GENERATED_BODY()
	
public:
	AShroomSlime();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
};
