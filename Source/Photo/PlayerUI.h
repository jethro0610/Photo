#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

class APhotoPlayer;
UCLASS()
class PHOTO_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		APhotoPlayer* parentPlayer;

	UFUNCTION(BlueprintImplementableEvent)
		void ScreenBlink(FColor screenColor);
};
