#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusConditionManager.generated.h"

DECLARE_DELEGATE(FStatusDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTO_API UStatusConditionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusConditionManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool isBurning;
	bool isWet;
	bool isSleeping;
	bool isSmelling;

public:
	void SetBurning(bool setActive);
	void SetWet(bool setActive);
	void SetSleeping(bool setActive);
	void SetSmelling(bool setActive);

	bool IsBurning();
	bool IsWet();
	bool IsSleeping();
	bool IsSmelling();

	FStatusDelegate burnEnabled;
	FStatusDelegate burnDisabled;

	FStatusDelegate wetEnabled;
	FStatusDelegate wetDisabled;

	FStatusDelegate sleepEnabled;
	FStatusDelegate sleepDisabled;

	FStatusDelegate smellEnabled;
	FStatusDelegate smellDisabled;

};
