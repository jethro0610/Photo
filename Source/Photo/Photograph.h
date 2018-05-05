#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Public/ImageUtils.h"
#include "Photograph.generated.h"

DECLARE_DELEGATE_OneParam(FUpdateImageDelegate, TArray<uint8>);

class FCompressAsync : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FCompressAsync>;

public:
	FCompressAsync(TArray<FColor> inputImage, int32 inputWidth, int32 inputHeight, FUpdateImageDelegate inputDelegate) :
		imageToCompress(inputImage),
		imageWidth(inputWidth),
		imageHeight(inputHeight),
		updateDelagate(inputDelegate)
	{}

protected:
	TArray<FColor> imageToCompress;
	int32 imageWidth;
	int32 imageHeight;
	FUpdateImageDelegate updateDelagate;

	void DoWork() {
		TArray<uint8> imageOutput;
		FImageUtils::CompressImageArray(imageWidth, imageHeight, imageToCompress, imageOutput);
		updateDelagate.Execute(imageOutput);
	}

	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCompressAsync, STATGROUP_ThreadPoolAsyncTasks);
	}
};

UCLASS()
class PHOTO_API UPhotograph : public UObject
{
	GENERATED_BODY()

public:
	UPhotograph();
	void UpdateFromRenderTarget(UTextureRenderTarget2D* inputRenderTarget);

	TArray<uint8> image;
	
	UFUNCTION(DisplayName = "UpdateImage")
	void UpdateImage(TArray<uint8> updatedImage);

	FUpdateImageDelegate updateDelegate;
};
