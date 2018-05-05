#include "Photograph.h"

UPhotograph::UPhotograph() {

}

void UPhotograph::UpdateFromRenderTarget(UTextureRenderTarget2D* inputRenderTarget) {
	updateDelegate.BindUFunction(this, TEXT("UpdateImage"));

	FTextureRenderTargetResource* renderResource = inputRenderTarget->GameThread_GetRenderTargetResource();

	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);
	readPixelFlags.SetLinearToGamma(true);

	TArray<FColor> uncompressedImage;
	renderResource->ReadPixels(uncompressedImage, readPixelFlags);

	int32 width = int32(inputRenderTarget->GetSurfaceWidth());
	int32 height = int32(inputRenderTarget->GetSurfaceHeight());
	(new FAutoDeleteAsyncTask<FCompressAsync>(uncompressedImage, width, height, updateDelegate))->StartBackgroundTask();
}

void UPhotograph::UpdateImage(TArray<uint8> updatedImage) {
	image = updatedImage;
}
